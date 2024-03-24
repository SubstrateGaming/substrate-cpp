#include <substrate/wrap_message.h>

const std::string substrate::wrap_message::U8A_WRAP_PREFIX_STR = "<Bytes>";
const std::string substrate::wrap_message::U8A_WRAP_POSTFIX_STR = "</Bytes>";
std::vector<uint8_t> substrate::wrap_message::U8A_WRAP_PREFIX(U8A_WRAP_PREFIX_STR.begin(), U8A_WRAP_PREFIX_STR.end());
std::vector<uint8_t> substrate::wrap_message::U8A_WRAP_POSTFIX(U8A_WRAP_POSTFIX_STR.begin(), U8A_WRAP_POSTFIX_STR.end());
size_t substrate::wrap_message::wrapLength = U8A_WRAP_PREFIX.size() + U8A_WRAP_POSTFIX.size();

bool substrate::wrap_message::is_wrapped(const std::vector<uint8_t> &data)
{
   if (data.size() < wrapLength)
      return false;

   return std::equal(U8A_WRAP_PREFIX.begin(), U8A_WRAP_PREFIX.end(), data.begin()) &&
          std::equal(U8A_WRAP_POSTFIX.begin(), U8A_WRAP_POSTFIX.end(), data.end() - U8A_WRAP_POSTFIX.size());
}

bool substrate::wrap_message::is_wrapped(const std::string &data)
{
   return is_wrapped(std::vector<uint8_t>(data.begin(), data.end()));
}

std::vector<uint8_t> substrate::wrap_message::unwrap(const std::vector<uint8_t> &data)
{
   if (!is_wrapped(data))
      return data;

   return std::vector<uint8_t>(data.begin() + U8A_WRAP_PREFIX.size(), data.end() - U8A_WRAP_POSTFIX.size());
}

std::vector<uint8_t> substrate::wrap_message::unwrap(const std::string &data)
{
   return unwrap(std::vector<uint8_t>(data.begin(), data.end()));
}

std::vector<uint8_t> substrate::wrap_message::wrap(const std::vector<uint8_t> &data)
{
   if (is_wrapped(data))
      return data;

   std::vector<uint8_t> wrappedData;
   wrappedData.insert(wrappedData.end(), U8A_WRAP_PREFIX.begin(), U8A_WRAP_PREFIX.end());
   wrappedData.insert(wrappedData.end(), data.begin(), data.end());
   wrappedData.insert(wrappedData.end(), U8A_WRAP_POSTFIX.begin(), U8A_WRAP_POSTFIX.end());
   return wrappedData;
}

std::vector<uint8_t> substrate::wrap_message::wrap(const std::string &data)
{
   return wrap(std::vector<uint8_t>(data.begin(), data.end()));
}
