#ifndef NET_
#define NET_
#include "../include.h"
#include "classes.h"

namespace net {
    namespace socket_n {
        RequestData LoadDataFromNetwork();
    }

    namespace request {
        namespace http {
            RequestData NewRequest(Methods method,IpAddress ip,std::string address  ,std::string data,std::string conetnt_type); 
        }
    }

    
    inline const char* ip_client;
    inline const char* ip_server;

    inline int port_client = 8081;
    inline int port_server = 8082;

}
#endif