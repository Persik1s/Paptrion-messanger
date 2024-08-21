/*

 ________  ___       ________  ___  ___  ________  _______      
|\   ____\|\  \     |\   __  \|\  \|\  \|\   ___ \|\  ___ \     
\ \  \___|\ \  \    \ \  \|\  \ \  \\\  \ \  \_|\ \ \   __/|    
 \ \  \    \ \  \    \ \  \\\  \ \  \\\  \ \  \ \\ \ \  \_|/__  
  \ \  \____\ \  \____\ \  \\\  \ \  \\\  \ \  \_\\ \ \  \_|\ \ 
   \ \_______\ \_______\ \_______\ \_______\ \_______\ \_______\
    \|_______|\|_______|\|_______|\|_______|\|_______|\|_______|
                                                                
                                                            
*/


#if _WIN32 || __linux__
    #if _WIN32
        #include <WinSock2.h>
        #pragma comment(lib,"ws2_32.lib")

    #elif __linux__
        #include <sys/socket.h>
    #endif
#endif

#include "cloude.h"
#include "tools/json.hpp"

namespace Net{
    std::string get_data(std::string& data);
    std::string new_requset(std::string method,std::string address,std::string ip,int32_t port ,std::string type,std::string data);

    struct Respone {
        std::string respone;
        int32_t code;
        Respone(std::string data){
            nlohmann::json object = nlohmann::json::parse(data);
            this->respone = object["Data"];
            this->code = object["Code"];
        }
    };
}


bool Cloude::CreateFileCloude(FileData file){
    std::string dump = this->get_dump_file(file);
    Net::Respone data = Net::new_requset("POST","create-file",this->m_ip,this->m_port,"application/json",dump);
    return data.code == 200;
}

bool Cloude::CreateDir(DirData dir){
    std::string dump = this->get_dump_dir(dir);
    Net::Respone data = Net::new_requset("POST","create-dir",this->m_ip,this->m_port,"application/json",dump);
    return data.code == 200;
}

bool Cloude::DeleteFile(FileData file){
    std::string dump = this->get_dump_file(file);
    Net::Respone data = Net::new_requset("DELETE","delete-file",this->m_ip,this->m_port,"application/json",dump);
    return data.code == 200;
}
bool Cloude::DeleteDir(DirData dir){
    std::string dump = this->get_dump_dir(dir);
    Net::Respone data = Net::new_requset("DELETE","delete-dir",this->m_ip,this->m_port,"application/json",dump);
    return data.code  == 200;
}

bool Cloude::IsFile(FileData file) {
    std::string dump = this->get_dump_file(file);
    Net::Respone data = Net::new_requset("GET","is-file",this->m_ip,this->m_port,"application/json",dump);
    return strstr(data.respone.c_str(),"True");
}

bool Cloude::IsDir(DirData dir) {
    std::string dump = this->get_dump_dir(dir);
    Net::Respone data = Net::new_requset("GET","is-dir",this->m_ip,this->m_port,"application/json",dump);
    return strstr(data.respone.c_str(),"True");
}

bool Cloude::WriteFile(FileData file){
    std::string dump = this->get_dump_file(file);
    Net::Respone data = Net::new_requset("POST","write-file",this->m_ip,this->m_port,"application/json",dump);
    return data.code == 200; 
}

std::string Cloude::ReadFile(FileData file){
    std::string dump = this->get_dump_file(file);
    Net::Respone data = Net::new_requset("POST","read-file",this->m_ip,this->m_port,"application/json",dump);
    return data.respone; 
}

std::vector<std::string> Cloude::GetListFile(const char* path){
    nlohmann::json object =  {
        {"path",path}
    }; 
    Net::Respone data = Net::new_requset("GET","file-name-all",this->m_ip,this->m_port,"application/json",object.dump());

    std::vector<std::string> list;
    nlohmann::json respone = nlohmann::json::parse(data.respone);
    for(int i = 0; i < respone.size();i++)
        list.push_back(respone[i]);
    
    return list;
}

std::vector<std::string> Cloude::GetListDir(const char* path){
    nlohmann::json object =  {
        {"path",path}
    }; 
    Net::Respone data = Net::new_requset("GET","dir-name-all",this->m_ip,this->m_port,"application/json",object.dump());

    std::vector<std::string> list;
    nlohmann::json respone = nlohmann::json::parse(data.respone);
    for(int i = 0; i < respone.size();i++)
        list.push_back(respone[i]);
    
    return list;
}

 std::string Cloude::get_dump_file(FileData& file){
    nlohmann::json object = {
        {"path", file.file_path},
        {"type", file.file_type},
        {"name", file.file_name}
    };
    return object.dump();
 }

std::string Cloude::get_dump_dir(DirData& dir){
    nlohmann::json object = {
        {"path", dir.dir_path},
        {"name", dir.dir_name}
    };
    return object.dump();
 }

namespace Net {
    std::string get_data(std::string& respone){
        std::string buffer;
        bool isRead = false;
            
        for(int i = 0;i < respone.size(); i++){
            if(!isRead)
                if(respone[i] != '{' && respone[i] != '[')
                    continue;
                
            isRead = true;
            buffer+=respone[i];

        }
        return buffer;
    }
    std::string new_requset(std::string method,std::string address,std::string ip,int32_t port ,std::string type,std::string data){
        #if _WIN32
            WSADATA w_data;
            WORD word = MAKEWORD(2,2);
            WSAStartup(word,&w_data);
        #endif

        sockaddr_in sock_address;
        sock_address.sin_family = AF_INET;

        sock_address.sin_port   =  htons(port);
        sock_address.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

            
        SOCKET client = socket(AF_INET,SOCK_STREAM,0);

        int is_connect = connect(client,(sockaddr*)&sock_address,sizeof(sock_address));
                
        std::string send_data;
              
                
                std::string header = method + " /" + address + " HTTP/1.0\n" +
                         "Host: " + ip + ":" + std::to_string(port) + "\n" +
                         "Content-Type: " + type + "; charset=utf-8\n" +
                         "Content-Length: " + std::to_string(data.size()) + "\r\n\r\n";

                send_data+= header + data;

                int is_send = send(client,send_data.c_str(),send_data.size(),0);
                char respone_buffer[65535];

                int size = recv(client,respone_buffer,sizeof(respone_buffer),0);
               
                #if _WIN32
                    WSACleanup();
                    closesocket(client);
                #elif __liunx__
                    close(clinet);
                #endif
                
                return Net::get_data(std::string(respone_buffer,size));        
        
    }
}