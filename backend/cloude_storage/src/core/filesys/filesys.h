#ifndef FILESYSTEM
#define FILESYSTEM
#include <vector>
#include <string>
namespace Filesystem {
    namespace type {
        struct FileData {
            std::string file_name;
            std::string file_path;
            std::string file_type;

            FileData(std::string file_name,std::string file_path, std::string file_type) :
                file_name(file_name), file_path(file_path), file_type(file_type) {}
        };

        struct DirData {
            std::string dir_name;
            std::string dir_path;

            DirData(std::string  dir_name, std::string dir_path ) :
                dir_name(dir_name), dir_path(dir_path) {}
        };
    }
    
    
    void write_file(type::FileData& file,const char* data);
    const char* read_file(type::FileData& file);

    void create_file(type::FileData& file);
    void create_dir(type::DirData& dir);

    void delete_dir(type::DirData& dir);
    void delete_file(type::FileData& file);

    bool is_file(type::FileData& file);
    bool is_dir(type::DirData& dir);

    std::vector<std::string> list_name_file(const char* path);
    std::vector<std::string> list_name_dir(const char* path);
}
#endif