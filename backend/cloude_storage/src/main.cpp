#include "core/net/net.h"
#include "core/logger/logger.h"
#include "core/handler/handler.h"




int main(void) {
    Net::server::Server server ({boost::asio::ip::make_address("127.0.0.1",Logger::log.code),8080});
    
    server.append_handler("/delete-file",Net::request::Methods::M_DELETE,Handler::HandlerDeleteFile);
    server.append_handler("/delete-dir",Net::request::Methods::M_DELETE,Handler::HandlerDeleteDir);
    server.append_handler("/create-dir",Net::request::Methods::POST,Handler::HandlerCreateDir);
    server.append_handler("/create-file",Net::request::Methods::POST,Handler::HandlerCreateFile);
    server.append_handler("/write-file",Net::request::Methods::POST,Handler::HandlerFileWrite);
    server.append_handler("/read-file",Net::request::Methods::GET,Handler::HandlerFileRead);
    server.append_handler("/is-dir",Net::request::Methods::GET,Handler::HandlerIsDir);
    server.append_handler("/is-file",Net::request::Methods::GET,Handler::HandlerIsFile);
    server.append_handler("/file-name-all",Net::request::Methods::GET,Handler::HandlerFileNameAll);
 
    server.run();
    
    getchar();
    return 0;
} 