#ifndef SERVICE_ACCOUNT  
#define SERVICE_ACCOUNT

#include "../../../components/json/json.hpp"

namespace Service {
    namespace account {
        std::string SignIn(nlohmann::json object);
        std::string SignUp(nlohmann::json object);
    }
}

#endif 