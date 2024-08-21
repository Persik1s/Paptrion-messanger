#include <vector>
#include <iostream>
#include "handler.h"
#include "../logger/logger.h"
#include "../../components/json/json.hpp"
#include "../service/service.h"

using json = nlohmann::json;
namespace Handler {
    Net::request::Respone HandlerDeleteFile(std::string data){
        try
        {
            json object = json::parse(data);
            Service::DeleteFileCloude(object);
            return {"OK",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerDeleteDir(std::string data){
        try
        {
            json object = json::parse(data);
            Service::DeleteDirCloude(object);
            return {"OK",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerCreateDir(std::string data){
        try
        {
            json object = json::parse(data);
            Service::CreateDirCloude(object);
            return {"OK",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }
    Net::request::Respone HandlerCreateFile(std::string data){
        try
        {
            json object = json::parse(data);
            Service::CreateFileCloude(object);
            return {"OK",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerFileRead(std::string data){
        try
        {
            json object = json::parse(data);
            auto data = Service::ReadFileCloude(object);
            return {data.c_str(),200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerFileWrite(std::string data){
        try
        {
            json object = json::parse(data);
            Service::WriteFileCloude(object);
            return {"OK",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }
    Net::request::Respone HandlerIsFile(std::string data){
        try
        {
            json object = json::parse(data);
            bool is = Service::IsFileCloude(object);
            return {is? "True" : "False",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerIsDir(std::string data){
        try
        {
            json object = json::parse(data);
            bool is = Service::IsDirCloude(object);
            return {is? "True" : "False",200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }

    Net::request::Respone HandlerFileNameAll(std::string data){
        try
        {
            json object = json::parse(data);
            return {Service::ListNameFileAll(object),200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }
    Net::request::Respone HandlerDirNameAll(std::string data){
        try
        {
            json object = json::parse(data);
            return {Service::ListNameDirAll(object),200};
        }
        catch(const std::exception& e){
            Logger::log.add("ERROR PARSED JSON");
            return {"Error parrsed json",400};
        }
    }
}