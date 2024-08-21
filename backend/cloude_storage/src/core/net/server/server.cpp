#include "server.h"
#include "../../logger/logger.h"
#include <iostream>

namespace Net {
    namespace server {
        void Server::net_handler(){
            boost::asio::ip::tcp::acceptor acceptor(m_service,this->m_point);
            while(1){
                boost::asio::ip::tcp::socket socket(m_service);

                acceptor.accept(socket);
                char buffer[5500];
                int size_buffer = socket.read_some(boost::asio::buffer(buffer));
                Net::request::Request req = std::string(buffer, size_buffer);
                auto it = m_maps.find(req.get_address());
                if (it == m_maps.end()) {
                    socket.close();
                    return;
                }

                std::pair pair = it->second;
                if (pair.first != req.get_method()) {
                    socket.close();
                    return;
                }

                Logger::log.add((" NEW REQUEST " + req.get_address()).c_str());
                Net::request::Respone response = pair.second(req.get_data());
                std::string data = response.get_data();
                std::string header = "HTTP/1.1 200 OK\r\n"
                                    "Content-Type: application/json; charset=utf-8\r\n"
                                    "Content-Length: " + std::to_string(data.size()) + "\r\n\r\n";

                boost::asio::write(socket, boost::asio::buffer(header + data), Logger::log.code);
                socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
                socket.close();
            }
        }

        void Server::append_handler(std::string handler_name,request::Methods method,std::function<Net::request::Respone(std::string)> function){
            Logger::log.add("ADD HANDLER");
            this->m_maps[handler_name] = std::make_pair(method,function);
        }

        void Server::run(){
            this->m_thread.join();
        }
    }
}