#include "routs.h"
#include "../net/server/server.h"
#include "handlers/handlers.h"
namespace Rout {
    void Init(){
        Net::server::Server server({boost::asio::ip::make_address("127.0.0.1"),8081});
        
        server.append_handler("/sign-in",Net::request::Methods::GET,  Handler::HandlerSignIn);
        server.append_handler("/sign-up",Net::request::Methods::POST, Handler::HandlerSignUp);
   
    
        server.run();
    }
}

