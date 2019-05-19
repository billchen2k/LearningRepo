#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int totalMissCount = 0;
int totalHitCount = 0;
int totalEvictCount = 0;

struct options{
	int S;
	int E;
	int b;
	char *traceDir;
};
int main(int argc, char *args[]) {
	char ch;
    while((ch = getopt(argc, args, "s")) != -1){
	    printf("%c", ch);
	    switch (ch) {
	    case 's':
		    printf("Bravo!!!");
		    break;
	    }
    }
	char *filedir = args[1];
	FILE *traceFile = fopen(filedir, "r");
	char line[1024];
	while (fgets(line, 1024, traceFile)!=NULL){
		printf("%s", line);
    }
    printf("%d\n", argc);
    printf("%s\n", args[0]);
    printSummary(0, 0, 0);
    return 0;
}
