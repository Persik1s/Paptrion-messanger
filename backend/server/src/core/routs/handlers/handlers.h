#ifndef HANDLER_ROUTS
#define HANDLER_ROUTS
#include "../../net/request/request.h"

namespace Handler {
    Net::request::Respone HandlerSignIn(std::string data);
    Net::request::Respone HandlerSignUp(std::string data);
    //Net::request::Respone HandlerChat(std::string data);
}

#endif