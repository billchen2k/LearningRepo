#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main() {
	mkfifo("PIPE", 0777);
	cout << "START" << endl;
	if (!fork()) {
		printf("From the child process: %d\n", getpid());
		int readfd = open("PIPE", O_RDONLY);
		char buffer[4096];
		while (1) {
			int len = read(readfd, buffer, 4096);
			if (strcmp(buffer, "exit\n") == 0) {
				break;
			}
			printf("Received from parent process: %s\n", buffer);
		}
	} else {
		printf("From the parent process: %d\n", getpid());
		int writefd = open("PIPE", O_WRONLY | O_NONBLOCK);
		char buffer[4096];
		while (fgets(buffer, 4096, stdin)) {
			if (strcmp(buffer, "exit\n") == 0) {
				write(writefd, buffer, strlen(buffer));
				break;
			}
			write(writefd, buffer, strlen(buffer));
		}
	}
	cout << "WROTE.";
	cout << "Clock:" << clock() << endl;
}
