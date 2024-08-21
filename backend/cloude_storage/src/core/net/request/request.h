#ifndef REQUEST
#define REQURST
#include <string> 
#include <vector>
#include "../../../components/json/json.hpp"

namespace Net {
    namespace request {
        enum class Methods {
            GET,
            POST,
            M_DELETE
        };

        class Request {
        private:        
            std::string m_request_str;
            std::string m_data;
            std::string m_address;
            Methods m_method;
        public:

            Request(std::string data);
            Request(){};

        public:
            Methods get_method() {
                return this->m_method;
            }
            
            std::string get_data() {
                return this->m_data;
            }

            std::string get_address(){
                return this->m_address;
            }
        private:
            Methods init_method();
            std::string init_data();
            std::string init_address();
        };

        class Respone {
        private:
            int m_status_code;
            const char* m_data;
            std::vector<std::string> m_mass;
        private:
            std::string dump_vector() {
                nlohmann::json vec;
                for(const auto& v : m_mass)
                    vec.push_back(v);
                

                nlohmann::json object = {
                    {"Data", vec},
                    {"Code", m_status_code}
                };
                return object.dump();
            }


            std::string dump_data( ){
                nlohmann::json object = {
                    {"Data", this->m_data},
                    {"Code", this->m_status_code}
                };
                return object.dump();
            }
         public:
            Respone(const char* data,int code) {
                this->m_data = data;
                this->m_status_code = code;
                this->m_data = this->dump_data().c_str();
                
            }
            Respone(std::vector<std::string> vec,int code){
                this->m_mass = vec;
                this->m_status_code = code;
                this->m_data = this->dump_vector().c_str();
            }
            Respone(){}
        public:
            const char* get_data(){
                return this->m_data;
            }
        };
    }
}

#endif