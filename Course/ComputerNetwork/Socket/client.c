#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define SERVER_PORT 5696
#define MAX_LINE 4096

int father_pid;
int localfd;
int connectfd;
char *now[64];

void closeConnect(){
	printf("Closing connection...\n");
	if (close(localfd) || close(connectfd) == -1) {
		("Error occured in close(): %s(erro: %d)", strerror(errno), errno);
	} else {
		printf("Client stopped.\n");
		exit(0);
	}
}

char *getCurrentTime() {
	time_t tim;
	struct tm *at;
	time(&tim);
	at = localtime(&tim);
	strftime(now, 79, "%Y-%m-%d %H:%M:%S", at);
	return now;
}


int main(int argc, char * argv[]){
	printf("A simple TCP duplex communication program. Press [Ctrl] + [C] to exit.\n\n");

	char *host;
	struct hostent *hp;
	struct sockaddr_in socketaddr;

	char *inbuffer[MAX_LINE];
	char *outbuffer[MAX_LINE];
	memset(inbuffer, 0, MAX_LINE * sizeof(char));
	memset(outbuffer, 0, MAX_LINE * sizeof(char));

	/* 信号处理 */
	signal(SIGINT, closeConnect);
	signal(SIGUSR1, closeConnect);

	if (argc == 2) {
		host = argv[1];
	} else {
		fprintf(stderr, "Invalid argument. Usage: client.o host\n");
		exit(1);
	}

	/* 创建 Socket */
	if ((localfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		printf("Error occured in socket(): %s(erro: %d)", strerror(errno), errno);
		exit(-1);
	}

	/* 设置服务地址 */
	if ((hp = gethostbyname(host)) < 0){
		printf("Error occured in gethostbyname(): %s(erro: %d)", strerror(errno), errno);
		exit(-1);
	}
	memset(&socketaddr, 0, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = htons(SERVER_PORT);
	if (inet_pton(AF_INET, host, &socketaddr.sin_addr) < 0) {
		printf("Error occured in inet_pton(): %s(erro: %d)", strerror(errno), errno);
		exit(-1);
	}

	/* 连接服务器 */
	if (connectfd = connect(localfd, (struct sockaddr *)&socketaddr, sizeof(socketaddr)) == -1){
		printf("Error occured in connect(): %s(erro: %d)", strerror(errno), errno);
		exit(-1);
	}

	printf("Connected to server %s:%d\n" ,inet_ntoa(socketaddr.sin_addr), ntohs(socketaddr.sin_port));
	int pid = fork();
	if (pid == 0) {
		signal(SIGINT, NULL);
		/* 子进程，从服务器接受数据 */
		int msglen;
		while((msglen = recv(localfd, inbuffer, MAX_LINE, 0)) > 0){
			inbuffer[msglen] = '\0';
			printf("<%s SERVER %s:%d> %s", getCurrentTime(), inet_ntoa(socketaddr.sin_addr), ntohs(socketaddr.sin_port) ,inbuffer);
			memset(inbuffer, 0, 4096 * sizeof(char));
		}
		printf("Server disconnected.\n");
		kill(father_pid, SIGUSR1);
	}

	else {
		/* 父进程，向服务器发送数据 */
		while (1) {
			
			fgets(outbuffer, MAX_LINE * sizeof(char), stdin);
			if (strcmp(outbuffer, "exit\n") == 0) {
				break;
				closeConnect();
			}
			int length = strlen(outbuffer) + 1;
			int ret = send(localfd, outbuffer, length, 0);
			if (ret < 0) {
				printf("Fail to send message: %s(erro: %d)", strerror(errno), errno);
			}
			if(ret == 0){
				printf("Server disconnected.\n");
				break;
			}
		}
		
	}
	int status;
	waitpid(pid, &status, 0);
	closeConnect();
}