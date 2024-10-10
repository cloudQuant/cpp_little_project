cmake_minimum_required(VERSION 3.10)
project(test_mongodb LANGUAGES CXX)
# 设置C++标准为C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(test_mongodb main.cpp)
find_package(bsoncxx CONFIG REQUIRED)
target_link_libraries(test_mongodb PRIVATE $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)
find_package(mongocxx CONFIG REQUIRED)
target_link_libraries(test_mongodb PRIVATE $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)




