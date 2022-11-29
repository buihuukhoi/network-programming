OBJS = server.o tcp_listener.o multi_client_chat.o web_server.o
CC = g++
FLAG = -lws2_32  # include library ws2_32.lib from MinGW

server: ${OBJS}
	${CC} ${OBJS} -o $@ ${FLAG}

clean:
	-del *.o

.cpp.o:
	${CC} -c $< ${FLAG}

