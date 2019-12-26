#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main() {
	mkfifo("PIPE", 0777);
	cout << "START" << endl;
	sleep(1);
	if(!fork()){
		printf("From the child process: %d\n", getpid());
		int readfd = open("PIPE", O_RDONLY );
		char *buffer;
		read(readfd, buffer, 4096);
		printf("Received from parent process: %s", buffer);
	}
	else{
		printf("From the parent process: %d\n", getpid());
		int writefd = open("PIPE", O_WRONLY);
		char buffer[4096];
		fgets(buffer, 4096, stdin);
		write(writefd, buffer, strlen(buffer));
	}
	printf("%Cloock: ul\n", clock());
}
