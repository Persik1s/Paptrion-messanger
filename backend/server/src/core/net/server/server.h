#ifndef SERVER
#define SERVER

#include <map>
#include <functional>
#include <thread>
#include "../request/request.h"
#include "../../../components/boost/include/boost-1_84/boost/asio.hpp"

namespace Net {
    namespace server {
        class Server {
        private:
            boost::asio::ip::tcp::endpoint m_point;
            boost::asio::io_service m_service;
            std::unordered_map<std::string,std::pair<request::Methods,std::function<request::Respone(std::string)>>> m_handlers;
            std::thread m_thread;

        private:
            void net_handler();
        public:
            Server(boost::asio::ip::tcp::endpoint end) : m_point(end), m_thread(&Server::net_handler,this) {}
            

            void append_handler(std::string name_handler,request::Methods method,std::function<request::Respone(std::string)> function);
            void run(); 
        };
    }
}

#endif