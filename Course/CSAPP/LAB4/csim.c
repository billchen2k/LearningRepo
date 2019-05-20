#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MACHINE_BITS 64
#define NEED_EVICT -1
#define NO_MATCH -2
#define CACHED 1
#define ADD_HIT 1
#define ADD_MISS 2
#define ADD_EVICT 3

int totalMissCount = 0;
int totalHitCount = 0;
int totalEvictCount = 0;
typedef unsigned long ulong;
typedef unsigned char *bytept;
const char *optString = "s:E:b:t:hv";
struct globalOptions {
	int setIndexBits;
	int associativity;
	int blockBits;
	int verboseFlag;
	int tagBits;
	char *traceDir;
} globalOptions;
struct result {
	int hit;
	int miss;
	int evict;
};
void usage() {
	printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
	printf("-h get help info\n");
	printf("-v Optional verbose flag that displays trace info\n");
	printf("-s <s> Number of set index bits\n");
	printf("-E <E> Associativity (number of lines per set)\n");
	printf("-b <b> Number of block bits\n");
	printf("-t <tracefile>: Name of the valgrind trace to replay\n");
}
typedef struct {
	int valid;
	ulong tag;
	clock_t time;
} CacheLine;

typedef CacheLine *CacheSet;
typedef CacheSet *CacheHead;

CacheHead CacheInit(int S, int E) {
	CacheHead cache;
	cache = calloc(1 << S, sizeof(CacheSet));
	if (cache == NULL) {
		printf("Fail to allocate memory for cache.");
		exit(EXIT_FAILURE);
	}
	int i = 0;
	for (i = 0; i < 1 << S; i++) {
		if ((cache[i] = calloc(E, sizeof(CacheLine))) == NULL) {
			printf("Fail to allocate memory for cache.");
			exit(EXIT_FAILURE);
		}
	}
	for (i = 0; i < 1 << S; i++) {
		int j;
		for (j = 0; j < E; j++) {
			cache[i][j].valid = 0;
		}
	}
	return cache;
}

int CacheJudge(CacheHead cache, ulong index, ulong tag) {
	int i;
	int fullFlag = 1;
	int matchFlag = 0;
	for (i = 0; i < globalOptions.associativity; i++) {
		if (cache[index][i].valid == 0) {
			fullFlag = 0;
		}
		if (cache[index][i].tag == tag && cache[index][i].valid == 1) {
			matchFlag = 1;
		}
	}
	if (matchFlag == 1)
		return CACHED;
	if (fullFlag == 1)
		return NEED_EVICT;
	else
		return NO_MATCH;
}

void CacheInsert(CacheHead cache, ulong index, ulong tag) {
	int freeLine = 0, i;
	for (i = 0; i < globalOptions.associativity; i++) {
		if (cache[index][i].valid == 0)
			break;
		freeLine++;
	}
	// CacheLine *target = cache[index] + freeLine;
	// target->tag = tag;
	// target->valid = 1;
	// target->time = clock();
	cache[index][freeLine].tag = tag;
	cache[index][freeLine].valid = 1;
	cache[index][freeLine].time = clock();
}

void CacheEvict(CacheHead cache, ulong index, ulong tag) {
	int firstLine = 0, i = 0;
	clock_t firstCachedTime = cache[index][i].time;
	for (i = 0; i < globalOptions.associativity; i++) {
		if (cache[index][i].time < firstCachedTime) {
			firstCachedTime = cache[index][i].time;
			firstLine = i;
		}
	}
	CacheLine *target = cache[index] + firstLine;
	target->tag = 0;
	target->time = 0;
	target->valid = 0;
}

