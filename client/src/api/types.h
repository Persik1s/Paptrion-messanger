#ifndef TYPES_
#define TYPES_
#include <string>
namespace Api {
    namespace types {

        class Member {
        public:
            std::string name;
            std::string surname;
            std::string username;
            int8_t age = 0;
            
            Member(std::string name,std::string surname,std::string username,int8_t age) 
                : name(name) , surname(surname), username(username), age(age) {}
            Member(){}
        
        };

        struct MessageData {        
            Member author;
            Member recipient;
            std::string message;

            MessageData(Member author,Member recipient, std::string message) 
            : author(author), recipient(recipient), message(message) {}

            MessageData();
        };

        struct AccountData {
            std::string password;
            std::string login;
            std::string ip;

            AccountData(std::string login,std::string password,std::string ip) 
                : login(login), password(password) , ip(ip) {}

            AccountData(){}
        };

        struct AccountBlock {
            Member mem;
            AccountData data;
            std::string email;
 
            AccountBlock(Member mem,AccountData data,std::string email) 
                : mem(mem), data(data), email(email) {}
            AccountBlock(){};
        };

        enum class STATUS_CLIENT {
            SIGN_IN,
            SIGN_UP_DATA,
            SIGN_UP_MEMBER,
            SIGN_UP_EMAIL,
            LOGI_IN
        };

        struct ChatBlock {
            Member author_chat;
            std::vector<MessageData> list_message;
            
            ChatBlock(Member author_chat,std::vector<MessageData> list_message) 
                : author_chat(author_chat), list_message(list_message) {}

            ChatBlock(){}
        };
    }
}

#endif