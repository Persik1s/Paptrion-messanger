#ifndef CLASSES_UI
#define CLASSES_UI

#include <memory>

#include "../core/core.h"

#include "../../components/imgui/imgui.h"
#include "../../components/imgui/imgui_impl_glfw.h"
#include "../../components/imgui/imgui_impl_opengl3.h"


namespace Ui {
    namespace ImGui_Local {
        class ImGuiWindow{
        private:
            Core::window::Window m_window;
        public:
            ImGuiWindow(Core::window::Window window,std::function<void()> render = nullptr,std::function<void()> comp = nullptr) {
                this->function_render = render;
                this->function_comp = comp;
                this->m_window = window;
            }

        public:
            void Render();
        public:
            std::function<void()> function_render;
            std::function<void()> function_comp;
        };

        class ImGuiBlock {
        private:

            const char* m_nameBlock;
            ImVec2 m_size;
            std::function<void()> m_renderF;
            ImGuiWindowFlags m_flags;
        
        public:
            ImGuiBlock(const char* nameBlock,ImVec2 size,std::function<void()> render,ImGuiWindowFlags flags = 0){
                this->m_nameBlock = nameBlock;
                this->m_size = size;
                this->m_renderF = render;
                this->m_flags = flags;

                this->render();
            }
        private:
            void render(){
                ImGui::SetNextWindowSize(this->m_size);
                ImGui::Begin(this->m_nameBlock,0,this->m_flags);
                this->m_renderF();
                ImGui::End();
            }
        };
    }

    class Image {
    private:
        int8_t m_colorData;
        int8_t m_comp;
        std::shared_ptr<unsigned char> m_bytes;
    public:
        unsigned char texture;        
        
        int32_t width;
        int32_t height;

    public:
        Image(const char* path);
        Image(unsigned char* bytes);
        Image(){}
        ~Image();
    private:
        void init_texture();
    };
}
#endif