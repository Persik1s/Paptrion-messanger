#ifndef REPOSITORY
#define REPOSITORY
#include "../model.h"
#include "../../../components/libpqxx/include/pqxx/pqxx"

namespace Model {
    namespace repository {
        inline pqxx::connection connect("host=127.0.0.1 port=5444 dbname=admin user=admin password=rootroot");
        
        inline void Init(){
            pqxx::work work(connect);
            work.exec("CREATE TABLE IF NOT EXISTS Users(name TEXT, surname TEXT, username TEXT, age INT, login TEXT, password TEXT , ip TEXT,hash_key TEXT)");
            work.commit();
        }
        namespace account {
            bool IsAccount(EntiyModel::HashKey key);
            bool InsertAccount(EntiyModel::UserAuthData data,EntiyModel::HashKey key);
            EntiyModel::Member SelectDataAccount(EntiyModel::HashKey key);

        }
    }
}

#endif