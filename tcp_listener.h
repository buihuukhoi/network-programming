#ifndef TCP_LISTENER_h
#define TCP_LISTENER_h


#include <WS2tcpip.h>

// uncomment the next line to use library ws2_32.lib if using Microsoft Visual Studio
// #pragma comment (lib, "ws2_32.lib")


class TcpListener {

public:
    TcpListener(const char* ip_address, int port) :
        _ip_address(ip_address), _port(port) {};

    int init();
    int run();

protected:

    // handler for client connections
    virtual void OnClientConnected(int client_socket);

    // handler for client disconnections
    virtual void OnClientDisconnected(int client_socket);

    // handler for a received message from a client
    virtual void OnMessageReceived(int client_socket, const char* msg, int length);

    // send a message to a client
    void SendToClient(int client_socket, const char* msg, int length);

    // broadcast a message from a client
    void BroadcastToClients(int sending_client, const char* msg, int length);

private:
    const char* _ip_address;
    int         _port;
    int         _listening_socket;
    fd_set      _master_fd;        // Master file descriptor set

};

#endif