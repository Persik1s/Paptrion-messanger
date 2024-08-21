#include "request.h"


namespace Net {
    namespace request {  
        Request::Request(std::string data){
            this->m_request_str = data;
            this->m_data = this->init_data();
            this->m_method = this->init_method();
            this->m_address = this->init_address();
        }

        Methods Request::init_method(){
            std::string methods;
            for(const auto& v : m_request_str){
                if(v == ' ' || v == '/')
                    break;

                methods.push_back(v);
            }

            switch (methods[0])
            {
                case 'G':{
                    return Methods::GET;
                }

                case 'P':{
                    return Methods::POST;
                }

                case 'D':{
                    return Methods::M_DELETE;
                }
            }

            return Methods::M_DELETE;
        }

        std::string Request::init_data(){
            std::string r_data;
            bool parrsed = false;

            for(const auto& v : m_request_str){
                if(!parrsed)
                    if(v != '{' && v != '[')
                        continue;
                
                parrsed = true;
                r_data.push_back(v);
            }

            return r_data;
        }

        std::string Request::init_address(){
            std::string r_data;
            bool parrsed = false;
            for(const auto& v : m_request_str){
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
    }
}

