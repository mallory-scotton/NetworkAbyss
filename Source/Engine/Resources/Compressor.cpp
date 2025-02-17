///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Resources/Compressor.hpp>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Data Compressor::compress(const Data& data, int level)
{
    Uint64 maxSize = compressBound(data.size());
    Data cdata(maxSize);
    Uint64 csize = maxSize;

    int result = compress2(
        cdata.data(),
        &csize,
        data.data(),
        data.size(),
        level
    );
    if (result != Z_OK)
        throw std::runtime_error("Compression failed");
    cdata.resize(csize);
    return (cdata);
}

///////////////////////////////////////////////////////////////////////////////
Data Compressor::decompress(const Data& cdata, Uint64 size)
{
    Data data(size);
    Uint64 dsize = size;

    int result = uncompress(
        data.data(),
        &dsize,
        cdata.data(),
        cdata.size()
    );
    if (result != Z_OK)
        throw std::runtime_error("Decompression failed");
    return (data);
}

} // namespace tkd
