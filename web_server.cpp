#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

#include "web_server.h"
#include "web_server_define.h"


// handler client's requests
void WebServer::OnMessageReceived(int client_socket, const char* msg, int length) {
    // Parse out the document requested, e.g. GET /index.html HTTP/1.1
    std::istringstream iss(msg);
    std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());

    std::string content = NOT_FOUND_404;
    std::string html_file = DEFAULT_PAGE;
    int error_code = ERROR_CODE_404;
    
    if (parsed.size() >= 3 && parsed[0] == GET && parsed[1] != HOME) {
        html_file = parsed[1];
    }
    
    // Open the document file
    std::ifstream f(WWW_FOLDER + html_file);

    if (f.good()) {
        std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        content = str;
        error_code = ERROR_CODE_200;
    }

    f.close();

    // Prepare the document to send back to the client
    std::ostringstream oss;
    oss << "HTTP/1.1 " << error_code << " OK" << ENDL;
    oss << "Cache-Control: no-cache, private" << ENDL;
    oss << "Content-Type: text/html" << ENDL;
    oss << "Content-Length: " << content.size() << ENDL;
    oss << ENDL;
    oss << content;

    std::string output = oss.str();
    int size = output.size() + 1;
        
    SendToClient(client_socket, output.c_str(), size);
}

// handler for client connections
void WebServer::OnClientConnected(int client_socket) {

}

// handler for client disconnections
void WebServer::OnClientDisconnected(int client_socket) {

}
