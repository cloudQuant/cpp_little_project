#include <zlib.h>
#include <iostream>
#include <iomanip>
#include <vector>

std::vector<uint8_t> gzipCompress(const std::string& input) {
    z_stream zs;
    memset(&zs, 0, sizeof(zs));

    if (deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        throw(std::runtime_error("deflateInit2 failed while compressing."));
    }

    zs.next_in = (Bytef*)input.data();
    zs.avail_in = input.size();

    int ret;
    std::vector<uint8_t> outbuffer;
    outbuffer.resize(32768);

    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer.data());
        zs.avail_out = outbuffer.size();

        ret = deflate(&zs, Z_FINISH);

        if (outbuffer.size() - zs.avail_out > 0) {
            outbuffer.resize(outbuffer.size() - zs.avail_out);
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {
        throw(std::runtime_error("Exception during zlib compression: (" + std::to_string(ret) + ") " + zs.msg));
    }

    return outbuffer;
}

int main() {
    std::string input = "Hello, World!";
    std::vector<uint8_t> compressedData = gzipCompress(input);

    std::cout << "Compressed data: ";
    for (size_t i = 0; i < compressedData.size(); i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)compressedData[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}