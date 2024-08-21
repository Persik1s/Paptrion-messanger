#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include "classes.h"
#include "../../components/stb/stb_image.h"
namespace Ui {
    namespace ImGui_Local {
         void ImGuiWindow::Render(){
            #if defined(IMGUI_IMPL_OPENGL_ES2)
                const char* glsl_version = "#version 100";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            #elif defined(__APPLE__)
                const char* glsl_version = "#version 150";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           
            #else
                const char* glsl_version = "#version 130";
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            
            #endif
            IMGUI_CHECKVERSION();

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(this->m_window.window, true);
            ImGui_ImplOpenGL3_Init(glsl_version);


            this->function_comp();
            
            bool show_demo_window = true;
            bool show_another_window = false;
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

            while(!glfwWindowShouldClose(this->m_window.window)){
                glfwPollEvents();
                if (glfwGetWindowAttrib(this->m_window.window, GLFW_ICONIFIED) != 0)
                {
                    ImGui_ImplGlfw_Sleep(10);
                    continue;
                }
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
                

                this->function_render();

                ImGui::Render();
                int display_w, display_h;
                glfwGetFramebufferSize(this->m_window.window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);
                glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(this->m_window.window);

            }
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    Image::Image(const char* path) {
        
        this->m_bytes.reset(stbi_load(path,&width,&height,(int32_t*)&m_comp,0));
        this->init_texture();
    }

    Image::Image(unsigned char* bytes){

        this->m_bytes.reset(stbi_load_from_memory(bytes,sizeof(bytes),&width,&height,(int32_t*)&m_comp,0));
        this->init_texture();
    }


    void Image::init_texture(){ 
        switch((int32_t)this->m_comp) {
            case 3:{
                this->m_colorData = GL_RGB;
                break;
            }

            case 4: {
                this->m_colorData = GL_RGBA;
                break;
            }
        }

        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, this->m_colorData, this->width, this->height, 0,  this->m_colorData, GL_UNSIGNED_BYTE, this->m_bytes.get());
        std::cout << image_texture << std::endl;
        this->texture = image_texture;
 
    }
}