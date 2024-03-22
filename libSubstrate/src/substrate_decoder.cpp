#include "logger.h"

#include <substrate/decoder.h>
#include <scale/scale_decoder_stream.hpp>

using namespace substrate;

namespace substrate::details
{
   class decoder
   {
   public:
      scale::ScaleDecoderStream _stream;

      decoder(std::span<const uint8_t> bytes)
          : _stream(std::move(bytes))
      {
      }
   };
}

decoder::decoder(std::span<const uint8_t> bytes)
    : _detail(std::make_unique<details::decoder>(std::move(bytes)))
{
}

decoder::~decoder()
{
}

decoder &decoder::operator>>(uint8_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(uint16_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(uint32_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(uint64_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(int8_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(int16_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(int32_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(int64_t &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(CompactInteger &v)
{
   _detail->_stream >> v;
   return *this;
}

decoder &decoder::operator>>(bool &v)
{
   _detail->_stream >> v;
   return *this;
}
