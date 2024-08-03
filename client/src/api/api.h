#ifndef API_
#define API_

#include "../include.h"
#include "../net/net.h"

namespace api{}
namespace api::types{}


#include "types.h"

namespace api {
    namespace client {
        namespace user {

            types::Member SignUp();
            types::Member SignIn(types::AccountData data);
            
            void SendMessage(types::MessageData message);

            std::vector<types::MessageData> GetListMessage(types::Member mem);

            inline std::vector<types::Member> list_chat;
            inline types::AccountData account_data;
        }
        std::vector<types::Member> GetListChat();

        inline types::Member local_profile;
    }
}
#endif