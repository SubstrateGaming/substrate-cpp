import re
import json
import requests

# Not really straight forward to detect from this metadata, hence this hard-coded variant to simplify things.
kSubscriptionAPI = ["submitAndWatchExtrinsic", "subscribeAllHeads", "subscribeFinalizedHeads", "subscribeNewHeads", "subscribeRuntimeVersion", "subscribeStorage"]

def parse_typescript_signature_with_return(signature):
    signature = str.replace(signature, "`", "")
    method_pattern = re.compile(r'(\w+)\s*\((.*?)\)\s*(?::\s*(.+))?')
    match = method_pattern.search(signature)
    if not match:
        return None

    method_name, params_block, return_type = match.groups()
    params = params_block.split(',') if params_block else []

    param_details = []
    for param in params:
        param = param.strip()
        if not param:
            continue
        parts = param.split(':')
        param_name = parts[0].strip().replace('?', '')
        param_type = parts[1].strip() if len(parts) > 1 else 'unknown'
        is_optional = '?' in parts[0]

        param_details.append({
            # 'signature': signature,
            'name': param_name,
            'type': param_type,
            'optional': is_optional
        })

    # We kinda "inject" our subscription API right into this.
    if method_name in kSubscriptionAPI:
        param_details.insert(0, {
            'name': 'callback',
            'type': 'subscription_callback_t',
            'optional': False
        })
        return_type = 'std::string'
    else:
        # Correctly set return type based on presence
        return_type = return_type.strip() if return_type else 'void'

    return {
        'parameters': param_details,
        'returnType': return_type
    }


def format_key(key):
    key = key.strip()
    ignored_keys = ["interface"]
    if key in ignored_keys:
        return None
    keys = ["jsonrpc", "summary", "unsafe", "deprecated"]
    if key not in keys:
        raise Exception(f"Unknown key: {key}")
    if key == "jsonrpc":
        return "name"
    return key

def format_value(key, value):
    value = value.strip()
    if key in ["unsafe", "deprecated"]:
        return True
    value = str.replace(value, "`", "")
    return value

def parse_markdown_to_json(content):
    section_regex = re.compile(r'^##\s+(.+)$', re.MULTILINE)
    method_regex = re.compile(r'^###\s+(.+?\(.*?\)): `(.+?)`', re.MULTILINE)
    detail_regex = re.compile(r'^- \*\*(.+?)\*\*:\s*(.+)$', re.MULTILINE)

    data_structure = {}

    sections = list(section_regex.finditer(content))

    for i, section in enumerate(sections):
        section_name = section.group(1).strip()
        section_data = []
        section_start = section.end()
        section_end = sections[i+1].start() if i+1 < len(sections) else len(content)

        section_content = content[section_start:section_end]
        methods = list(method_regex.finditer(section_content))

        for j, method in enumerate(methods):
            method_signature = f"{ method.group(1).strip()}: {method.group(2).strip()}"
            method_data = {}
            method_start = method.end()
            method_end = methods[j+1].start() if j+1 < len(methods) else len(section_content)

            method_content = section_content[method_start:method_end]
            details = detail_regex.findall(method_content)

            for detail in details:
                key, value = detail
                key = format_key(key)
                if key is None:
                    continue
                value = format_value(key, value)
                if value is None:
                    continue
                method_data[key] = value

            method_data["method"] = parse_typescript_signature_with_return(method_signature)
            section_data.append(method_data)

        data_structure[section_name] = section_data

    json_data = json.dumps(data_structure, indent=4)
    return json_data


def download_markdown(url):
    response = requests.get(url)
    response.raise_for_status()
    return response.text

content = download_markdown("https://raw.githubusercontent.com/polkadot-js/docs/master/docs/substrate/rpc.md")
json_output = parse_markdown_to_json(content)
print(json_output)
