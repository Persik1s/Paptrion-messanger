#ifndef TYPES_
#define TYPES_
#include <string>
namespace api {
    namespace types {
        class Member {
        public:
            std::string name;
            std::string surname;
            std::string username;
            int age;
            
            Member(std::string name,std::string surname,std::string username,int age) {
                this->name = name;
                this->surname = surname;
                this->username = username;
                this->age = age;
            }
            Member(){}
        };

        class MessageData {
        public:
            Member author;
            Member recipient;
            std::string message;

            MessageData(Member author,Member recipient, std::string message) {
                this->author = author;
                this->recipient = author;
                this->message = message;
            }

            MessageData();
        };

        class AccountData {
        public:
            std::string password;
            std::string login;

            AccountData(std::string login,std::string password){
                this->login = login;
                this->password = password;
            }
            AccountData(){}
        };

    }
}

#endif