#include <iostream>
#include <string>
#include <sstream>
#include "tcp_listener.h"

int TcpListener::init() {
    // Initialize winsock
    WSADATA ws_data;
    WORD ver = MAKEWORD(2, 2);

    int wsok = WSAStartup(ver, &ws_data);
    if (wsok != 0) {
        std::cerr << "Can't initilize winsock!" << std::endl;
        return wsok;
    }

    // Create a listening socket
    _listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_listening_socket == INVALID_SOCKET) {
        std::cerr << "Can't create a socket!" << std::endl;
        return WSAGetLastError();
    }

    // Bind the ip address and port to the socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(_port);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;
    // inet_pton(AF_INET, _ip_address, &hint.sin_addr);
    if (bind(_listening_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        return WSAGetLastError();
    }

    // Tell Winsock which socket is used for listening
    if (listen(_listening_socket, SOMAXCONN) == SOCKET_ERROR) {
        return WSAGetLastError();
    }

    // Create the master file descriptor set and zero it
    FD_ZERO(&_master_fd);

    // Place the listening socket into the master file descriptor _master_fd
	FD_SET(_listening_socket, &_master_fd);

    return 0;
}

int TcpListener::run() {
    bool running = true;  // TODO: add quit() flag to quit the program

    while (running) {
        fd_set copy = _master_fd;

        // Get the total number of socket handles that are ready and contained in the fd_set copy
        int socket_count = select(0, &copy, nullptr, nullptr, nullptr);
        if (socket_count == SOCKET_ERROR) {
            std::cerr << "an error occurred during select()!" << std::endl;
            return WSAGetLastError();
        }

        // Check socket by socket
        for (int i = 0; i < socket_count; i++) {
            SOCKET sock = copy.fd_array[i];

            if (sock == _listening_socket) {
                // Accept a new connection
                SOCKET client = accept(_listening_socket, nullptr, nullptr);

                // Add the new connection to the list of connected clients (_master_fd)
                FD_SET(client, &_master_fd);

                OnClientConnected(sock);
            }
            else {  // client's socket
                char buf[4096];
                ZeroMemory(buf, 4096);

                // Receive message
                int bytes_in = recv(sock, buf, 4096, 0);
                if (bytes_in <= 0) { // drop the client
                    OnClientDisconnected(sock);
                    closesocket(sock);
                    FD_CLR(sock, &_master_fd);
                }
                else {
                    // Handle the received message
                    OnMessageReceived(sock, buf, bytes_in);
                }
            }
        }
    }

    // Remove the listening socket from the master file descriptor set and close it
    FD_CLR(_listening_socket, &_master_fd);
    closesocket(_listening_socket);

    // Remove other sockets from the master file descriptor set and close them
    while (_master_fd.fd_count > 0) {
        SOCKET sock = _master_fd.fd_array[0];
        FD_CLR(sock, &_master_fd);
        closesocket(sock);
    }

    // Cleanup winsock
    WSACleanup();
    return 0;
}

void TcpListener::SendToClient(int client_socket, const char* msg, int length) {
    send(client_socket, msg, length, 0);
}

void TcpListener::BroadcastToClients(int sending_client, const char* msg, int length) {
    for (int i = 0; i < _master_fd.fd_count; i++) {
        SOCKET out_socket = _master_fd.fd_array[i];
        if (out_socket != _listening_socket && out_socket != sending_client) {
            SendToClient(out_socket, msg, length);
        } 
    }
}


void TcpListener::OnClientConnected(int client_socket) {

}

void TcpListener::OnClientDisconnected(int client_socket) {

}

void TcpListener::OnMessageReceived(int client_socket, const char* msg, int length) {

}

