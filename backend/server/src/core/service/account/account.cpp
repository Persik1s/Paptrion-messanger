#include "account.h"
#include "../model.h"
#include "../../model/repository/repository.h"
#include <iostream>

namespace Service {
    namespace account {
        std::string SignIn(nlohmann::json object){
            EntiyService::UserCreds auth = {
                object["login"],
                object["password"]
            };
            EntiyService::HashKey key = md5((auth.login + auth.password).c_str());

            bool isModel = Model::repository::account::IsAccount(key.key);
            if(!isModel)
                return "ERROR ACCOUNT";

            auto data = Model::repository::account::SelectDataAccount(key.key);
            std::cout << key.key << " " << data.name << std::endl;
            nlohmann::json data_object = {
                {"name",data.name},
                {"surname",data.surname},
                {"username",data.username},
                {"age",data.age}
            };    
            return data_object.dump();
        }

        std::string SignUp(nlohmann::json object) {
            EntiyService::UserCreds auth = {
                object["data"]["login"],
                object["data"]["password"]
            };
            std::cout << auth.login << " " << auth.password << std::endl;
            EntiyService::HashKey key = md5((auth.login + auth.password).c_str());

            bool isModel = Model::repository::account::IsAccount(key.key);
            if(isModel)
                return "Account exists";

            EntiyService::UserAuthData data_auth = {
                {
                    object["user"]["name"],
                    object["user"]["surname"],
                    object["user"]["username"],
                    object["user"]["age"]
                },
                {
                    object["data"]["login"],
                    object["data"]["password"]
                },
                object["ip"]
            };
            
            bool is_insert = Model::repository::account::InsertAccount(
                {{
                    data_auth.user.name,
                    data_auth.user.surname,
                    data_auth.user.username,
                    data_auth.user.age
                },
                {
                    data_auth.data.login,
                    data_auth.data.password
                },
                data_auth.ip},
                key.key
            );
            
            return is_insert? "Succeful create account" : "Error create account";
        }
    }
}