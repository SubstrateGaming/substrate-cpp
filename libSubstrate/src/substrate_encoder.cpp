#include "logger.h"

#include <substrate/encoder.h>
#include <substrate/hex.h>

#include <scale/scale_encoder_stream.hpp>

using namespace substrate;

namespace substrate::details
{
   class encoder
   {
   public:
      scale::ScaleEncoderStream _stream;

      encoder()
      {
      }
   };
}

encoder::encoder()
    : _detail(std::make_unique<details::encoder>())
{
}

encoder::~encoder()
{
}

encoder &encoder::operator<<(uint8_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(uint16_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(uint32_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(uint64_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(int8_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(int16_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(int32_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(int64_t v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(CompactInteger v)
{
   _detail->_stream << v;
   return *this;
}

encoder &encoder::operator<<(bool v)
{
   _detail->_stream << v;
   return *this;
}

// Encode as static collection, not as dynamic.
encoder& encoder::operator<<(const std::span<const uint8_t>& v)
{
   for (const auto item : v) {
      _detail->_stream << item;
   }
   return *this;
}

// Encodes as dynamic collection (pre-fixed with size)
encoder& encoder::operator<<(const encoder& v)
{
   const auto data = v.assemble();
   _detail->_stream << substrate::CompactInteger(data.size());
   for (const auto item : data) {
      _detail->_stream << item;
   }
   return *this;
}

substrate::bytes encoder::assemble() const
{
   return _detail->_stream.to_vector();
}

std::string encoder::assemble_hex() const
{
   const auto data = assemble();
   return hex_encode(data);
}