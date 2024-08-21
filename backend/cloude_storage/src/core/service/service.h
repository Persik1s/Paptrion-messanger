#ifndef SERVICE
#define SERVICE
#include <vector>
#include "../../components/json/json.hpp"

namespace Service {
    void DeleteFileCloude(nlohmann::json& json);
    void DeleteDirCloude(nlohmann::json&  json);
    
    void CreateFileCloude(nlohmann::json&  json);
    void CreateDirCloude(nlohmann::json&  json);

    void WriteFileCloude(nlohmann::json&  json);
    std::string ReadFileCloude(nlohmann::json&  json);

    bool IsFileCloude(nlohmann::json&  json);
    bool IsDirCloude(nlohmann::json&  json);

    std::vector<std::string> ListNameFileAll(nlohmann::json&  json);
    std::vector<std::string> ListNameDirAll(nlohmann::json& json);
}

#endif