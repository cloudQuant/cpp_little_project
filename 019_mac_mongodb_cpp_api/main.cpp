#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <iostream>

int main() {
    // MongoDB实例
    mongocxx::instance instance{};
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

    // 连接到数据库和集合
    auto db = client["testdb"];
    auto collection = db["testcollection"];

    // 构建一个文档
    bsoncxx::builder::stream::document document{};
    document << "name" << "MongoDB"
             << "type" << "database"
             << "count" << 1;

    // 插入文档
    collection.insert_one(document.view());

    std::cout << "Document inserted successfully!" << std::endl;

    return 0;
}
