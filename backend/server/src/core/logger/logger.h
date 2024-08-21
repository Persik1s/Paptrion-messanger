#ifndef LOGGER 
#define LOGGER 

#include <thread>
#include <string>
#include "../../components/boost/include/boost-1_84/boost/system/error_code.hpp"

namespace Logger {
    namespace types {
        class logger {
        public:
            logger() : m_thread(&logger::handler,this) {} 
        private:
            std::thread m_thread;
            int m_count_error;
            
            std::vector<std::string> m_list_error;
            std::string m_last_messge;

        public:
            std::vector<std::string> get_list_error(){
                return this->m_list_error;
            }

            void add_err(const char* error){
                this->push_error(error);
            }

            void add_err(boost::system::error_code error) {
                this->push_error(error.message().c_str());
            }
            void add(const char* message) {
                this->m_last_messge = message;
            }

            std::string get_last_error(){
                this->m_list_error.back();
            }
            ~logger(){
                this->m_thread.join();
            }
        private:
            void push_error(const char* error){
                this->m_count_error++;
                this->m_list_error.push_back(error);
                this->m_last_messge = error;
            }
            void handler( ){
                while(1){
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if(!this->m_last_messge.empty()){
                        printf("[LOGGER ] -> %s\n",this->m_last_messge.c_str());
                        this->m_last_messge.clear();
                    }
                }
            }
        };
    }

    inline types::logger log;
}

#endif