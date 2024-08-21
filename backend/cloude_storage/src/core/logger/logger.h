#ifndef LOGGER
#define LOGGER

#include <vector>
#include <thread>

#include "../../components/boost/include/boost-1_84/boost/system/error_code.hpp"


namespace Logger {
    namespace types {
        class logger {
        private:
            //Error
            int m_count_errors = 0;
            std::vector<std::string> m_list_errors;

            std::string m_last_message;

            std::thread m_thread; 
        private:
            void push_error(const char* error){
                this->m_count_errors++;
                this->m_list_errors.push_back(error);
                this->m_last_message = error;
            }

            void handler(){
                while(1){
                    //std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(!this->m_last_message.empty())
                        printf("[LOGGER] -> %s\n",this->m_last_message.c_str()),this->m_last_message.clear();
                
                    if(this->code)
                        this->add_error(this->code),this->code.clear();
                }
            }
        public:
            logger() : m_thread(&logger::handler,this) {}
            
            ~logger() {
                this->m_thread.join();
            }
            void add_error(boost::system::error_code code){
                this->push_error(code.message().c_str());
            }

            void add_error(const char* error){
                this->push_error(error);
            }

            void add(const char* log){
                this->m_last_message = log;
            }

            const char* get_last_error(){
                if(!this->m_list_errors.empty())
                    return this->m_list_errors.back().c_str();
                return nullptr;
            }
            int get_count(){
                return this->m_count_errors;
            }
        public:
            boost::system::error_code code;
        };
    }


    inline types::logger log;
}




#endif