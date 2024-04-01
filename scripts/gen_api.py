import json
import os
import sys

kModules = ["author", "chain", "state", "payment", "system"]
kSkipUnsafeMethods = True

def generate_rpc_client(modules, output_dir):
    class_name = "rpc_client"
    filename = os.path.join(output_dir, f"{class_name}.h")
    module_forward_macro = []

    with open(filename, 'w') as file:
        file.write("#pragma once\n")
        file.write("#include \"types.h\"\n\n")
        for module in modules:
            module = module.replace("/", "_");
            if module in kModules:
                file.write(f'#include "rpc/rpc_{module}.h"\n')
                module_forward_macro.append(f"   SUBSTRATE_IMPL_RPC_{str.upper(module)}")
        file.write("\nnamespace substrate::rpc\n{\n")
        file.write(f"   class LIB_SUBSTRATE_EXPORT {class_name} :\n")
        module_classes = [f"      public {module.replace('/', '_')}" for module in modules if module in kModules]
        file.write(",\n".join(module_classes))
        file.write("\n   {\n   public:\n")
        file.write(f"      virtual ~{class_name}() = default;\n")
        file.write("   };\n}\n")
        file.write(f"#ifndef SUBSTRATE_IMPL_RPC_CLIENT\n")
        file.write(f"#define SUBSTRATE_IMPL_RPC_CLIENT \\\n")
        file.write(str.join(" \\\n", module_forward_macro))
        file.write(f"\n#endif\n")


def generate_cpp_source_for_module(module_name, methods, output_dir):
    module_name_sanitized = module_name.replace("/", "_")
    filename = os.path.join(output_dir, f"rpc_{module_name_sanitized}.cpp")
    with open(filename, 'w') as file:
        file.write("#include \"substrate_client.h\"\n\n")
        file.write("using namespace substrate::rpc;\n")
        file.write("using namespace substrate::rpc::detail;\n\n")
        for index, method in enumerate(methods):
            if kSkipUnsafeMethods and 'unsafe' in method and method['unsafe']:
                continue
            params = ", ".join(f"std::optional<{param['type']}> {param['name']}" if param['optional'] else f"{param['type']} {param['name']}" for param in method['method']['parameters'])
            method_declaration = f"{method['method']['returnType']} substrate_client::{method['name']}({params}) const"
            file.write(method_declaration + "\n")
            file.write("{\n")
            # Simplify to just pass parameter names
            rpc_params = ", ".join(param['name'] for param in method['method']['parameters'])
            # Handle methods with zero parameters by passing an empty json array for such cases
            rpc_call = f"rpc<{method['method']['returnType']}>(\"{method['name']}\"" + (f", {rpc_params}" if rpc_params else "") + ");"
            file.write(f"   return {rpc_call}\n")
            file.write("}\n\n")


def generate_cpp_header_for_module(module_name, methods, output_dir):
    module_name_sanitized = module_name.replace("/", "_")
    filename = os.path.join(output_dir, f"rpc_{module_name_sanitized}.h")
    with open(filename, 'w') as file:
        file.write("#pragma once\n\n")
        file.write(f"namespace substrate::rpc\n{{\n   class LIB_SUBSTRATE_EXPORT {module_name_sanitized}\n   {{\n   public:\n")
        file.write("      virtual ~{}() = default;\n\n".format(module_name_sanitized))

        method_forward_macro = []

        for index, method in enumerate(methods):
            if kSkipUnsafeMethods and 'unsafe' in method and method['unsafe']:
                continue
            if 'summary' in method:
                file.write("      /**\n       * @brief {}\n".format(method['summary']))
                if 'unsafe' in method and method['unsafe']:
                    file.write("       * @warning This method is marked as unsafe.\n")
                if 'deprecated' in method and method['deprecated']:
                    file.write("       * @deprecated This method is deprecated.\n")
                for param in method['method']['parameters']:
                    file.write("       * @param {} {}\n".format(param['name'], param['type']))
                if method['method']['returnType'] != 'void':
                    file.write("       * @return {}\n".format(method['method']['returnType']))
                file.write("       */\n")
            params = ", ".join(f"std::optional<{param['type']}> {param['name']} = std::nullopt" if param['optional'] else f"{param['type']} {param['name']}" for param in method['method']['parameters'])
            method_declaration = f"      virtual {method['method']['returnType']} {method['name']}({params}) const = 0;"
            method_forward_impl_declaration = f"   virtual {method['method']['returnType']} {method['name']}({params}) const override;"
            method_forward_macro.append(method_forward_impl_declaration)

            if index == len(methods) - 1:
                file.write(method_declaration + "\n")
            else:
                file.write(method_declaration + "\n\n")

        file.write("   };\n}\n\n")
        up = str.upper(module_name_sanitized)
        file.write(f"#ifndef SUBSTRATE_IMPL_RPC_{up}\n")
        file.write(f"#define SUBSTRATE_IMPL_RPC_{up} \\\n")
        file.write(str.join(" \\\n", method_forward_macro))
        file.write(f"\n#endif\n")

def generate_interfaces_from_json(json_file, output_dir):
    with open(json_file, 'r') as file:
        data = json.load(file)

    for module_name, methods in data.items():
        module_name = module_name.replace("/", "_")
        if module_name in kModules:
            generate_cpp_header_for_module(module_name, methods, os.path.join(output_dir, "public", "substrate", "rpc"))
            generate_cpp_source_for_module(module_name, methods, os.path.join(output_dir, "src", "rpc"))
    generate_rpc_client(data, os.path.join(output_dir, "public", "substrate"))

if __name__ == "__main__":
    json_file_path = sys.argv[1]
    output_directory = "libSubstrate"
    generate_interfaces_from_json(json_file_path, output_directory)
