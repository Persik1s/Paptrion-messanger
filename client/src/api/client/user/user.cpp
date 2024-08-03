#include "../../api.h"
#include "../../../components/json/json.hpp"


using json = nlohmann::json;

namespace api {
    namespace client {
        types::Member user::SignIn(types::AccountData data) {
            
            json j_data = {
                {"login",data.login},
                {"password",data.password}
            };
            net::RequestData respone = net::request::http::NewRequest(
                net::Methods::M_GET,
                net::server,
                "account/sign-in",
                j_data.dump(),
                "application/json"
            );
            std::string respone_data = net::request::get_request_data(respone);
            std::cout << respone_data << std::endl;

            json object = json::parse(respone_data);

            types::Member member = types::Member {
                object["name"],
                object["surname"],
                object["username"],
                object["age"]
            };            
            
            return member;
        }

        std::vector<types::MessageData> user::GetListMessage(types::Member mem){
            std::vector<types::MessageData> list;

            json j_data = {
                {"author", {
                    {"name",api::client::local_profile.name},
                    {"surname",api::client::local_profile.surname},
                    {"username",api::client::local_profile.username},
                    {"{age",api::client::local_profile.age},
                }},
                {"recipient",{
                    {"name",mem.name},
                    {"surname",mem.surname},
                    {"username",mem.username},
                    {"age",mem.age},
                }}
            };

            net::RequestData respone = net::request::http::NewRequest(

                net::Methods::M_GET,
                net::server,
                "chat/get_list_message",
                j_data.dump(),
                "application/json"
            );

            std::string respone_data = net::request::get_request_data(respone);
            json object = json::parse(respone_data);
            std::cout << object.size() << std::endl;

            for(int i = 0; i < object.size();i++) {
                types::Member author = {
                    object[i]["author"]["name"],
                    object[i]["author"]["surname"],
                    object[i]["author"]["username"],
                    object[i]["author"]["age"],
                };

                types::Member recipient = {
                    object[i]["recipient"]["name"],
                    object[i]["recipient"]["surname"],
                    object[i]["recipient"]["username"],
                    object[i]["recipient"]["age"],
                };

                
                types::MessageData message_data = {
                    author,
                    recipient,
                    object[i]["message"]
                };

                list.push_back(message_data);
            
            }
            return list;
        }

    }
}