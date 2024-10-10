### mac上使用下面指令编译：
g++ main.cpp -o main $(pkg-config --cflags --libs libmongocxx) --std=c++11