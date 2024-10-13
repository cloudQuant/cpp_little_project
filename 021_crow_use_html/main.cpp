#include "crow.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <boost/filesystem.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/oid.hpp>
#include <mongocxx/stdx.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using mongocxx::cursor;

using namespace std;
using namespace crow;
using namespace crow::mustache;

string getView(const string &filename, crow::mustache::context &x) {
    std::string filePath = filename + ".html";
    return crow::mustache::load(filePath).render(x).body_;
}

void sendFile(response &res, string filename, string contentType){
  ifstream in("public/" + filename, ifstream::in);
  if(in){
    ostringstream contents;
    contents << in.rdbuf();
    in.close();
    res.set_header("Content-Type", contentType);
    res.write(contents.str());
  } else {
    res.code = 404;
    res.write("Not found");
  }
  res.end();
}

void sendHtml(response &res, string filename){
  sendFile(res, filename + ".html", "text/html");
}

void sendImage(response &res, string filename){
  sendFile(res, "images/" + filename, "image/jpeg");
}

void sendScript(response &res, string filename){
  sendFile(res, "scripts/" + filename, "text/javascript");
}

void sendStyle(response &res, string filename){
  sendFile(res, "styles/" + filename, "text/css");
}

int main(int argc, char* argv[]) {
    crow::SimpleApp app;
//    crow::mustache::set_base(".");
    // MongoDB Instance Initialization
    mongocxx::instance instance{};
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

// Connect to Database and Collection
    auto db = client["testdb"];
    auto collection = db["contracts"];

// Check if the collection exists, and drop it if it does
    auto collection_names = db.list_collection_names();
    if (std::find(collection_names.begin(), collection_names.end(), "contracts") != collection_names.end()) {
        db["contracts"].drop();
    }
    // Check if the file exists
    std::string filePath = "contracts.json";
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "Error: File does not exist at: " << std::filesystem::absolute(filePath) << std::endl;
        return 1;
    }
    // Read JSON file
    std::ifstream jsonFile(filePath);

    if (!jsonFile.is_open()) {
        std::cerr << "Error: Unable to open JSON file." << std::endl;
        return 1;
    }

    rapidjson::IStreamWrapper isw(jsonFile);
    rapidjson::Document jsonData;
    jsonData.ParseStream(isw);

    if (jsonData.HasParseError()) {
        std::cerr << "Error: Failed to parse JSON. Error code: " << jsonData.GetParseError() << std::endl;
        return 1;
    }

    if (!jsonData.IsArray()) {
        std::cerr << "Error: JSON data is not an array." << std::endl;
        return 1;
    }

    if (jsonData.IsArray()) {
        std::vector<bsoncxx::document::value> documents;

        for (const auto& item : jsonData.GetArray()) {
            bsoncxx::builder::basic::document doc;
            for (auto& m : item.GetObject()) {
                std::string key = m.name.GetString();

                if (m.value.IsString()) {
                    doc.append(bsoncxx::builder::basic::kvp(key, m.value.GetString()));  // Handle string values
                } else if (m.value.IsInt()) {
                    doc.append(bsoncxx::builder::basic::kvp(key, m.value.GetInt()));     // Handle integer values
                } else if (m.value.IsBool()) {
                    doc.append(bsoncxx::builder::basic::kvp(key, m.value.GetBool()));    // Handle boolean values
                } else if (m.value.IsDouble()) {
                    doc.append(bsoncxx::builder::basic::kvp(key, m.value.GetDouble()));  // Handle double values
                }
                // Add more checks here for other types like arrays, objects, etc., if needed.
            }
            documents.push_back(doc.extract());
        }

        // Insert documents in bulk into MongoDB
        collection.insert_many(documents);

        std::cout << "Documents inserted successfully!" << std::endl;
    } else {
        std::cerr << "Error: JSON data is not an array." << std::endl;
    }

  CROW_ROUTE(app, "/styles/<string>")
    ([](const request &req, response &res, string filename){
      sendStyle(res, filename);
    });

  CROW_ROUTE(app, "/scripts/<string>")
    ([](const request &req, response &res, string filename){
      sendScript(res, filename);
    });

  CROW_ROUTE(app, "/images/<string>")
    ([](const request &req, response &res, string filename){
      sendImage(res, filename);
    });

  CROW_ROUTE(app, "/about")
    ([](const request &req, response &res){
      sendHtml(res, "about");
    });

    CROW_ROUTE(app, "/contract/<string>")
      ([&collection](string email){
         auto doc = collection.find_one(make_document(kvp("email", email)));
         crow::json::wvalue dto;
         dto["contract"] = json::load(bsoncxx::to_json(doc.value().view()));
         return getView("contract", dto);
      });

  CROW_ROUTE(app, "/contracts")
    ([&collection](){
        mongocxx::options::find opts;
        opts.skip(9);  // 跳过前 9 条记录
        opts.limit(10);  // 限制返回 10 条记录
        auto docs = collection.find({}, opts);
        crow::json::wvalue dto;
          vector<crow::json::rvalue> contracts;
          contracts.reserve(10);
          for(auto doc : docs){
            contracts.push_back(json::load(bsoncxx::to_json(doc)));
          }
          dto["contracts"] = contracts;
          std::cout << contracts[0] << std::endl;
          return getView("contracts", dto);
    });

  CROW_ROUTE(app, "/")
    ([](const request &req, response &res){
      sendHtml(res, "index");
    });

  char* port = getenv("PORT");
  uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
  cout << "PORT = " << iPort << "\n";
  app.port(iPort).multithreaded().run();
}
