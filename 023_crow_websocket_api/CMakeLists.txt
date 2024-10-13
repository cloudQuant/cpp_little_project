cmake_minimum_required(VERSION 3.7)
set(CMAKE_TOOLCHAIN_FILE "/Users/yunjinqi/vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_TOOLCHAIN_FILE "/home/yun/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(hello_crow)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Crow REQUIRED)
add_executable(hello_crow main.cpp)
target_link_libraries(hello_crow PRIVATE Crow::Crow asio::asio)

find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(hello_crow PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)

find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(hello_crow PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

find_package(RapidJSON CONFIG REQUIRED)
target_link_libraries(hello_crow PRIVATE rapidjson)