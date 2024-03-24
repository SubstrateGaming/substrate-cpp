#include "logger.h"

#include <substrate/decoder.h>
#include <scale/scale_decoder_stream.hpp>

using namespace substrate;

namespace substrate::details
{
   class decoder
   {
   public:
      size_t _size;
      std::vector<uint8_t> _bytes;
      scale::ScaleDecoderStream _stream;

      decoder(std::vector<uint8_t> bytes)
         : _size(bytes.size())
         , _bytes(std::move(bytes))
         , _stream(_bytes)
      {
      }
   };
}

decoder::decoder(std::vector<uint8_t> bytes)
   : _detail(std::make_unique<details::decoder>(std::move(bytes)))
{
}

decoder::~decoder()
{
}

size_t decoder::size() const
{
   return _detail->_size;
}

std::span<const uint8_t> decoder::bytes() const
{
   return _detail->_stream.span();
}

void decoder::seek(size_t offset)
{
   assert(_detail->_stream.hasMore(offset));
   _detail->_stream.seek(offset);
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

decoder &decoder::operator>>(std::vector<uint8_t>& v)
{
   // Decode as static collection, not as dynamic.
   // This means we take the remaining bytes.
   while (_detail->_stream.hasMore(1))
      v.emplace_back(_detail->_stream.nextByte());
   return *this;
}
