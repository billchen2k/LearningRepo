#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
int main(){
	struct stat stat;
	char *bufp;
	int fd = open("/Users/billchen/OneDrive\ -\ stu.ecnu.edu.cn/Workspace/LearningRepo/Course/CSAPP/Chapter9Work/hello.txt", O_RDWR, 0);
	fstat(fd, &stat);
	bufp = mmap(NULL, stat.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	*bufp = 'J';
	munmap(bufp, stat.st_size);
	return 0;
}