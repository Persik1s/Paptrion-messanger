
#include <vector> 

#include "../../components/fonts/font.h"
#include "../ui.h"

#include <iostream>
char buffer[25];

namespace Ui {
    namespace Gui {
        namespace Menu {
            void Draw (){
                switch (Api::client::user::status)
                {
                    case Api::types::STATUS_CLIENT::SIGN_IN:{
                        Ui::Draw::Components::TextDraw("P",Ui::Gui::unisans_bold_italic,144,ImColor(255,255,255,255),{286,78});
                        
                        Ui::Draw::Components::InputText("Login",Api::client::user::account_data.login.data(),Api::client::user::account_data.login.capacity(),{285,37},{163,284},{71,71,71,255},5);
                        Ui::Draw::Components::InputText("Password",Api::client::user::account_data.password.data(),Api::client::user::account_data.password.capacity(),{285,37},{163,342},{71,71,71,255},5);

                        bool pressed_button_1 = Ui::Draw::Components::ButtonDraw("Login",Ui::Gui::inter_medium,18,ImColor(0,173,69,255),{163,31},{284,37},14);
                        if(pressed_button_1){
                            
                            Api::client::local_profile = Api::client::user::SignIn(Api::client::user::account_data);
                            Api::client::user::UpdateChatAndMessage();
                            
                            Api::client::user::status = Api::types::STATUS_CLIENT::LOGI_IN;
                        }
                        bool pressed_button_2 = Ui::Draw::Components::ButtonDraw("Sign Up",Ui::Gui::inter_medium,18,ImColor(49,49,49,255),{163,37},{284,37},14,{149,149,149,255});
                        if(pressed_button_2)
                            Api::client::user::status = Api::types::STATUS_CLIENT::SIGN_UP_DATA;
                        break;
                    }

                    case Api::types::STATUS_CLIENT::SIGN_UP_DATA:{
                        Ui::Draw::Components::ChildStartDraw("##block_sign_up",{589,244},{27,98},ImColor(71,71,71,255),0,10);
                        {
                            //Ui::Draw::Components::RectDraw("##block_1",{589,244},ImColor(71,71,71,255),{0,0},5);
                            Ui::Draw::Components::TextDraw("P",Ui::Gui::unisans_bold_italic,144,ImColor(255,255,255,255),{49,24});
                            Ui::Draw::Components::InputText("Login",Api::client::user::account_block.data.login.data(),Api::client::user::account_block.data.login.capacity(),{303,53},{268,21},ImColor(82,82,82,255),5);       
                            Ui::Draw::Components::InputText("Password",Api::client::user::account_block.data.password.data(),Api::client::user::account_block.data.password.capacity(),{303,53},{268,95},ImColor(82,82,82,255),5);
                            
                            bool pressed_button = Ui::Draw::Components::ButtonDraw("Further",Ui::Gui::inter_medium,16,ImColor(19,108,148,255),{448,31},{124,53},5);
                            if(pressed_button)
                                Api::client::user::status = Api::types::STATUS_CLIENT::SIGN_UP_MEMBER;
                        }
                        Ui::Draw::Components::ChildEndDraw();
                        break;
                    }

                    case Api::types::STATUS_CLIENT::SIGN_UP_MEMBER: {
                        Ui::Draw::Components::ChildStartDraw("##block_sign_up",{589,344},{27,98},ImColor(71,71,71,255),0,10);
                        {
                            //Ui::Draw::Components::RectDraw("##block_1",{589,244},ImColor(71,71,71,255),{0,0},5);
                            Ui::Draw::Components::TextDraw("P",Ui::Gui::unisans_bold_italic,144,ImColor(255,255,255,255),{49,24});
                            Ui::Draw::Components::InputText("Name",Api::client::user::account_block.mem.name.data(),Api::client::user::account_block.mem.name.capacity(),{303,53},{268,21},ImColor(82,82,82,255),5);       
                            Ui::Draw::Components::InputText("Surname",Api::client::user::account_block.mem.surname.data(),Api::client::user::account_block.mem.surname.capacity(),{303,53},{268,95},ImColor(82,82,82,255),5);
                            Ui::Draw::Components::InputNumber("Age",(int32_t*)&Api::client::user::account_block.mem.age,{303,53},{268,169},ImColor(82,82,82,255),5);
                            
                            bool pressed_button = Ui::Draw::Components::ButtonDraw("Further",Ui::Gui::inter_medium,16,ImColor(19,108,148,255),{448,31},{124,53},5);
                            if(pressed_button)
                                Api::client::user::status = Api::types::STATUS_CLIENT::SIGN_UP_EMAIL;
                        }
                        Ui::Draw::Components::ChildEndDraw();    
                        break;
                    };
                    case Api::types::STATUS_CLIENT::SIGN_UP_EMAIL: {
                        Ui::Draw::Components::ChildStartDraw("##block_sign_up",{589,184},{27,98},ImColor(71,71,71,255),0,10);
                        {
                            //Ui::Draw::Components::RectDraw("##block_1",{589,244},ImColor(71,71,71,255),{0,0},5);
                            Ui::Draw::Components::TextDraw("P",Ui::Gui::unisans_bold_italic,144,ImColor(255,255,255,255),{49,24});
                            Ui::Draw::Components::InputText("Email",Api::client::user::account_block.email.data(),Api::client::user::account_block.email.capacity(),{303,53},{268,21},ImColor(82,82,82,255),5);       
                            
                            bool pressed_button = Ui::Draw::Components::ButtonDraw("Further",Ui::Gui::inter_medium,16,ImColor(19,108,148,255),{448,31},{124,53},5);
                            if(pressed_button){
                                std::string username = (Api::client::user::account_block.mem.name + Api::client::user::account_block.mem.surname);
                       

                                Api::client::user::account_block.mem.username = (std::string(Api::client::user::account_block.mem.name.c_str()) + std::string(Api::client::user::account_block.mem.surname.c_str()));
                                Api::client::local_profile = Api::client::user::SignUp(Api::client::user::account_block);
                                Api::client::user::UpdateChatAndMessage();
                                Api::client::user::status = Api::types::STATUS_CLIENT::LOGI_IN;
                            }
                        }
                        Ui::Draw::Components::ChildEndDraw();   
                        break;
                    }
                
                    case Api::types::STATUS_CLIENT::LOGI_IN:{
                        Ui::Gui::window_size = {1287,683};

                        if(Api::client::user::list_chat_block.size()){
                             int isActive = 0;
                            for(int i = 0; i < Api::client::user::list_chat_block.size();i++){
                                Api::types::Member member = Api::client::user::list_chat_block[i].author_chat;

                                Ui::Draw::Components::ChildStartDraw(("##chat_block_" + member.username).c_str(),{249,53},{14,i == 0? 17 : (float)(i+1 * 17)},ImColor(57,57,57,255),ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse,6);
                                //Ui::Draw::Components::TextDraw((member.surname + " " + member.name).c_str(),Ui::Gui::inter_medium,16,ImColor(255,255,255,255),{64,14});
                                bool pressed = Ui::Draw::Components::ButtonDraw((member.surname + " " + member.name).c_str(),Ui::Gui::inter_medium,16,ImColor(0,0,0,0),{0,0},{249,53});

                                Ui::Draw::Components::ChildEndDraw();

                                if(pressed)
                                    isActive = i;
                            }
                            Ui::Draw::Components::ChildStartDraw("##name_chat",{984,53},{287,17},ImColor(67,67,67,255),0,10);
                            Ui::Draw::Components::TextDraw(Api::client::user::list_chat_block[isActive].author_chat.name.c_str(),Ui::Gui::inter_medium,16, ImColor(255,255,255,255), {18,18});
                            Ui::Draw::Components::ChildEndDraw();

                            //Ui::Draw::Components::ChildStartDraw("##chat",{984,646},{287,17},ImColor(60,60,60,255),ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse,10);
                            {


                                Ui::Draw::Components::ChildStartDraw("##list",{984,539},{287,79},ImColor(60,60,60,255),ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse ,10);
                        
                                std::vector<Api::types::MessageData> list = Api::client::user::list_chat_block[isActive].list_message;                            
                                    
                                for(int i = 0; i < list.size();i++){
                                    
                                    Api::types::MessageData data = list[i];
                                    // Ui::Draw::Components::TextDraw(list[i].message.c_str(),Ui::Gui::inter_medium,16,ImColor(255,255,255,255),{,0});
                                    ImVec2 pos_block = {data.author.username == Api::client::local_profile.username? (float)(964 - ((10 + data.message.size()) * 4)) : 20 , 10};
                                    Ui::Draw::Components::ChildStartDraw(("##message" + std::to_string(i)).c_str(),{(float)(((10 + data.message.size()) * 4)),37},pos_block,ImColor(66,66,66,255),ImGuiWindowFlags_NoScrollbar,2, true);
                                    Ui::Draw::Components::TextDraw(list[i].message.c_str(),Ui::Gui::inter_medium,16,ImColor(255,255,255,255),{10,10});
                                    Ui::Draw::Components::ChildEndDraw();
                                }
                                Ui::Draw::Components::ChildEndDraw();

                                
                                    
                                if(GetAsyncKeyState(VK_RETURN) & 1){
                                    Api::types::MessageData data = {
                                        Api::client::local_profile,
                                        Api::client::user::list_chat_block[isActive].author_chat,
                                        Api::client::user::chat::message_buffer
                                    };

                                    Api::client::user::SendMessage(data);
                                    Api::client::user::UpdateChatAndMessage();   
                                }     
                            }
                            //Ui::Draw::Components::ChildEndDraw(); 

                            Ui::Draw::Components::InputText(("Write at @" + Api::client::user::list_chat_block[isActive].author_chat.username).c_str(),Api::client::user::chat::message_buffer,78,{984,37},{287,626},ImColor(68,68,68,255),5);
                        }
                       
                        
                        Ui::Draw::Components::ChildStartDraw("##profile",{261,50},{14,613},ImColor(60,60,60,255),ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar,10);
                        Ui::Draw::Components::TextDraw((std::string(Api::client::local_profile.surname.c_str()) + " " + std::string(Api::client::local_profile.name.c_str())).c_str(),Ui::Gui::inter_medium,16,ImColor(255,255,255,255),{64,14});
                        Ui::Draw::Components::ChildEndDraw();
                        break;
                    }
                }
            }
        }
        void InitComp() {
            Api::client::user::status = Api::types::STATUS_CLIENT::SIGN_IN;

            ImGuiStyle* style = &ImGui::GetStyle();

            style->Colors[ImGuiCol_WindowBg] = ImVec4(RGBA(49,49,49,255));
            style->WindowPadding = {0.f,0.f};
            style->FramePadding = {0.f,0.f};       

            Ui::Gui::window_size = {643,683};
            // Ui::Gui::img = Ui::Image {
            //     "D:\\1.png"
            // };
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.Fonts->AddFontFromMemoryTTF(inter_medium_bytes,sizeof(inter_medium_bytes),170);
            Ui::Gui::inter_medium = io.Fonts->AddFontFromMemoryTTF(inter_medium_bytes,sizeof(inter_medium_bytes),170);

            io.Fonts->AddFontFromMemoryTTF(unisans_bold_italic_bytes,sizeof(unisans_bold_italic_bytes),170);
            Ui::Gui::unisans_bold_italic = io.Fonts->AddFontFromMemoryTTF(unisans_bold_italic_bytes,sizeof(unisans_bold_italic_bytes),170);

            io.Fonts->AddFontFromMemoryTTF(inter_medium_bytes,sizeof(inter_medium_bytes),18);
            Ui::Gui::inter_medium_lite = io.Fonts->AddFontFromMemoryTTF(inter_medium_bytes,sizeof(inter_medium_bytes),18);
            
            Api::client::user::account_data.login.reserve(50);
            Api::client::user::account_data.password.reserve(50);

            Api::client::user::account_block.data.login.reserve(50);
            Api::client::user::account_block.data.password.reserve(50);

            Api::client::user::account_block.mem.name.reserve(50);
            Api::client::user::account_block.mem.surname.reserve(50);
            Api::client::user::account_block.mem.username.reserve(50);
        }

        
        void MainRenderPoint() {
            Ui::ImGui_Local::ImGuiBlock window1 = {
                "Window",
                Ui::Gui::window_size,
                Ui::Gui::Menu::Draw,

                ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
            };
        }
    }
}