#ifndef CLOUDE_REPOS
#define CLOUDE_REPO 
#include "../../../components/cloude/cloude.h"

namespace Model {
    namespace cloude {
        inline Cloude cloude_repo;
        inline void Init(){
            cloude_repo = {"127.0.0.1",8080};
        }
    } 
}

#endif
