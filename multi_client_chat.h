#ifndef MULTI_CLIENT_CHAT_H
#define MULTI_CLIENT_CHAT_H


#include "tcp_listener.h"


class MultiClientChat : public TcpListener {

public:

    MultiClientChat(const char* ip_address, int port) :
        TcpListener(ip_address, port) {}

protected:

    // handler for client connections
    virtual void OnClientConnected(int client_socket);

    // handler for client disconnections
    virtual void OnClientDisconnected(int client_socket);

    // handler for a received message from a client
    virtual void OnMessageReceived(int client_socket, const char* msg, int length);

};

#endif