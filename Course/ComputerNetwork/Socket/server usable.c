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
#include <time.h>
#include <signal.h>

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
	for (int i = 0; i < cc;i ++){
		if(close(connectfd[i] == -1)){
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

void connectionHandler(int clientfd, struct sockaddr_in client) {

	/* 初始化缓冲区*/
	char outbuffer[MAX_LINE];
	char inbuffer[MAX_LINE];
	memset(outbuffer, 0, 4096 * sizeof(char));
	memset(inbuffer, 0, 4096 * sizeof(char));

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
		printf("Client %s:%d disconnected", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		kill(father_pid, SIGUSR1);
	} else {
		/* 父进程，向客户端发送数据 */
		while (1) {
			if(cc == 1){
				/* 只在连接数 1 的子进程中执行 */
				fgets(outbuffer, MAX_LINE * sizeof(char), stdin);
				if (strcmp(outbuffer, "exit\n") == 0) {
					kill(father_pid, SIGUSR1);
					break;
				}
				//printf("Writing %s (pid=%d, clientfd=%d, connnected[cc]=%d)", outbuffer, getpid(), clientfd, connectfd[0]);
				int i = 0;
				for (i = 0; i < cc; i++){
					printf("(pid=%d, clientfd=%d, connnected[i]=%d)", getpid(), clientfd, connectfd[i]);
					if (send(connectfd[i], outbuffer, strlen(outbuffer), 0) < 0) {
						outbuffer[strlen(outbuffer) - 1] = '\0';
						printf("Fail to send message: %s(erro: %d)", strerror(errno), errno);
					}
				}
				memset(outbuffer, 0, 4096 * sizeof(char));
			}
		}
		
	}
}

int main(int argc, char *argv[]) {
	printf("A simple TCP duplex communication program. Press [Ctrl] + [C] or say 'exit' to exit.\n\n");
	struct sockaddr_in local;

	/* 捕捉中断 */
	signal(SIGINT, closeConnect);
	signal(SIGUSR1, closeConnect);
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

		/* 建立新进程并处理连接，主进程继续接受连接 */
		int pid = fork();
		if (pid == 0) {
			signal(SIGINT, NULL);
			/* 子进程处理消息 */
			close(localfd);
			int clientfd = connectfd[cc - 1];
			printf("Client %s:%d connected. clientfd = %d.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), clientfd);
			connectionHandler(clientfd, client);

		} else {
			//close(connectfd[cc - 1]);
			continue;
		}
	}
}
