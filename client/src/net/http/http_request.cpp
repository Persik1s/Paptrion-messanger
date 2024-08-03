#include "../net.h"

namespace net {
    namespace request {
        namespace http {
            RequestData NewRequest(Methods method,IpAddress ip,std::string address ,std::string data,std::string conetnt_type){
                #if _WIN32
                    WSADATA w_data;
                    WORD word = MAKEWORD(2,2);
                    WSAStartup(word,&w_data);
                #endif

                sockaddr_in sock_address;
                sock_address.sin_family = AF_INET;

                switch (ip.type)
                {
                    case InternetAddress::IpV4Address:{
                        sock_address.sin_port   =  htons(ip.port);
                        sock_address.sin_addr.S_un.S_addr = inet_addr(ip.ip);
                        break;
                    }
                    case InternetAddress::DnsAddress:{
                        struct hostent* host;
                        host = gethostbyname(ip.ip);
                        sock_address.sin_port = htons(80);
                        sock_address.sin_addr = *((LPIN_ADDR)*host->h_addr_list);
                        break;
                    }
                }
            
                SOCKET client = socket(AF_INET,SOCK_STREAM,0);

                int is_connect = connect(client,(sockaddr*)&sock_address,sizeof(sock_address));
                
                std::string send_data;
                switch (method)
                {  
                    case Methods::M_GET: {
                        send_data += "GET";
                        break;
                    }

                    case Methods::M_POST: {
                        send_data += "POST";
                        break;
                    }

                    case Methods::M_DELETE: {
                        send_data += "DELETE";
                        break;
                    }
                }            
                
                std::string header = " /" + address + " HTTP/1.0\n" +
                         "Host: " + ip.ip + ":" + std::to_string(ip.port) + "\n" +
                         "Content-Type: " + conetnt_type + "; charset=utf-8\n" +
                         "Content-Length: " + std::to_string(data.size()) + "\r\n\r\n";

                send_data+= header + data;

                int is_send = send(client,send_data.c_str(),send_data.size(),0);
                char respone_buffer[1000];

                int size = recv(client,respone_buffer,sizeof(respone_buffer),0);
                
                RequestData respone = RequestData {
                    std::string(respone_buffer,size),
                    StatusCode::StatusOk
                };

                #if _WIN32
                    WSACleanup();
                    closesocket(client);
                #elif __liunx__
                    close(clinet);
                #endif
                
                return respone;
            } 
        } 
    }
}