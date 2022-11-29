# Network Programming

## An C++ implementation for `Web server` and `Multi-Client-Chat server` on the Windows environment.

* A simple web server listens for TCP connections, parses HTTP requests, and responds to clients.
* A multi-client-chat server listens for TCP connections, receives messages from a client, and broadcasts to others..


## Requirements
* Compliler: MinGW32-g++
* Makefile: MinGW32-make
* `Note`: if using Microsoft Visual Studio, please uncomment the line  `// #pragma comment (lib, "ws2_32.lib")`  in `tcp_listener.h` file to use library ws2_32.lib

## Usage
Note: switch `SERVER_TYPE` between `WEB_SERVER` and `CHAT_SERVER` to change server types. (the line `#define SERVER_TYPE     (WEB_SERVER)` in server.cpp)
```bash
> mingw32-make  # build

> mingw32-make clean  # clean

> server  # run server

```

## TODO:
* Apply multi-threading to serve different clients.
