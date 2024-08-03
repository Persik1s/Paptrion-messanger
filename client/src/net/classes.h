#ifndef CLASSES_
#define CLASSES_
#include <string>
namespace net {
    enum class StatusCode {
        StatusOk,
        StatusBadRequest
    };

    enum class Methods {
        M_GET,
        M_DELETE,
        M_POST
    };

    enum class InternetAddress  {
        IpV4Address,
        DnsAddress
    };

    class IpAddress {
    public:
        const char* ip;
        int port;
        InternetAddress type;

        IpAddress(InternetAddress type,const char* ip , int port = 80) {
            this->ip = ip;
            this->type = type;
            this->port = port;
        }
        
    };

    class RequestData {
    public:
        std::string respone;
        StatusCode status;
        RequestData(std::string respone,StatusCode code) {
            this->respone = respone;
            this->status = code;
        }
    };
}

#endif