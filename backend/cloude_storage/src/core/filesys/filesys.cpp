#include <fstream>
#include <filesystem>

#include "filesys.h"
#include "../logger/logger.h"
namespace Filesystem {
    void write_file(type::FileData& file,const char* data){
        std::string f = file.file_path + std::string("/") + file.file_name + file.file_type;
        std::string read_file = Filesystem::read_file(file);
        std::filesystem::path path(f.c_str());
        std::ofstream file_obejct(path.string());
        file_obejct << read_file + data << std::endl;
        file_obejct.close();
        Logger::log.add(f.c_str());
    }

    const char* read_file(type::FileData& file){
        std::string f = file.file_path + std::string("/") + file.file_name + file.file_type;
        std::filesystem::path path(f.c_str());   
        std::ifstream file_object(path.string());
        std::string buffer,content;
        while(std::getline(file_object,buffer)){
            content += buffer + '\n';
        }
        Logger::log.add(f.c_str());
        return content.c_str();
    }

    void delete_file(type::FileData& file){
        std::string f = file.file_path + std::string("/") + file.file_name + file.file_type;
        std::filesystem::path path(f.c_str());
        if(!std::filesystem::exists(path))
            return;

        Logger::log.add(f.c_str());
        std::filesystem::remove(path);
    }

    void delete_dir(type::DirData& dir) {
        std::string f = dir.dir_path + std::string("/") + dir.dir_name;
        std::filesystem::path path(f.c_str());
        if(!std::filesystem::exists(path) || !std::filesystem::is_directory(path))
            return;

        Logger::log.add(f.c_str());
        std::filesystem::remove(path);
    }


    void create_dir(type::DirData& dir){
        std::string f = dir.dir_path + std::string("/") + dir.dir_name;
        std::filesystem::path path(f.c_str());
        if(std::filesystem::exists(path) && std::filesystem::is_directory(path))
            return;

        Logger::log.add(f.c_str());
        std::filesystem::create_directory(path); 
    } 

    void create_file(type::FileData& file){
        std::string f = file.file_path + std::string("/") + file.file_name + file.file_type;
        std::filesystem::path path(f.c_str());
        if(std::filesystem::exists(path))
            return;

        
        std::ofstream file_object(path.string());        
        file_object.is_open();
        file_object.close();
        Logger::log.add(f.c_str());
    }   

    bool is_file(type::FileData& file){
        std::string f = file.file_path + std::string("/") + file.file_name + file.file_type;
        std::filesystem::path path(f.c_str());
        Logger::log.add(f.c_str());
        return std::filesystem::exists(path);
    }

    bool is_dir(type::DirData& dir){
        std::string f = dir.dir_path + std::string("/") + dir.dir_name;
        std::filesystem::path path(f.c_str());
        Logger::log.add(f.c_str());
        return std::filesystem::exists(path);
    }

    std::vector<std::string> list_name_file(const char* path) {
        std::filesystem::path p(path);
        if (!std::filesystem::exists(p) || !std::filesystem::is_directory(p)) {
            return {};
        }
        std::vector<std::string> file_names;
        for (const auto& entry : std::filesystem::directory_iterator(p)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                file_names.push_back(entry.path().filename().string().c_str());
            }
        }
        return file_names;
    }
    std::vector<std::string> list_name_dir(const char* path){
        std::filesystem::path p(path);
        
        if(!std::filesystem::exists(p) || std::filesystem::is_directory(p)){
            return {};
        }
        std::vector<std::string> dir_name;
        for(const auto& entry : std::filesystem::directory_iterator(p)){
            if(std::filesystem::is_directory(entry.path())){
                dir_name.push_back(entry.path().filename().string().c_str());
            }
        }
        return dir_name;
    } 
}