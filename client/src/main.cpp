#include <iostream>

#include "ui/ui.h"
#include "net/net.h"

#if _WIN32
    #include <Windows.h>
#elif __liunx__
    #include <pthread.h>
#endif

int main(void) {
    Net::client = {Net::InternetAddress::IpV4Address,"127.0.0.1",8081};
    Net::server = {Net::InternetAddress::IpV4Address,"127.0.0.1",8082};

    #if _WIN32
        CreateThread(0,0,(LPTHREAD_START_ROUTINE)Api::web::InputHandler,0,0,0);
    #elif __linux__
    //Create thread
    #endif


    // Api::client::user::account_data = {
    //     "janedoe",
    //     "mysecretpassword",
    //     Net::client.ip
    // };

    // // Api::client::local_profile = Api::client::user::SignIn(Api::client::user::account_data);
    // // std::vector<Api::types::Member> list_chat = Api::client::GetListChat();
                           
    // // for(int i = 0; i < list_chat.size();i++){
    // //     std::cout << list_chat[i].username << std::endl;
    // // }
                            
    
    // // for(int i = 0;i < api::client::user::list_chat.size();i++){
    // //     api::types::MessageData data = {
    // //         api::client::local_profile,
    // //         api::client::user::list_chat[i],
    // //         "hello"        
    // //     };
    // //     std::cout << api::client::user::SendMessage(data) << std::endl;

    // //     // std::cout << api::client::user::list_chat[i].name << std::endl;
    // //     // std::cout << api::client::user::list_chat[i].name << std::endl;
    // //     // std::cout << api::client::user::list_chat[i].name << std::endl;
    // //     // std::cout << api::client::user::list_chat[i].name << std::endl;
    // // }




    // // //std::cout << net::request::get_request_data(net::socket_n::LoadDataFromNetwork()) << std::endl;
    // // //std::cout << net::request::http::NewRequest(net::request::Methods::M_GET,{net::request::InternetAddress::DnsAddress,"ip-api.com"},"/json/24.48.0.1","","application/json").respone;
    // // std::cout << GetLastError() << std::endl;
    // // getchar();

    Api::client::user::account_block.data.ip = Net::client.ip;
    Api::client::user::account_data.ip = Net::client.ip;
    Ui::Core::InitGLFW();

    Ui::Core::window::Window window = Ui::Core::window::Window {
        "Patrion",
        900,
        900,
    };
    Ui::Core::InitGLAD();



    Ui::ImGui_Local::ImGuiWindow gui = Ui::ImGui_Local::ImGuiWindow {
        window,
        Ui::Gui::MainRenderPoint,
        Ui::Gui::InitComp
    };

    gui.Render();

    return 0;    
}

