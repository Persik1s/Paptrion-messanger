cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)
project(server)

set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/components/boost")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.84.0 REQUIRED COMPONENTS system filesystem)
find_package(PostgreSQL REQUIRED)

add_executable(
    server
    src/components/cloude/cloude.cpp
    src/components/crypto/md5.cpp
    
    src/core/net/server/server.cpp
    src/core/net/request/request.cpp

    src/core/service/account/account.cpp
    src/core/model/repository/account/account.cpp
    src/core/routs/handlers/account/account.cpp
    
    src/core/routs/routs.cpp
    src/main.cpp    
)

if(Boost_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    message(STATUS "Found BOOST ${Boost_VERSION_STRING}")
endif()

target_link_libraries(${PROJECT_NAME} ${PostgreSQL_LIBRARIES} ws2_32.lib wsock32.lib)

include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/components/libpqxx/include)
target_link_libraries(${PROJECT_NAME}  ${CMAKE_CURRENT_SOURCE_DIR}/src/components/libpqxx/lib/pqxx.lib)

