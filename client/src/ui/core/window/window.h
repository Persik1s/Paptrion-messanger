#ifndef WINDOW_
#define WINDOW_

#include <functional>

#include "../../../components/glad/include/glad/gl.h"
#include "../../../components/glfw/include/GLFW/glfw3.h"

namespace Ui {
    namespace Core {
        namespace window {
            class Window {
            public:
                Window(const char* nameWindow,int16_t width,int16_t height,std::function<void()> render = nullptr){
                    this->width = width;
                    this->height = height;
                    this->naemWindow = nameWindow;

                    this->renderFunction = render;

                    this->init_window();
                }

                Window() {}   

            public:
                const char* naemWindow;

                int16_t width;
                int16_t height;

                GLFWwindow* window;
                std::function<void()> renderFunction = nullptr;
            
            private:
                void init_window();

            public:
            
                void SwapBuffer();
                void DestroyWindow();
            };
        }
    } 
}

#endif