#include <iostream>
#include <string>
#include <vector>
#if _WIN32 || __linux__
    #if _WIN32
        #include <WinSock2.h>
        #pragma comment(lib,"ws2_32.lib")

    #elif __linux
        #include <sys/socket.h>
    #endif
#endif

