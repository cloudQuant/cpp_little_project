#include <stdio.h>
#include <string.h>
#include <zlib.h>

void compress_data(const char* input, uLong input_len, Bytef* output, uLong* output_len) {
    int ret = compress(output, output_len, (const Bytef*)input, input_len);
    if (ret != Z_OK) {
        printf("Compression failed: %d\n", ret);
    }
}

void uncompress_data(const Bytef* input, uLong input_len, Bytef* output, uLong* output_len) {
    int ret = uncompress(output, output_len, input, input_len);
    if (ret != Z_OK) {
        printf("Decompression failed: %d\n", ret);
    }
}

int main() {
    //const char* input = "Hello, zlib! This is a test string to demonstrate zlib compression and decompression.";
    const char* input = "Hello, zlib! This is a test string to demonstrate zlib ";
    uLong input_len = strlen(input) + 1;
    uLong output_len = compressBound(input_len);
    Bytef compressed[output_len];
    Bytef uncompressed[input_len];

    // 压缩数据
    compress_data(input, input_len, compressed, &output_len);

    // 判断压缩是否有效
    if (output_len < input_len) {
        printf("Compression is effective. Original size: %lu, Compressed size: %lu\n", input_len, output_len);
    } else {
        printf("Compression is not effective. Original size: %lu, Compressed size: %lu\n", input_len, output_len);
    }

    // 解压缩数据
    uLong uncompressed_len = input_len;
    uncompress_data(compressed, output_len, uncompressed, &uncompressed_len);

    // 验证解压缩后的数据是否与原始数据一致
    if (strcmp((const char*)uncompressed, input) == 0) {
        printf("Decompression successful. Uncompressed data matches the original data.\n");
    } else {
        printf("Decompression failed. Uncompressed data does not match the original data.\n");
    }

    return 0;
}