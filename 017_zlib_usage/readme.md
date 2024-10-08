zlib.h 是 zlib 库的头文件，zlib 是一个广泛使用的数据压缩库，提供了对数据进行压缩和解压缩的功能。
zlib 库最初由 Jean-loup Gailly 和 Mark Adler 开发，主要用于处理 gzip 格式的数据压缩。

### 功能
zlib.h 提供了以下主要功能：

- 数据压缩：将数据压缩为更小的数据块。

- 数据解压缩：将压缩后的数据解压缩为原始数据。

- 流式压缩和解压缩：支持流式处理，可以逐步压缩或解压缩数据。

- 内存管理：提供内存分配和释放的函数。

- 错误处理：提供错误码和错误信息。

### 主要数据结构
zlib.h 中定义了几个主要的数据结构：

- z_stream：表示压缩或解压缩的流。它包含了输入和输出的缓冲区、压缩或解压缩的状态等信息。
```c++
typedef struct z_stream_s {
    z_const Bytef *next_in;  /* 输入缓冲区的下一个字节 */
    uInt avail_in;           /* 输入缓冲区中可用的字节数 */
    uLong total_in;          /* 输入的总字节数 */

    Bytef *next_out;         /* 输出缓冲区的下一个字节 */
    uInt avail_out;          /* 输出缓冲区中可用的字节数 */
    uLong total_out;         /* 输出的总字节数 */

    z_const char *msg;       /* 错误信息 */
    struct internal_state FAR *state; /* 内部状态 */

    alloc_func zalloc;       /* 内存分配函数 */
    free_func zfree;         /* 内存释放函数 */
    voidpf opaque;           /* 用户数据 */

    int data_type;           /* 数据类型 */
    uLong adler;             /* Adler-32 或 CRC-32 校验和 */
    uLong reserved;          /* 保留字段 */
} z_stream;
```
### 主要函数
zlib.h 中定义了多个函数，用于压缩和解压缩数据。以下是一些常用的函数：

- deflateInit：初始化压缩流。

- deflate：执行压缩操作。

- deflateEnd：结束压缩流。

- inflateInit：初始化解压缩流。

- inflate：执行解压缩操作。

- inflateEnd：结束解压缩流。

- compress：一次性压缩数据。

- uncompress：一次性解压缩数据。

### 编译指令
```g++ main.cpp -o main -lz```

### 代码

```c++
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

```