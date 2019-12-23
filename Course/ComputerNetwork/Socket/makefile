cc = gcc
all: client server
.PHONY : all
client : 
	cc client.c -o client.o
server :
	cc server.c -o server.o
kill:
	kill -9 $(lsof -i:5696 -t)