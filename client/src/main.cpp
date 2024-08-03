#include "net/net.h"

int main() {
    net::ip_client = "127.0.0.1";
 
    std::cout << net::socket_n::LoadDataFromNetwork().respone << std::endl;
    //std::cout << net::request::http::NewRequest(net::request::Methods::M_GET,{net::request::InternetAddress::DnsAddress,"ip-api.com"},"/json/24.48.0.1","","application/json").respone;
    
    getchar();
    return 0;    
}