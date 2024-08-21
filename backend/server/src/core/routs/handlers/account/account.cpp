#include "../handlers.h"
#include "../../../service/account/account.h"


#include "../../../logger/logger.h"
#include "../../../components/json/json.hpp"

#include <iostream>
namespace Handler {
    Net::request::Respone HandlerSignIn(std::string data){
        try {
            nlohmann::json object = nlohmann::json::parse(data);
            return {Service::account::SignIn(object),200};
        }
        catch(const std::exception& e){
           Logger::log.add("ERROR JSON PARSE");
           return {"Error json",400};
        }
    }

    Net::request::Respone HandlerSignUp(std::string data){
        try {
            std::cout << data << std::endl;
            nlohmann::json object = nlohmann::json::parse(data);
            return {Service::account::SignUp(object),200};
        }
        catch(const std::exception& e){
           Logger::log.add("ERROR JSON PARSE");
           return {"Error json",400};
        }
    }
    
}