#ifndef UI_
#define UI_
#define RGBA(r, g, b, a) (r / 255.0f), (g / 255.0f), (b / 255.0f), (a / 255.0f)

#include "classes/classes.h"
#include "../api/api.h"
namespace Ui{}
namespace Ui::ImGui_Local{}
namespace Ui::Gui{}
namespace Ui::Draw{}
namespace Ui::Draw::Components{}

namespace Ui {
    namespace Draw {
        namespace Components {
            void ImageDarw(Ui::Image img,ImVec2 size,ImVec2 pos);
            void TextDraw(const char* str,ImFont* font,int size_font,ImColor color_text,ImVec2 pos_text);
        
            bool ButtonDraw(const char* str, ImFont* font, int size_font, ImColor color, ImVec2 pos_button, ImVec2 size_button,float round = 0,ImColor text_color = {255,255,255,255});

            void InputText(const char* strName,char* buffer,int size_buffer, ImVec2 size,ImVec2 pos,ImColor color,int round = 0, bool childPos = false);
            void InputNumber(const char* strName,int* buffer, ImVec2 size,ImVec2 pos,ImColor color,int round = 0, bool childPos = false);
            
            void ChildStartDraw(const char* str,ImVec2 size,ImVec2 pos,ImColor backround,ImGuiChildFlags flags = 0,int round = 0,bool childPos = false);
            void ChildEndDraw();

            void RectDraw(const char* str,ImVec2 size,ImColor color,ImVec2 pos,int round = 0);
        }

    }
    namespace Gui {
        void InitComp();
        void MainRenderPoint();

        inline ImFont* inter_medium;
        inline ImFont* inter_medium_lite;
        inline ImFont* unisans_bold_italic;

        inline ImVec2 window_size;

    }


}
#endif