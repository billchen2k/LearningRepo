#include <stdio.h>
#include <unistd.h>

int main(){
	int t = 3;
	pid_t pid, pid1;
	pid = fork();
	if (pid == 0) {
		t *= t;
		printf("child: %d", t);
    }
    else{
	    wait(NULL);
	    printf("parent: %d", t);
    }
}