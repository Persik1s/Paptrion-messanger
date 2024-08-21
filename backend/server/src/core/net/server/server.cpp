#include "server.h"
#include <iostream>

namespace Net {
    namespace server {
        void Server::net_handler(){
            boost::asio::ip::tcp::acceptor accept(m_service,this->m_point);

            while(1){
                boost::asio::ip::tcp::socket socket(m_service);
                accept.accept(socket);
                char buffer[5500];
                int size = socket.read_some(boost::asio::buffer(buffer));
                request::Request  request = std::string(buffer,size);
                auto it = this->m_handlers.find(request.get_address());
                
                if(it == this->m_handlers.end()){
                    Logger::log.add_err("ERROR ADDRESS");
                    socket.close();
                    continue;
                }
                std::pair pair = it->second;
                if(pair.first != request.get_method()){
                    Logger::log.add_err("ERROR ADDRESS");
                    socket.close();
                    continue;
                }
            
                Net::request::Respone response = pair.second(request.get_data());
                std::string data = response.get_data();
                std::string header = "HTTP/1.1 200 OK\r\n"
                                    "Content-Type: application/json; charset=utf-8\r\n"
                                    "Content-Length: " + std::to_string(data.size()) + "\r\n\r\n";

                boost::asio::write(socket, boost::asio::buffer(header + data));
                socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                socket.close();
            }
        }

        void Server::append_handler(std::string name_handler,request::Methods method,std::function<request::Respone(std::string)> function){
            this->m_handlers[name_handler] = std::make_pair(method,function);
        }

        void Server::run(){
            this->m_thread.join();
        }
    }
}