void Adder(int type, int num) {
	int v = globalOptions.verboseFlag;
	switch (type) {
	case ADD_EVICT:
		totalEvictCount += num;
		if (v && num != 0)
			printf("eviction ");
		break;
	case ADD_HIT:
		totalHitCount += num;
		if (v && num != 0)
			printf("hit ");
		break;
	case ADD_MISS:
		totalMissCount += num;
		if (v && num != 0)
			printf("miss ");
	}
}
void printByte(bytept h, int len){
	int i;
	for (i = 0; i < len; i++)
		printf("%.2x ", h[i]);
	printf("\n");
}
void Execute(CacheHead cache, char type, ulong address, int len) {
	//ulong index = (address >> globalOptions.blockBits) & ((1 << globalOptions.setIndexBits) - 1);
	ulong index = (address << globalOptions.tagBits) >> (MACHINE_BITS - globalOptions.setIndexBits);
	ulong tag = address >> (globalOptions.blockBits + globalOptions.setIndexBits);
	int status = CacheJudge(cache, index, tag);
	if (globalOptions.verboseFlag == 1) {
		printf("\n[address:] ");
		printByte((bytept)&address, sizeof(long));
		printf("[index:] ");
		printByte((bytept)&index, sizeof(long));
		printf("[tag:] ");
		printByte((bytept)&tag, sizeof(long));
		printf("(Decimal)[index: %ld, tag: %ld] \n", index, tag);
	}
	switch (status) {
	case CACHED:
		if (type == 'M') {
			Adder(ADD_HIT, 2 * len);
		} else {
			Adder(ADD_HIT, 1);
		}
		break;
	case NO_MATCH:
		CacheInsert(cache, index, tag);
		if (type == 'M') {
			Adder(ADD_MISS, 1);
			Adder(ADD_HIT, 2 * len - 1);
		} else {
			Adder(ADD_MISS, 1);
			Adder(ADD_HIT, len - 1);
		}
		break;
	case NEED_EVICT:
		CacheEvict(cache, index, tag);
		CacheInsert(cache, index, tag);
		if (type == 'M') {
			Adder(ADD_MISS, 1);
			Adder(ADD_EVICT, 1);
			Adder(ADD_HIT, 2 * len - 1);
			
		}
		else {
			Adder(ADD_MISS, 1);
			Adder(ADD_EVICT, 1);
			Adder(ADD_HIT, len - 1);
		}
		break;
	default:
		printf("Unknown error.\n");
		exit(EXIT_FAILURE);
	}
	if (globalOptions.verboseFlag == 1) {
		printf("\n");
	}
}

int main(int argc, char *args[]) {
	char ch;
	while ((ch = getopt(argc, args, optString)) != -1) {
		switch (ch) {
		case 's':
			if (atoi(optarg) < 0) {
				printf("Unvalid input. Try Again.");
				exit(EXIT_FAILURE);
			}
			globalOptions.setIndexBits = atoi(optarg);
			break;
		case 'E':
			if (atoi(optarg) < 0) {
				printf("Unvalid input. Try Again.");
				exit(EXIT_FAILURE);
			}
			globalOptions.associativity = atoi(optarg);
			break;
		case 'b':
			if (atoi(optarg) < 0) {
				printf("Unvalid input. Try Again.");
				exit(EXIT_FAILURE);
			}
			globalOptions.blockBits = atoi(optarg);
			break;
		case 't':
			globalOptions.traceDir = optarg;
			break;
		case 'v':
			globalOptions.verboseFlag = 1;
			break;
		case 'h':
			usage();
			exit(EXIT_FAILURE);
		default:
			usage();
			exit(EXIT_FAILURE);
			break;
		}
	}
	globalOptions.tagBits = MACHINE_BITS - globalOptions.blockBits - globalOptions.setIndexBits;
	FILE *traceFile = fopen(globalOptions.traceDir, "r");
	if (traceFile == NULL) {
		printf("Fail to open file: %s\n", globalOptions.traceDir);
		exit(EXIT_FAILURE);
	}

	CacheHead cache = CacheInit(globalOptions.setIndexBits, globalOptions.associativity);
	char traceLine[32];
	while (fgets(traceLine, 32, traceFile) != NULL) {
		if (globalOptions.verboseFlag == 1) {
			char *p = traceLine;
			while(*p != '\n'){
				putchar(*p);
				p++;
			}
			putchar(' ');
		}
		char mode;
		ulong address;
		int len;
		sscanf(traceLine, " %c %lx,%d", &mode, &address, &len);
		if (mode == 'I')
			continue;
		Execute(cache, mode, address, len);
	}
	//printf("hits:%d misses:%d evictions:%d\n", totalHitCount, totalMissCount, totalEvictCount);
	printSummary(totalHitCount, totalMissCount, totalEvictCount);
	return 0;
}
