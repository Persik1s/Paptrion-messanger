cmake_minimum_required(VERSION 3.11.3)


set(CMAKE_CXX_STANDARD 17)
project(client)

add_executable(
    client
    src/main.cpp
    src/net/http/http_request.cpp
    src/net/socket/socket.cpp
)