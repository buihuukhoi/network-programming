#define CHAT_SERVER     (1)
#define WEB_SERVER      (2)
#define SERVER_TYPE     (WEB_SERVER)


#if SERVER_TYPE == CHAT_SERVER      // CHAT_SERVER

#include "multi_client_chat.h"
#define PORT 54000
using Server = MultiClientChat;

#elif SERVER_TYPE == WEB_SERVER     // WEB_SERVER

#include "web_server.h"
#define PORT 8081
using Server = WebServer;

#else                               // OTHERS
#error NOT SUPPORT SERVER_TYPE
#endif


int main(){
    Server server("0.0.0.0", PORT);
    if (server.init() != 0) {
        return -1;
    }

    server.run();

    system("pause");

    return 0;
}
