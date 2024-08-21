#include "../../ui.h"
#include "../../../components/imgui/imgui_internal.h"

namespace Ui {
    namespace Draw {
        namespace Components {
            void ImageDarw(Ui::Image img,ImVec2 size,ImVec2 pos){
                ImGui::SetCursorPos(pos);
                ImGui::Image((void*)(intptr_t)img.texture,size);
            }

            void TextDraw(const char* str,ImFont* font,int size_font,ImColor color_text,ImVec2 pos_text){
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                if (window->SkipItems)
                    return;

                ImGuiContext& g = *GImGui;
                const ImGuiStyle& style = g.Style;
                const ImGuiID id = window->GetID(str);

                const ImVec2 label_size = ImGui::CalcTextSize(str, NULL, true);
                const float square_sz = ImGui::GetFrameHeight();
                const ImVec2 pos = {window->DC.CursorPos.x + pos_text.x,window->DC.CursorPos.y + pos_text.y};
                ImVec2 tablePos =  { square_sz + (style.ItemInnerSpacing.x + label_size.x), label_size.y + style.FramePadding.y * 2};
                
                
                ImRect total_bb(pos, { tablePos.x + pos.x ,tablePos.y + pos.y });


                ImGui::ItemSize(total_bb, style.FramePadding.y);
                ImGui::ItemAdd(total_bb, id);

                window->DrawList->AddText(font,size_font,pos,color_text,str);
            }    
            bool ButtonDraw(const char* str, ImFont* font, int size_font, ImColor color, ImVec2 pos_button, ImVec2 size_button,float round,ImColor text_color) {
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                if (window->SkipItems)
                    return false;

                ImGuiContext& g = *GImGui;
                const ImGuiStyle& style = g.Style;
                const ImGuiID id = window->GetID(str);
                const ImVec2 label_size = ImGui::CalcTextSize(str);
                const ImVec2 pos = { window->DC.CursorPos.x + pos_button.x, window->DC.CursorPos.y + pos_button.y };
                ImRect total_bb(pos, { pos.x + size_button.x, pos.y + size_button.y });
                ImGui::ItemSize(total_bb, style.FramePadding.y);
                ImGui::ItemAdd(total_bb, id);

                window->DrawList->AddRectFilled(total_bb.Min, total_bb.Max, color, round);
                
                ImVec2 text_pos = ImVec2(pos.x +  size_button.x / 2  - (strlen(str) * 4), pos.y + 14);
                window->DrawList->AddText(font, size_font, text_pos, text_color, str);

                return ImGui::IsItemClicked();
            }
            void ChildStartDraw(const char* str,ImVec2 size,ImVec2 pos,ImColor backround,ImGuiChildFlags flags,int round,bool childPos) {
                
               ImVec2 cursorPos = ImGui::GetCursorPos();
               ImVec2 new_cursor_pos = (childPos == 1) ? ImVec2(cursorPos.x + pos.x, cursorPos.y + pos.y) : ImVec2(pos.x, pos.y);
                if(pos.x != 0 || pos.y != 0)
                    ImGui::SetCursorPos(new_cursor_pos);
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding,round);

                ImGui::PushStyleColor(ImGuiCol_ChildBg,ImVec4(backround));

                ImGui::BeginChild(str,size,0,flags);
            }

            void ChildEndDraw() {
                ImGui::EndChild();
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            }

            void InputText(const char* strName,char* buffer,int size_buffer, ImVec2 size,ImVec2 pos,ImColor color,int round, bool childPos){
                ChildStartDraw((std::string("##child") + strName).c_str(),size,pos,color,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse,round,childPos);

                ImGui::PushFont(Ui::Gui::inter_medium_lite);
                ImGui::PushItemWidth(size.x - 10);
 
                ImGui::SetCursorPos({10,9});
                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)color);
                ImGui::InputText(" ",buffer,size_buffer);
                ImGui::PopStyleColor();
                

                ImGui::PopItemWidth();
                ImGui::PopFont();
                if(!strlen(buffer)){

                    ImGui::SetCursorPos({10,0});
                    TextDraw(strName,Ui::Gui::inter_medium,18,ImColor(255,255,255,255),{10,9});
                }

                
                ChildEndDraw();
            }

            void InputNumber(const char* strName,int* buffer, ImVec2 size,ImVec2 pos,ImColor color,int round, bool childPos){
                ChildStartDraw((std::string("##child") + strName).c_str(),size,pos,color,ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse,round,childPos);

                ImGui::PushFont(Ui::Gui::inter_medium_lite);
                ImGui::PushItemWidth(size.x - 10);
 
                ImGui::SetCursorPos({10,9});

                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)color);
                ImGui::InputInt(" ", buffer, 0,0,ImGuiInputTextFlags_None);
                ImGui::PopStyleColor();
                

                ImGui::PopItemWidth();
                ImGui::PopFont();
                
                if(!(*buffer)){
                    ImGui::SetCursorPos({10,0});
                    TextDraw(strName,Ui::Gui::inter_medium,18,ImColor(255,255,255,255),{10,9});
                }

                
                ChildEndDraw();
            }

            void RectDraw(const char* str,ImVec2 size,ImColor color,ImVec2 pos_rect,int round) {
                ImGuiWindow* window = ImGui::GetCurrentWindow();
                if (window->SkipItems)
                    return;

                ImGuiContext& g = *GImGui;
                const ImGuiStyle& style = g.Style;
                const ImGuiID id = window->GetID(str);
                const ImVec2 label_size = ImGui::CalcTextSize(str);
                const ImVec2 pos = { window->DC.CursorPos.x + pos_rect.x, window->DC.CursorPos.y + pos_rect.y };
                ImRect total_bb(pos, { pos.x + size.x, pos.y + size.y });
                ImGui::ItemSize(total_bb, style.FramePadding.y);
                ImGui::ItemAdd(total_bb, id);

                window->DrawList->AddRectFilled(total_bb.Min,total_bb.Max,color,round);
        
            }
        }
    }
}