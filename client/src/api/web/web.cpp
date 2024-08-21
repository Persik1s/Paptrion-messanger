#include "../api.h"
#include "../../components/json/json.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

namespace Api {
    namespace web {
        bool IsResponeError(const char* data ) {
            for(auto& l : request::error::error_list)
                if(strstr(data,l))
                    return 1;
                
            return 0;
        }   

        void InputHandler() {
            while(true) {
                Net::RequestData respone = Net::socket_n::LoadDataFromNetwork();
                std::string data = Net::request::get_request_data(respone);

                json object = json::parse(data);
                if (object["Event"] == "NEW_MESSAGE")
                    Api::client::user::UpdateChatAndMessage();
            }
        }
    }
}

