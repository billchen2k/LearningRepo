#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <time.h>

#define MAX_PENDING 5
#define MAX_LINE 4096
#define MAX_CLIENT 15

#define CLIENT_CONNECTED 1
#define CLIENT_CLOSED -1
int father_pid;
int localfd;

struct client{
	int fd;
	int status;
};
struct client connectfd[MAX_CLIENT];
/* Client count */
int cc = 0;
char now[64];

void closeConnect(int signum) {
	printf("Closing connection...\n");
	int i;
	for (int i = 0; i < cc;i ++){
		if(connectfd[i].status == CLIENT_CONNECTED){
			if (close(connectfd[i].fd) == -1) {
				("Error occured in close(): %s(erro: %d)", strerror(errno), errno);
				return;
			}
		}
	}
	if (close(localfd) == -1) {
		("Error occured in close(): %s(erro: %d)", strerror(errno), errno);
		return;
	}
	printf("Server stopped. All clients will be disconnected.\n");
	exit(0);
}

char *getCurrentTime() {
	time_t tim;
	struct tm *at;
	time(&tim);
	at = localtime(&tim);
	strftime(now, 79, "%Y-%m-%d %H:%M:%S", at);
	return now;
}

void connectionHandler(int clientfd, struct sockaddr_in client) {

	/* 初始化缓冲区*/
	char outbuffer[MAX_LINE];
	char inbuffer[MAX_LINE];
	memset(outbuffer, 0, 4096 * sizeof(char));
	memset(inbuffer, 0, 4096 * sizeof(char));
	int recvpid = fork();

	// /* 建立进程通信管道 */	
	// int pipefd[2];
	// pipe(pipefd);
	// int *write_fd = &pipefd[1];
	// int *read_fd = &pipefd[0];

	if (recvpid == 0) {
		/* 子进程，接受客户端的数据并显示 */
		while (1) {
			int msglen;
			msglen = recv(clientfd, inbuffer, MAX_LINE, 0);
			if (msglen <= 0) {
				break;
			}
			inbuffer[msglen] = '\0';
			printf("<%s CLIENT %s:%d> %s", getCurrentTime(), inet_ntoa(client.sin_addr), ntohs(client.sin_port), inbuffer);
			memset(inbuffer, 0, 4096 * sizeof(char));
		}
		printf("Client %s:%d disconnected\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		//write(*write_fd, itoa(clientfd), strlen(itoa(clientfd)));
		close(clientfd);
		exit(0);
	} else {
		/* 父进程，向客户端发送数据 */
		while (1) {
			fgets(outbuffer, MAX_LINE * sizeof(char), stdin);
			if (strcmp(outbuffer, "exit\n") == 0) {
				kill(father_pid, SIGUSR1);
				break;
			}
			//printf("Writing %s (pid=%d, clientfd=%d, connnected[cc]=%d)", outbuffer, getpid(), clientfd, connectfd[0]);
			int i = 0;
			for (i = 0; i < cc; i++) {
				int len = 0;
				/* 只向活跃的连接发送 */
				if (connectfd[i].status == CLIENT_CONNECTED) {
					if ((len = send(connectfd[i].fd, outbuffer, strlen(outbuffer), 0)) < 0) {
						outbuffer[strlen(outbuffer) - 1] = '\0';
						printf("Fail to send message: %s(erro: %d)", strerror(errno), errno);
					}
					if (len == 0) {
						connectfd[i].status = CLIENT_CLOSED;
						printf("CONNECTIO_CLOSED\n");
					}
				}
			}
			memset(outbuffer, 0, 4096 * sizeof(char));
		}
		
	}
}

int main(int argc, char *argv[]) {
	printf("A simple TCP duplex communication program. Press [Ctrl] + [C] to exit.\n\n");
	char *serverport;
	if (argc == 2) {
		serverport = argv[1];
	} else {
		printf("Invalid arguments. Usage: server.o port\n");
	}
	struct sockaddr_in local;
	int sendpid = -1;
	/* 捕捉中断 */
	signal(SIGINT, closeConnect);
	signal(SIGUSR1, closeConnect);
	father_pid = getpid();
	memset(connectfd, 0, MAX_CLIENT * sizeof(int));

	/* 设置服务器地址 */
	memset(&local, 0, sizeof(local));
	local.sin_addr.s_addr = htons(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(serverport));

	/* 创建 Socket */
	if ((localfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		printf("Error occured in socket().\n");
		exit(-1);
	}

	/* 绑定地址 */
	if (bind(localfd, (struct sockaddr *)&local, sizeof(local)) == -1) {
		printf("Error occured in bind(): %s(errno: %d)\n", strerror(errno), errno);
		exit(-1);
	}

	/* 创建一个监听 socket */
	if (listen(localfd, MAX_PENDING) == -1) {
		printf("Error occured in listen(): %s(errno: %d)\n", strerror(errno), errno);
		exit(-1);
	}
	printf("Socket established. Waiting for client...\n");
	while (1) {
		
		/* 阻塞建立连接 */
		struct sockaddr_in client;
		int sin_size = sizeof(struct sockaddr_in);
		memset(&client, 0, sizeof(client));
		if (cc < MAX_CLIENT){
			if ((connectfd[cc].fd = accept(localfd, (struct sockaddr *)&client, &sin_size)) == -1) {
				printf("Error occured in accept(): %s(errno: %d)", strerror(errno), errno);
				exit(-1);
			}
			connectfd[cc++].status = CLIENT_CONNECTED;
		} else {
			printf("Max client count reached.");
			break;
		}

		/* 杀死旧的输出进程 */
		if (sendpid != -1) {
			// printf("Killing %d", sendpid);
			kill(sendpid, SIGKILL);
		}

		/* 建立新进程并处理连接，主进程继续接受连接 */
		sendpid = fork();
		// printf("%d", sendpid);
		if (sendpid == 0) {
			signal(SIGINT, NULL);
			/* 子进程处理消息 */
			close(localfd);
			int clientfd = connectfd[cc - 1].fd;
			printf("Client %s:%d connected. clientfd = %d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), clientfd);
			connectionHandler(clientfd, client);
		} else {
			//close(connectfd[cc - 1]);
			continue;
		}
	}
	int status;
	wait(&status);
	closeConnect(0);
}
