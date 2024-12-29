# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(IconvExample)

# 查找 libiconv
find_package(Iconv REQUIRED)

# 打印 libiconv 的相关信息
message(STATUS "Iconv found: ${Iconv_FOUND}")
message(STATUS "Iconv include dirs: ${Iconv_INCLUDE_DIRS}")
message(STATUS "Iconv libraries: ${Iconv_LIBRARIES}")

# 包含 libiconv 的头文件路径
include_directories(${Iconv_INCLUDE_DIRS})

# 查找 libiconv 库
find_library(ICONV_LIBRARY iconv)
if (NOT ICONV_LIBRARY)
    message(FATAL_ERROR "libiconv not found")
endif()
message(STATUS "ICONV_LIBRARY: ${ICONV_LIBRARY}")

# 添加可执行文件
add_executable(iconv_example main.cpp)

# 链接 libiconv
target_link_libraries(iconv_example ${ICONV_LIBRARY})