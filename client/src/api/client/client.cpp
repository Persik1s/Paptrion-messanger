#include "../api.h"

#include "../../components/json/json.hpp"
#include <iostream>
using json = nlohmann::json;
namespace Api {
    std::vector<types::Member> client::GetListChat(){
        std::vector<types::Member> list;
        json j_data = {
            {"login",user::account_data.login.c_str()},
            {"password",user::account_data.password.c_str()},
            {"ip",user::account_data.ip.c_str()}
        };
         std::cout << j_data.dump() << std::endl;
        Net::RequestData respone = Net::request::http::NewRequest(
            Net::Methods::M_GET,
            Net::server,
            "account/get_list_chat",
            j_data.dump(),
            "application/json"
        );
        if(Api::web::IsResponeError(respone.respone.c_str()))
            return list;

        std::string respone_data = Net::request::get_request_data(respone);

        json object = json::parse(respone_data);
        for(int i = 0; i < object.size();i++){
            types::Member mem = types::Member {
                object[i]["name"],
                object[i]["surname"],
                object[i]["username"],
                object[i]["age"]
            };
            list.push_back(mem);
        }
        
        return list;
    }
}