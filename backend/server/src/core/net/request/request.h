#ifndef REQUEST
#define REQUEST
#include <string>

#include "../../../components/json/json.hpp"
#include "../../logger/logger.h"

namespace Net {
    namespace request {
        enum class Methods  {
            GET,
            POST,
            M_DELETE,
            NONE
        };

        class Request {
        private:
            Methods m_method;
            std::string m_address;
            std::string m_data;
        private:
            std::string parse_json_data(std::string data);
            std::string init_address(std::string data);
            Methods init_method(std::string data);
        public:
            Request(std::string data){
                this->m_address = this->init_address(data);
                this->m_method = this->init_method(data);
                this->m_data = this->parse_json_data(data);
            }

            std::string get_data(){
                return this->m_data;
            }
            
            std::string get_address(){
                return this->m_address;
            }

            Methods get_method(){
                return this->m_method;
            }
        };

        class Respone {
        private:
            std::string m_str_dump;
        private:
            std::string get_dump_data(std::string str,int code){
                nlohmann::json object = {
                    {"Data",str},
                    {"Code",code}
                };
                return object.dump();
            }
        public:
            Respone(std::string data,int code){
                this->m_str_dump = this->get_dump_data(data,code);
            }
            std::string get_data(){
                return this->m_str_dump; 
            }
        };
    }
}

#endif