#include "../repository.h"
#include "../../../logger/logger.h"

namespace Model {
    namespace repository {
        namespace account {   
            bool IsAccount(EntiyModel::HashKey key) {
                if(!Model::repository::connect.is_open())
                    std::runtime_error("ERROR DATA BASE");
                    
                pqxx::work work(Model::repository::connect);
                pqxx::result result = work.exec_params("SELECT hash_key FROM Users WHERE  hash_key = $1",key.key);
                return result.size() > 0;
            }

            EntiyModel::Member SelectDataAccount(EntiyModel::HashKey key){
                if(!Model::repository::connect.is_open())
                    throw std::runtime_error("ERROR DATA BASE");
                
                pqxx::work work(Model::repository::connect);
                pqxx::result result = work.exec_params("SELECT name, surname,username,age FROM Users WHERE hash_key = $1",key.key);
                return {
                    result[0][0].as<std::string>(),
                    result[0][1].as<std::string>(),
                    result[0][2].as<std::string>(),
                    result[0][3].as<int32_t>()
                };
            }
            bool InsertAccount(EntiyModel::UserAuthData data,EntiyModel::HashKey key){
                if(!Model::repository::connect.is_open())
                    throw std::runtime_error("ERROR DATA BASE");
                
                if( data.data.login.empty() || 
                    data.data.password.empty() ||
                    data.user.name.empty() ||
                    data.user.surname.empty() ||
                    data.user.username.empty() ||
                    data.ip.empty()) {
                    return 0;
                }
                pqxx::work work(Model::repository::connect);
                try {
                    pqxx::result result = work.exec_params("INSERT INTO Users(name, surname, username, age,login, password, ip, hash_key)  VALUES($1,$2,$3,$4,$5,$6,$7,$8)",
                    data.user.name,data.user.surname,data.user.username,data.user.age,data.data.login,data.data.password,data.ip,key.key);
                    work.commit();

                    return 1;
                } catch(const pqxx::sql_error& err) {
                    work.abort();
                    Logger::log.add_err(err.what());
                    return 0;
                }
            }
        }
    }
}