#ifndef NET_
#define NET_

#if _WIN32 || __linux__
    #if _WIN32
        #include <WinSock2.h>
        #pragma comment(lib,"ws2_32.lib")

    #elif __linux__
        #include <sys/socket.h>
    #endif
#endif

#include "classes.h"

namespace Net {
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
}
#endif