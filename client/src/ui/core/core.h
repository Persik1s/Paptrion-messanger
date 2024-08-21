#ifndef CORE_
#define CORE_
#include "window/window.h"

namespace Ui {
    namespace Core {
        inline bool InitGLFW(){
            if(!glfwInit())
                return 0;    
            return 1;
        }

        inline bool InitGLAD(){
            if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
                return 0;    
            return 1;
        }
    }
}

#endif