#ifndef HANDLER
#define HANDLER
#include <string>
#include "../net/net.h"
namespace Handler {
    Net::request::Respone HandlerDeleteFile(std::string data);
    Net::request::Respone HandlerDeleteDir(std::string data);

    Net::request::Respone HandlerFileRead(std::string data);
    Net::request::Respone HandlerFileWrite(std::string data);

    Net::request::Respone HandlerCreateFile(std::string data);
    Net::request::Respone HandlerCreateDir(std::string data);

    Net::request::Respone HandlerIsFile(std::string data);
    Net::request::Respone HandlerIsDir(std::string data);

    Net::request::Respone HandlerFileNameAll(std::string data);
    Net::request::Respone HandlerDirNameAll(std::string data);
}
#endif 