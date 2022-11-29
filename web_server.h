#ifndef WEB_SERVER_H
#define WEB_SERVER_H


#include "tcp_listener.h"


class WebServer : public TcpListener {

public:

    WebServer(const char* ip_address, int port) :
        TcpListener(ip_address, port) {}

protected:

    // handler for client's requests
    virtual void OnMessageReceived(int client_socket, const char* msg, int length);

    // handler for client connections
    virtual void OnClientConnected(int client_socket);

    // handler for client disconnections
    virtual void OnClientDisconnected(int client_socket);

};


#endif  // WEB_SERVER_H
