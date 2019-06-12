# 第十三讲 信号

> 101085101210 陈俊潼

## 8.7

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void sigint_handler(int sig) {
	return;
}
unsigned int snooze(unsigned int secs) {
	int rc = sleep(secs);
	printf("Slept for %d of %d secs.\n", secs - rc, secs);
	return rc;
}
int main(int argc, char *args[]) {
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
	    printf("Error setting signals.\n.");
	    exit(-1);
    }
    if (argc != 2) {
	    printf("Parameter error.\n");
	    exit(-1);
	}
	snooze(atoi(args[1]));
	return 0;
}
```