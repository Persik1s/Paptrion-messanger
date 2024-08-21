#include "window.h"



namespace Ui {
    namespace Core {
        namespace window {
            void Window::init_window() {
                this->window = glfwCreateWindow(
                    this->width,
                    this->height,
                    this->naemWindow,
                    0,
                    0
                );

                glfwMakeContextCurrent(this->window);
            }
            void Window::SwapBuffer(){
                glfwSwapBuffers(this->window);
            }

        
            void Window::DestroyWindow(){
                glfwDestroyWindow(this->window);
            }
        }
    }
}
