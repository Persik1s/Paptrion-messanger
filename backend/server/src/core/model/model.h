#ifndef MODEL_REPO
#define MODEL_REPO
#include <string>

namespace EntiyModel {
    
    class Member{
    public:
        std::string name;
        std::string surname;
        std::string username;
        int32_t age;
    public:
        Member(std::string name,std::string surname,std::string username,int32_t age) : 
            name(name), surname(surname), username(username), age(age) {}
        Member(){}
    };

    struct UserCreds {
        std::string login;
        std::string password;
        UserCreds(std::string login,std::string password) :
            login(login), password(password) {}
    };

    struct UserAuthData {
        Member user;
        UserCreds data;
        std::string ip;
        UserAuthData(Member user,UserCreds data,std::string ip) :
            user(user), data(data), ip(ip) {}
    };

    struct Message {
        Member author;
        Member recipient;
        const char* message;
    };

    struct HashKey {
        std::string key;
        HashKey(std::string key_hash) :
            key(key_hash) {}
        HashKey() {}
    };
}

#endif