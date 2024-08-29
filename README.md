# Patrion messanger

![alt text](assets/windows-support.svg) ![alt text](assets/linux-support.svg)


## About 

В этом примере мы создадим простой мессенджер, который может работать на различных платформах, таких как Windows и Linux. Мы будем использовать ImGui для создания графического интерфейса пользователя, GLFW для управления окном и вводом, Boost для работы с сетью, OpenGL для рендеринга графики, Socket для сетевого программирования и JSON для обмена данными. Кроме того, мы используем GLAD для загрузки функций OpenGL.

In this example, we will create a simple messenger that can run on various platforms such as Windows and Linux. We will use ImGui for creating a graphical user interface, GLFW for window and input management, Boost for network operations, OpenGL for graphics rendering, Socket for network programming, and JSON for data exchange. Additionally, we will use GLAD for loading OpenGL functions


## Build

Для компиляции проекта используйте соответствующие файлы build.bat в папке build, которые настроены для компиляции проекта 

To compile the project, use the corresponding build.bat files in the build folder, which are configured for compiling the project

# Third-party
- C++

- Client
    - ImGui( [ImGui](https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples))
    - Glad( [Glad](https://glad.dav1d.de/))
    - GLFW( [Glfw](https://www.glfw.org/))
    - Json( [Json](https://github.com/nlohmann/json) )
- Backend
    - Json( [Json](https://github.com/nlohmann/json) )
    - Boost([Boost](https://www.boost.org/))
