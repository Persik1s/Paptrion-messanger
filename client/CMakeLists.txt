cmake_minimum_required(VERSION 3.11.3)


set(CMAKE_CXX_STANDARD 17)
project(client)

add_executable(
    client
    src/main.cpp

    src/net/http/http_request.cpp
    src/net/socket/socket.cpp

    src/api/client/client.cpp
    src/api/client/user/user.cpp
    src/api/web/web.cpp
    
    src/ui/core/window/window.cpp

    src/ui/classes/classes.cpp
    src/ui/draw/components/components.cpp
    src/ui/gui/gui.cpp
    

    
    src/components/imgui/imgui_impl_opengl3.cpp
    src/components/imgui/imgui_demo.cpp
    src/components/imgui/imgui_draw.cpp
    src/components/imgui/imgui_tables.cpp
    src/components/imgui/imgui_widgets.cpp
    src/components/imgui/imgui_impl_glfw.cpp
    src/components/imgui/imgui.cpp




    src/components/glad/src/gl.c
    src/components/glad/src/wgl.c
)

add_subdirectory(
    src/components/glfw
)

target_link_libraries(client glfw)