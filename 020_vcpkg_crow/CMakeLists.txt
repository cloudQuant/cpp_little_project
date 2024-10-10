cmake_minimum_required(VERSION 3.10)
set(CMAKE_TOOLCHAIN_FILE "/Users/yunjinqi/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(test_crow LANGUAGES CXX)
# 设置C++标准为C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(Crow REQUIRED)
add_executable(test_crow main.cpp)
target_link_libraries(test_crow PRIVATE Crow::Crow asio::asio)





