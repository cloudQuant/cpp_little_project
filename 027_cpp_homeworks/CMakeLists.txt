# 设置 CMake 的最低版本
cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "/Users/yunjinqi/vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_TOOLCHAIN_FILE "/home/yun/vcpkg/scripts/buildsystems/vcpkg.cmake")
# 项目名称
project(MyHomeworkProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# 添加头文件路径
include_directories(include)

## 添加源文件
#set(SOURCES
#
#)
#
## 添加库目标
#add_library(my_homework ${SOURCES})

# 添加测试文件
set(TEST_SOURCES
        tests/test_my_homework.cpp
        tests/test_pointer.cpp
)

# 添加测试目标
add_executable(test_my_homework ${TEST_SOURCES})


# 启用测试
enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_my_homework PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)



# 添加测试
add_test(
        NAME test_my_homework
        COMMAND test_my_homework
)