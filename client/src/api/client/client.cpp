#include "../api.h"

#include "../../components/json/json.hpp"

using json = nlohmann::json;
namespace api {
    std::vector<types::Member> client::GetListChat(){
        std::vector<types::Member> list;
        json j_data = {
            {"login",user::account_data.login},
            {"password",user::account_data.password}
        };

        net::RequestData respone = net::request::http::NewRequest(
            net::Methods::M_GET,
            net::server,
            "account/get_list_chat",
            j_data.dump(),
            "application/json"
        );

        std::string respone_data = net::request::get_request_data(respone);
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