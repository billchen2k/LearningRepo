#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main() {
	cout << "START" << endl;
	for (int i = 0; i < 8; i++) {
		fork();
	}
	switch (fork()) {
	case -1:
		cout << "FORK FAILED.\n";
		break;
	case 0:
		printf("From the child process: %d\n", getpid());
		break;
	default:
		printf("From the parent process: %d\n", getpid());
		break;
	}
	printf("%Cloock: u\n", clock());
}
