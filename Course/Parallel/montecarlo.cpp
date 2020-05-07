/**
 * @file montecarlo.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief This pthread multi-thread program is used to calculate value of Pi using Monter Carlo method.
 * 		  Tested on macOS & Linux.
 * @version 1.0
 * @date 2020-05-07 21:06
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <cmath>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <random>
#include <sys/time.h>
using namespace std;

long DEGREE = 100000000;	 	// Times to calculate.
long THREAD_COUNT = 15; 	// Thread count.
long countIn = 0;	 		// Times the dot falls into the circle.
long runningThreads = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Used to get a random double number between -1 and 1.
 * 
 * @return double 
 */
double
frand() {
	double f = double(rand()) / RAND_MAX;
	return -1 + 2 * f;
}

/**
 * @brief Calculate the distance between (0,0) and (x,y).
 * 
 * @param x X cordinate value
 * @param y Y cordinate value
 * @return double distance.
 */
double distance(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

/**
 * @brief Monte Carlo method. Multi-thread supported.
 * 
 * @param count How many times to compute.
 */
void *montecarlo(void *c) {
	srand(clock());
	int count = *(int *)c;
	int myCount = 0;
	for (int i = 0; i < count; i++) {
		double d = distance(frand(), frand());
		if (d <= 1) {
			myCount++;
		}
	}
	pthread_mutex_lock(&m);
	countIn+=myCount;
	runningThreads--;
	pthread_mutex_unlock(&m);
}

/**
 * @brief Return time in millseconds.
 * 
 * @return long 
 */
long mtime() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long ms = tp.tv_sec * 1000L + tp.tv_usec / 1000;
	return ms;
}


int main() {
start:
	countIn = 0;
	char ch;
	cout << "Specify thread count (leave empty to use default value " << THREAD_COUNT << "): ";
	if ((ch = cin.get()) != '\n') {
		cin.putback(ch);
		cin >> THREAD_COUNT;
		cin.get();
	}
	cout << "Specify degree (leave empty to use default value " << DEGREE<< "): ";
	if ((ch = cin.get()) != '\n') {
		cin.putback(ch);
		cin >> DEGREE;
		cin.get();
	}
	cout << "Computing..." << endl;
	long start, end;
	start = mtime();
	pthread_t *pid = new pthread_t[THREAD_COUNT];
	int tasknum = DEGREE / THREAD_COUNT;
	for (int i = 0; i < THREAD_COUNT; i++) {
		runningThreads++;
		pthread_create(&pid[i], NULL, montecarlo, &tasknum);
	}
	int p = runningThreads;
	// for (int i = 0; i < THREAD_COUNT; i++){
	// 	pthread_join(pid[i], NULL);
	// }
	while (runningThreads) {
		if (p != runningThreads) {
			//cout << runningThreads << endl;
			p = runningThreads;
		}
		continue;
	}
	double pi = 4 * double(countIn) / (THREAD_COUNT * tasknum);
	end = mtime();
	printf("%-16s|%-15s\n", "Attribute", "Value");
	printf("----------------|---------------\n");
	printf("%-16s|%-15ld\n", "Degree", DEGREE);
	printf("%-16s|%-15ld\n", "Thread count", THREAD_COUNT);
	printf("%-16s|%-15ld\n", "In circle", countIn);
	printf("%-16s|%-15ld\n", "Out of circle", THREAD_COUNT * tasknum - countIn);
	printf("%-16s|%ld ms\n", "Time elapsed", end - start);
	printf("%-16s|%.10f\n", "Pi", pi);
	printf("Finished. [r] to restart or any other key to exit...\n");
	ch = cin.get();
	if (ch == 'R' || ch == 'r') {
		cin.get();
		goto start;
	}
	pthread_mutex_destroy(&m);
	return 0;
}