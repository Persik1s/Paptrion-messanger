#include "request.h"



namespace Net {
    namespace request {
        std::string Request::init_address(std::string data){
            std::string r_data;
            bool parrsed = false;
            for(const auto& v : data){
                if(!parrsed)
                    if(v != '/')
                        continue;
                parrsed = true;
                if(v == ' ')
                    break;
                r_data.push_back(v);
            }

            return r_data;
        }
    
        std::string Request::parse_json_data(std::string data){
            for(auto it = data.begin(); it != data.end();it++){
                if(*it != '[' && *it != '{')
                    continue;
               
                return std::string(it,data.end());
            }
            Logger::log.add("ERROR JSON");
            return "None json object";
        }

        Methods Request::init_method(std::string data){
            std::string method;
            for(const auto& v :data)
                method.push_back(v);

            switch (method[0])
            {
                case 'G':
                    return Methods::GET;
                case 'P':   
                    return Methods::POST;
                case 'D':
                    return Methods::M_DELETE;
            }

            return Methods::NONE;
        }
    }
}