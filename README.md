# Network Programming

An C++ implementation for Web server and Multi-Client-Chat server on the Windows environment.

* Simple web server listen for TCP connections, parse simple HTTP request and repsonse to clients.
* Multi-Client-Chat server listen for TCP connections, receive messages from a client and broadcast to others.


## Requirements
* Compliler: MinGW32-g++
* Makefile: MinGW32-make
* Note: if using Microsoft Visual Studio, please uncomment the line  `// #pragma comment (lib, "ws2_32.lib")`  in tcp_listener.h file to use library ws2_32.lib

## Usage example
Note: switch `SERVER_TYPE` between `WEB_SERVER` and `CHAT_SERVER` to change server types. (the line `#define SERVER_TYPE     (WEB_SERVER)` in server.cpp)
```bash
> mingw32-make

> mingw32-make clean

> server

```

## TODO:
* Apply multi-threading to serve different clients.
