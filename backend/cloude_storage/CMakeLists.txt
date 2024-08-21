cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
project(cloude)

set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/components/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.84.0 REQUIRED COMPONENTS system filesystem)

add_executable(
    cloude
    src/core/filesys/filesys.cpp
    src/core/handler/handler.cpp
    src/core/service/service.cpp
    src/core/net/request/request.cpp
    src/core/net/server/server.cpp
    src/main.cpp
)

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
endif()