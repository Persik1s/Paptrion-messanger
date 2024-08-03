#ifndef NET_
#define NET_
#include "../include.h"

#include "classes.h"
namespace net {
    namespace socket_n {
        RequestData LoadDataFromNetwork();
    }

    namespace request {
       inline std::string get_request_data(RequestData data) {
            std::string buffer;
            bool isRead = false;
            
            for(int i = 0;i < data.respone.size(); i++){
                if(!isRead)
                    if(data.respone[i] != '{' && data.respone[i] != '[')
                        continue;
                
                isRead = true;
                buffer+=data.respone[i];

            }
            return buffer;
        }

        namespace http {
            RequestData NewRequest(Methods method,IpAddress ip,std::string address  ,std::string data,std::string conetnt_type); 
        }
    }

    inline IpAddress client;
    inline IpAddress server;

    inline int port_client = 8081;
    inline int port_server = 8082;

}
#endif