#include "../../api.h"

#include "../../../components/json/json.hpp"
#include <iostream>
using json = nlohmann::json;

namespace Api {
    namespace client {
        types::Member user::SignIn(types::AccountData data) {
            
            json j_data = {
                {"login",data.login.c_str()},
                {"password",data.password.c_str()},
                {"ip",data.ip.c_str()}
            };

            Net::RequestData respone = Net::request::http::NewRequest(
                Net::Methods::M_GET,
                Net::server,
                "account/sign-in",
                j_data.dump(),
                "application/json"
            );
            
            std::string respone_data = Net::request::get_request_data(respone);
        
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
                    {"name",Api::client::local_profile.name},
                    {"surname",Api::client::local_profile.surname},
                    {"username",Api::client::local_profile.username},
                    {"{age",Api::client::local_profile.age},
                }},
                {"recipient",{
                    {"name",mem.name},
                    {"surname",mem.surname},
                    {"username",mem.username},
                    {"age",mem.age},
                }}
            };
           
            Net::RequestData respone = Net::request::http::NewRequest(
                Net::Methods::M_GET,
                Net::server,
                "chat/get_list_message",
                j_data.dump(),
                "application/json"
            );
            std::string respone_data = Net::request::get_request_data(respone);
            if(Api::web::IsResponeError(respone_data.c_str()))
                return list;

            
            json object = json::parse(respone_data);
         
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

        bool user::SendMessage(types::MessageData data) {
            json j_data = {
                {"author",{
                    {"name",data.author.name},
                    {"surname",data.author.surname},
                    {"username",data.author.username},
                    {"age",data.author.age}
                }},
                {"recipient",{
                    {"name",data.recipient.name},
                    {"surname",data.recipient.surname},
                    {"username",data.recipient.username},
                    {"age",data.recipient.age}
                }},
                {"message",data.message}
            };



            Net::RequestData respone = Net::request::http::NewRequest(
                Net::Methods::M_POST,
                Net::server,
                "chat/send_message",
                j_data.dump(),
                "application/json"
            );

            return respone.status == Net::StatusCode::StatusOk;
        }
        
        void user::UpdateChatAndMessage(){
            if (Api::client::user::list_chat_block.size())
                Api::client::user::list_chat_block.clear();

            std::vector<Api::types::Member> list_chat = Api::client::GetListChat();
                           
            for(int i = 0;i < list_chat.size();i++){     
                std::vector<Api::types::MessageData> message_list = Api::client::user::GetListMessage(list_chat[i]);

                Api::types::ChatBlock data = {
                    list_chat[i],
                    message_list
                };
                Api::client::user::list_chat_block.push_back(data);
            }
        }

        types::Member user::SignUp(types::AccountBlock data) {
            json j_data = {
                {"data",{
                    {"login",data.data.login.c_str()},
                    {"password",data.data.password.c_str()},
                    {"ip",data.data.ip.c_str()}
                }},
                {"user",{
                    {"name",data.mem.name.c_str()},
                    {"surname",data.mem.surname.c_str()},
                    {"username",data.mem.username.c_str()},
                    {"age",data.mem.age}
                }},
                {"email",data.email.c_str()}
            };
    
            Net::RequestData respone = Net::request::http::NewRequest(
                Net::Methods::M_POST,
                Net::server,
                "account/sign-up",
                j_data.dump(),
                "application/json"
            );
            // std::string respone_data = Net::request::get_request_data(respone);

 
            return types::Member {
                data.mem.name.c_str(),
                data.mem.surname.c_str(),
                data.mem.username.c_str(),
                data.mem.age
            };
        }
    }
}