#include "net/net.h"
#include "api/api.h"
int main() {
    net::client = {net::InternetAddress::IpV4Address,"127.0.0.1",8081};
    net::server = {net::InternetAddress::IpV4Address,"127.0.0.1",8082};

    api::client::user::account_data = {
        "janedoe",
        "mysecretpassword"
    };

    api::client::local_profile = api::client::user::SignIn(api::client::user::account_data);
    api::client::user::list_chat = api::client::GetListChat();
    for(int i = 0;i < api::client::user::list_chat.size();i++){
        std::cout << api::client::user::GetListMessage(api::client::user::list_chat[i])[i].message << std::endl;
    }




    //std::cout << net::request::get_request_data(net::socket_n::LoadDataFromNetwork()) << std::endl;
    //std::cout << net::request::http::NewRequest(net::request::Methods::M_GET,{net::request::InternetAddress::DnsAddress,"ip-api.com"},"/json/24.48.0.1","","application/json").respone;
    std::cout << GetLastError() << std::endl;
    getchar();
    return 0;    
}