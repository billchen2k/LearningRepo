#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define SERVER_PORT 5696
#define MAX_PENDING 5
#define MAX_LINE 4096
#define MAX_CLIENT 10

int father_pid;
int localfd;
int connectfd[MAX_CLIENT];
/* Client count */
int cc = 0;
char now[64];

void closeConnect(int signum) {
	printf("Closing connection...\n");
	int i;
	for (int i = 0; i < cc; i++) {
		if (close(connectfd[i] == -1)) {
			("Error occured in close(): %s(erro: %d)", strerror(errno), errno);
			return;
		}
	}
	if (close(localfd) == -1) {
		("Error occured in close(): %s(erro: %d)", strerror(errno), errno);
		return;
	}
	printf("Server stopped.\n");
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

/* 连接服务处理，返回消息发送的进程 pid */
void reveiveHandler(int clientfd, struct sockaddr_in client) {
	/* 初始化缓冲区*/
	char inbuffer[MAX_LINE];
	char outbuffer[MAX_LINE];
	memset(inbuffer, 0, 4096 * sizeof(char));
	memset(outbuffer, 0, 4096 * sizeof(char));
	if (!fork()) {
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
		exit(-1);
	}
	else{
		while (1) {
			fgets(outbuffer, MAX_LINE * sizeof(char), stdin);
			printf("Text Got.");
			if (strcmp(outbuffer, "exit\n") == 0) {
				kill(father_pid, SIGUSR1);
				break;
			}
			int i = 0;
			for (i = 0; i < cc; i++) {
				printf("(pid=%d, clientfd=%d, connnected[i]=%d)Writing %s ", getpid(), connectfd[i], outbuffer);
				if (send(connectfd[i], outbuffer, strlen(outbuffer), 0) < 0) {
					outbuffer[strlen(outbuffer) - 1] = '\0';
					printf("Fail to send message: %s(erro: %d)", strerror(errno), errno);
				}
			}
			memset(outbuffer, 0, 4096 * sizeof(char));
		}
	}
}

int main(int argc, char *argv[]) {
	printf("A simple TCP duplex communication program. Press [Ctrl] + [C] or say 'exit' to exit.\n\n");
	struct sockaddr_in local;
	int sendpid = -1;


	/* 信号处理 */
	signal(SIGINT, closeConnect);
	signal(SIGUSR1, closeConnect);
	// signal(SIGCHLD, SIG_IGN);
	father_pid = getpid();

	memset(connectfd, 0, MAX_CLIENT * sizeof(int));

	/* 设置服务器地址 */
	memset(&local, 0, sizeof(local));
	local.sin_addr.s_addr = htons(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(SERVER_PORT);

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
		if ((connectfd[cc] = accept(localfd, (struct sockaddr *)&client, &sin_size)) == -1) {
			printf("Error occured in accept(): %s(errno: %d)", strerror(errno), errno);
			exit(-1);
		}
		cc++;

		/* 建立新进程并处理消息接受，主进程继续接受连接 */
		int pid = fork();
		if (pid == 0) {
			/* 建立子进程处理消息接收 */
			close(localfd);
			int clientfd = connectfd[cc - 1];
			printf("Client %s:%d connected. clientfd = %d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), clientfd);
			reveiveHandler(clientfd, client);
		} 
		else {
			//close(connectfd[cc - 1]);
			continue;
		}
		/* 建立一个新进程用于发送消息，杀死之前的发送进程 */
		// if (sendpid != -1) {
		// 	kill(sendpid, SIGKILL);
		// }
		// sendpid = fork();

		// if (sendpid == -1) {
		// 	printf("Error occured in fork() for send: %s(errno: %d)\n", strerror(errno), errno);
		// }

		// if (sendpid == 0) {
		// 	/* 建立子进程中处理消息发送 */
		// 	char outbuffer[MAX_LINE];
		// 	memset(outbuffer, 0, 4096 * sizeof(char));
		// 	while (1) {
		// 		printf("WHY?");
		// 		printf("SEND THREAD CREATED: PID=%d, cc=%d\n", getpid(), cc);
		// 		fgets(outbuffer, MAX_LINE * sizeof(char), stdin);
		// 		printf("Text Got.");
		// 		if (strcmp(outbuffer, "exit\n") == 0) {
		// 			kill(father_pid, SIGUSR1);
		// 			break;
		// 		}
		// 		int i = 0;
		// 		for (i = 0; i < cc; i++) {
		// 			printf("(pid=%d, clientfd=%d, connnected[i]=%d)Writing %s ", getpid(), connectfd[i], outbuffer);
		// 			if (send(connectfd[i], outbuffer, strlen(outbuffer), 0) < 0) {
		// 				outbuffer[strlen(outbuffer) - 1] = '\0';
		// 				printf("Fail to send message: %s(erro: %d)", strerror(errno), errno);
		// 			}
		// 		}
		// 		memset(outbuffer, 0, 4096 * sizeof(char));
		// 	}
		// } else {
		// 	continue;
		// }
	}
	int status;
	wait(&status);
	closeConnect(0);
}
