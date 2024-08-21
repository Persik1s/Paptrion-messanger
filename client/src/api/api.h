#ifndef API_
#define API_

#include <vector>

namespace Api{}
namespace Api::types{}

#include "../net/net.h"
#include "types.h"


namespace Api {
    namespace client {
        namespace user {
            types::Member SignUp(types::AccountBlock data);
            types::Member SignIn(types::AccountData data);
            
            bool SendMessage(types::MessageData message);

            void UpdateChatAndMessage();

            std::vector<types::MessageData> GetListMessage(types::Member mem);

            inline std::vector<types::ChatBlock> list_chat_block;

            inline types::AccountData account_data;
            inline types::AccountBlock account_block;

            inline types::STATUS_CLIENT status;
        
            namespace chat {
                inline char message_buffer[78];
            }
        }
        std::vector<types::Member> GetListChat();

        inline types::Member local_profile;
    }
    namespace web {
        namespace request {
            namespace error {
                inline std::vector<const char*> error_list = {
                    "LIST_MESSAGE_NULL",
                    "LIST_CHAT_NULL"
                };
            }
        }
        void InputHandler();
        bool IsResponeError(const char* data);
    }
}
#endif