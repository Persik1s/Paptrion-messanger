#ifndef CLOUDE
#define CLOUDE 
#include <string>
#include <vector>

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


class Cloude {
private:

    std::string m_ip;
    int m_port;

public:
    Cloude(std::string ip,int port) : m_ip(ip), m_port(port) {}
    Cloude(){};
public:
    bool CreateFileCloude(FileData file);
    bool CreateDir(DirData dir);

    bool DeleteFile(FileData data);
    bool DeleteDir(DirData dir);

    bool WriteFile(FileData file);
    std::string ReadFile(FileData file);

    bool IsFile(FileData file);
    bool IsDir(DirData dir);


    std::vector<std::string> GetListFile(const char* path);
    std::vector<std::string> GetListDir(const char* path);
private:
    std::string get_dump_file(FileData& file);
    std::string get_dump_dir(DirData& file);
};
#endif 