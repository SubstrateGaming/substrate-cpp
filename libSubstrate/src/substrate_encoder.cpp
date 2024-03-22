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

encoder& encoder::operator<<(const std::span<const uint8_t>& v)
{
   _detail->_stream << v;
   return *this;
}

std::vector<uint8_t> encoder::assemble() const
{
   return _detail->_stream.to_vector();
}

std::string encoder::assemble_hex() const
{
   const auto data = assemble();
   return hex_encode(data);
}