#ifndef SERVER 
#define SERVER
#include <functional>
#include <thread>
#include <map>

#include "../net.h"
#include "../../../components/boost/include/boost-1_84/boost/asio.hpp"


namespace Net {
    namespace server {
        class Server {
        private:
            boost::asio::ip::tcp::endpoint m_point;     
           std::unordered_map<std::string, std::pair<request::Methods, std::function<Net::request::Respone(std::string)>>> m_maps;
            std::thread m_thread;
            boost::asio::io_service m_service;
        private:
        
            void net_handler();
        public:
        
            Server(boost::asio::ip::tcp::endpoint end) : m_point(end), m_thread(&Server::net_handler,this) {}
        public:

            void append_handler(std::string handler_name,request::Methods method,std::function<Net::request::Respone(std::string)> function);
            void run();
        };
    }
}

#endif 