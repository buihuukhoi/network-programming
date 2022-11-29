#include <string>
#include "multi_client_chat.h"


void MultiClientChat::OnClientConnected(int client_socket) {
    // send a welcome message to the connected client
    std::string welcome_msg = "Welcome to the chat server!\r\n";
    SendToClient(client_socket, welcome_msg.c_str(), welcome_msg.size() + 1);
}

void MultiClientChat::OnClientDisconnected(int client_socket) {

}

void MultiClientChat::OnMessageReceived(int client_socket, const char* msg, int length) {
    BroadcastToClients(client_socket, msg, length);
}

