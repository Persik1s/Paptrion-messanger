#include "service.h"
#include "../filesys/filesys.h"


namespace Service {
    void DeleteDirCloude(nlohmann::json&  json){
        Filesystem::type::DirData dir = {
            json["name"],
            json["path"]
        };
        Filesystem::delete_dir(dir);
    }

    void DeleteFileCloude(nlohmann::json& json){
        Filesystem::type::FileData file = {
            json["name"],
            json["path"],
            json["type"]
        };
        Filesystem::delete_file(file);
    }

    void CreateFileCloude(nlohmann::json&  json){
        Filesystem::type::FileData file = {
            json["name"],
            json["path"],
            json["type"]
        };
        Filesystem::create_file(file);
    }

    void CreateDirCloude(nlohmann::json&  json){
        Filesystem::type::DirData dir = {
            json["name"],
            json["path"]
        };
        Filesystem::create_dir(dir);
    }

    std::string ReadFileCloude(nlohmann::json&  json){
        Filesystem::type::FileData file = {
            json["name"],
            json["path"],
            json["type"]
        };

        return Filesystem::read_file(file);
    }
    void WriteFileCloude(nlohmann::json&  json){
        Filesystem::type::FileData file = {
            json["name"],
            json["path"],
            json["type"]
        };
        std::string data = json["data"];

        Filesystem::write_file(file,data.c_str());
    }
    bool IsFileCloude(nlohmann::json&  json){
        Filesystem::type::FileData file = {
            json["name"],
            json["path"],
            json["type"]
        };
        return Filesystem::is_file(file);
    }
    bool IsDirCloude(nlohmann::json&  json){
        Filesystem::type::DirData dir = {
            json["name"],
            json["path"]
        };
        return Filesystem::is_dir(dir);       
    }
    std::vector<std::string> ListNameFileAll(nlohmann::json&  json){
        return Filesystem::list_name_file(std::string(json["path"]).c_str());
    }

    std::vector<std::string> ListNameDirAll(nlohmann::json& json){
        return Filesystem::list_name_dir(std::string(json["path"]).c_str());
    }
}