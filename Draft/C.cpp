#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main() {
	pid_t pid = getpid();
	cout << pid;
	execl("/bin/cat", "cat", "/etc/passwd", (char *) 0);
	printf("EXECL ERROR");
}