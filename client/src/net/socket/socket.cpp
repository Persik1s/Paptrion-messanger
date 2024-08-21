#include "../net.h"


namespace Net {
    namespace socket_n {
        RequestData LoadDataFromNetwork() {
            #if _WIN32
                WSADATA w_data;
                WORD word = MAKEWORD(2,2);
                WSAStartup(word,&w_data);
            #endif


            sockaddr_in address_in;
            address_in.sin_addr.S_un.S_addr = inet_addr(Net::client.ip);
            address_in.sin_family = AF_INET;
            address_in.sin_port = htons(Net::client.port);

            SOCKET client = socket(AF_INET,SOCK_STREAM,0);

            bool is_bind = bind(client,(sockaddr*)&address_in,sizeof(address_in));
            bool is_listen = listen(client,5);

            SOCKET is_acccpet = accept(client,0,0);

            char respone_buffer[1000];
            int size = recv(is_acccpet,respone_buffer,sizeof(respone_buffer),0);
            
            if (size < 0) {
                std::string message = {
                    "HTTP/1.1 400 Bad Request\r\n"
                    "Content-Length: 13\r\n"
                    "Content-Type: text/plain\r\n\r\n"
                    "Message: BadRequest"
                };
                                    
                send(is_acccpet, message.c_str(), message.size(), 0);

                RequestData data = RequestData {
                    std::string("Null"),
                    Net::StatusCode::StatusBadRequest
                };

                return data;
            }

            std::string message = 
            {   "HTTP/1.1 200 OK\r\n"
                "Content-Length: 6\r\n"
                "Content-Type: text/plain\r\n\r\n"
                "Message: OK"
            };
            

            send(is_acccpet, message.c_str(), message.size(), 0);

    

            #if _WIN32
                WSACleanup();
                closesocket(client);
            #elif __liunx__
                close(clinet);
            #endif
            
            RequestData data = RequestData {
                std::string(respone_buffer,size),
                Net::StatusCode::StatusOk
            };

            return data;
        }
    }
}