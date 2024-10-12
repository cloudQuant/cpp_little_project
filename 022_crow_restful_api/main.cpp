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


void getView(response &res, const string &filename, context &x) {
    res.set_header("Content-Type", "text/html");
    std::string filePath = filename + ".html";
    auto text = crow::mustache::load(filePath).render(x).body_;
    res.write(text);
    res.end();
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

void notFound(response &res, const string &message){
    res.code = 404;
    res.write(message + ": Not Found");
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
            bsoncxx::builder::stream::document doc;
            for (auto& m : item.GetObject()) {
                std::string key = m.name.GetString();

                if (m.value.IsString()) {
                    doc << key << m.value.GetString();  // Handle string values
                } else if (m.value.IsInt()) {
                    doc << key << m.value.GetInt();     // Handle integer values
                } else if (m.value.IsBool()) {
                    doc << key << m.value.GetBool();    // Handle boolean values
                } else if (m.value.IsDouble()) {
                    doc << key << m.value.GetDouble();  // Handle double values
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
      ([&collection](const request &req, response &res, string email){
         auto doc = collection.find_one(make_document(kvp("email", email)));
         crow::json::wvalue dto;
         dto["contract"] = json::load(bsoncxx::to_json(doc.value().view()));
         return getView(res, "contract", dto);
      });

    CROW_ROUTE(app, "/contract/<string>/<string>")
      ([&collection](const request &req, response &res, string firstname, string lastname){
        auto doc = collection.find_one(
          make_document(kvp("firstName", firstname), kvp("lastName", lastname)));
        if(!doc){
          return notFound(res, "Contract");
        }
        crow::json::wvalue dto;
        dto["contract"] = json::load(bsoncxx::to_json(doc.value().view()));
        getView(res, "contract", dto);
      });

    CROW_ROUTE(app, "/add/<string>/<string>")
   ([](const request &req, response &res, string a, string b){
       res.set_header("Content-Type","text/plain");
       ostringstream os;
       os << "String: " << a << " + " << b << " = " << a + b << "\n";
       res.write(os.str());
       res.end();
   });

    CROW_ROUTE(app, "/add/<int>/<int>")
    ([](const request &req, response &res, int a, int b){
        res.set_header("Content-Type","text/plain");
        ostringstream os;
        os << "Integer: " << a << " + " << b << " = " << a + b << "\n";
        res.write(os.str());
        res.end();
    });

    CROW_ROUTE(app, "/add/<double>/<double>")
     ([](const request &req, response &res, double a, double b){
         res.set_header("Content-Type","text/plain");
         ostringstream os;
         os << "Double: " << a << " + " << b << " = " << a + b << "\n";
         res.write(os.str());
         res.end();
     });

  CROW_ROUTE(app, "/contracts")
    ([&collection](const request &req, response &res){
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
          return getView(res, "contracts", dto);
    });

    CROW_ROUTE(app, "/api/contracts")
    ([&collection](const request &req){
      auto skipVal = req.url_params.get("skip");
      auto limitVal = req.url_params.get("limit");
      int skip = skipVal? stoi(skipVal): 0;
      int limit = limitVal? stoi(limitVal): 10;

      mongocxx::options::find opts;
      opts.skip(skip);
      opts.limit(limit);
      auto docs = collection.find({}, opts);
      vector<crow::json::rvalue> contracts;
      contracts.reserve(10);

      for(auto doc : docs){
        contracts.push_back(json::load(bsoncxx::to_json(doc)));
      }
      crow::json::wvalue dto;
      dto["contracts"] = contracts;
      return crow::response{dto};
    });

    CROW_ROUTE(app, "/query")
      ([](const request &req, response &res){
        auto firstname = req.url_params.get("firstname");
        auto lastname = req.url_params.get("lastname");
        ostringstream os;
        os << "Hello "<< (firstname? firstname: "") <<
          " " << (lastname? lastname: "") << endl;
        res.set_header("Content-Type", "text/plain");
        res.write(os.str());
        res.end();
      });

   CROW_ROUTE(app, "/rest_test").methods(HTTPMethod::Post, HTTPMethod::Get,
       HTTPMethod::Put)
         ([](const request &req, response &res){
           string method = method_name(req.method);
           res.set_header("Content-Type", "text/plain");
           res.write(method + " rest_test");
           res.end();
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
