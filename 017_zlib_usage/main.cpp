#include <stdio.h>
#include <string.h>
#include <zlib.h>

void compress_data(){
    const char* input = "Hello, zlib!";
    uLong input_len = strlen(input) + 1;
    uLong output_len = compressBound(input_len);
    Bytef output[output_len];

    int ret = compress(output, &output_len, (const Bytef*)input, input_len);
    if (ret != Z_OK) {
        printf("Compression failed: %d\n", ret);
    }
    printf("before compressed size: %lu\n", input_len);
    printf("Compressed size: %lu\n", output_len);
 }

 void uncompress_data(){
    const char* input = "Hello, zlib!";
    uLong input_len = strlen(input) + 1;
    uLong output_len = compressBound(input_len);
    Bytef compressed[output_len];

    int ret = compress(compressed, &output_len, (const Bytef*)input, input_len);
    if (ret != Z_OK) {
        printf("Compression failed: %d\n", ret);
    }

    Bytef uncompressed[input_len];
    uLong uncompressed_len = input_len;

    ret = uncompress(uncompressed, &uncompressed_len, compressed, output_len);
    if (ret != Z_OK) {
        printf("Decompression failed: %d\n", ret);
    }

    printf("Uncompressed data: %s\n", uncompressed);
 }

 void inflate_data(){
    const char* input = "Hello, zlib!";
    uLong input_len = strlen(input) + 1;
    uLong output_len = compressBound(input_len);
    Bytef output[output_len];

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef*)input;
    stream.avail_in = input_len;
    stream.next_out = output;
    stream.avail_out = output_len;

    int ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        printf("deflateInit failed: %d\n", ret);
    }

    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        printf("deflate failed: %d\n", ret);
        deflateEnd(&stream);
    }

    deflateEnd(&stream);
    printf("Compressed size: %lu\n", output_len - stream.avail_out);
 }

 void deflate_data(){
    const char* input = "Hello, zlib!";
    uLong input_len = strlen(input) + 1;
    uLong output_len = compressBound(input_len);
    Bytef compressed[output_len];

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.next_in = (Bytef*)input;
    stream.avail_in = input_len;
    stream.next_out = compressed;
    stream.avail_out = output_len;

    int ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
        printf("deflateInit failed: %d\n", ret);
    }

    ret = deflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        printf("deflate failed: %d\n", ret);
        deflateEnd(&stream);
    }

    deflateEnd(&stream);

    Bytef uncompressed[input_len];
    uLong uncompressed_len = input_len;

    stream.next_in = compressed;
    stream.avail_in = output_len - stream.avail_out;
    stream.next_out = uncompressed;
    stream.avail_out = uncompressed_len;

    ret = inflateInit(&stream);
    if (ret != Z_OK) {
        printf("inflateInit failed: %d\n", ret);
    }

    ret = inflate(&stream, Z_FINISH);
    if (ret != Z_STREAM_END) {
        printf("inflate failed: %d\n", ret);
        inflateEnd(&stream);
    }

    inflateEnd(&stream);
    printf("Uncompressed data: %s\n", uncompressed);
 }

int main() {
    compress_data();
    uncompress_data();
    inflate_data();
    deflate_data();
    return 0;
}