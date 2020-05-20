/**
 * @file ompreader.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief This program implemted a producer-consumer program with OpenMP. Tested on macOS & Linux.
 * @version 1.0
 * @date 2020-05-20 14:31
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <fstream>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <time.h>
#define MAX_WORD 1000000

using namespace std;

/** Constants */
int THREAD_COUNT = 5;
int FILE_COUNT = 15;
string rootPath = "/Users/billchen/OneDrive/Workspace/LearningRepo/Course/Parallel/Homework2/";
// string rootPath = "";
/**
 * @brief Word struct, stores the word and producer thread.
 */
struct word {
	string str;
	int thread;
	int file;

	word(int t, string s, int f) {
		thread = t;
		str = s;
		file = f;
	}
	word() {
		str = "";
		thread = -1;
		file = -1;
	}
};

/**
 * @brief Queue struct. Used for message queue. Mutex lock implemted.
 */
struct queue {
	word *w;
	int queue_size;
	int pos_back, pos_front;
	int write_count, read_count;
	omp_lock_t front_mutex, back_mutex;

	void enqueue(word _w) {
		if (queue_size >= MAX_WORD) {

			return;
		}
		omp_set_lock(&back_mutex);
		w[pos_back] = _w;
		queue_size++;
		pos_back++;
		write_count++;
		omp_unset_lock(&back_mutex);
	}

	int dequeue(word &_w) {
		omp_set_lock(&front_mutex);
		if (queue_size == 0) {
			w->thread = -1;
			omp_unset_lock(&front_mutex);
			return -1;
		} else {
			word rw = w[pos_front];
			pos_front++;
			queue_size = queue_size == 0 ? 0 : queue_size - 1;
			read_count++;
			_w = rw;
		}
		omp_unset_lock(&front_mutex);
		return 0;
	}

	queue() {
		w = new word[MAX_WORD];
		queue_size = pos_back = pos_front = write_count = read_count = 0;
		omp_init_lock(&front_mutex);
		omp_init_lock(&back_mutex);
	}

	void reset() {
		queue_size = pos_back = pos_front = write_count = read_count = 0;
	}
};

queue Q;
int done = 0;

/**
 * @brief  Get current time as HH:mm:ss.ms format.
 * 
 * @return char* 
 */
string get_ftime() {
	time_t t = time(NULL);
	struct tm *stime = localtime(&t);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int ms = tv.tv_usec / 1000;
	char time[32]{0};
	snprintf(time, sizeof(time), "%02d:%02d:%02d.%02d", stime->tm_hour, stime->tm_min, stime->tm_sec, ms);
	return time;
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

/**
 * @brief Print information for comsumer.
 * 
 * @param thread Thread number
 * @param str String to print
 */
void print_consumer(int thread, word &w) {
	string time = get_ftime();
	printf("<%s Consumer #%d>: Read from producer #%d file #%d - %s\n",
	       time.c_str(), thread, w.thread, w.file, w.str.c_str());
}

/**
 * @brief Print information for producer.
 * 
 * @param w  Word to print.
 */
void print_producer(word &w) {
	string time = get_ftime();
	printf("<%s Producer #%d>: Write into queue from file #%d - %s\n",
	       time.c_str(), w.thread, w.file, w.str.c_str());
}

int main() {

start:
	char ch;
	cout << "Specify thread count (leave empty to use default value " << THREAD_COUNT << ", should be at least 2.): ";
	if ((ch = cin.get()) != '\n') {
		cin.putback(ch);
		cin >> THREAD_COUNT;
		cin.get();
	}

	long start = mtime();
#pragma omp parallel num_threads(THREAD_COUNT) shared(done, Q)
	{
#pragma omp for
		for (int i = 0; i < THREAD_COUNT; i++) {
			if (i < (THREAD_COUNT + 1) / 2) {
				printf("Producer #%d at work.\n", omp_get_thread_num());
				// Producer
				for (int j = 0; j < FILE_COUNT; j++) {
					if (omp_get_thread_num() % (THREAD_COUNT + 1) / 2 == i) {
						ifstream ifs;
						ifs.open(rootPath + "text/" + to_string(j) + ".txt");
						while (!ifs.eof()) {
							string t;
							ifs >> t;
							if (t.size() < 1)
								continue;
							word w(omp_get_thread_num(), t, j);
							Q.enqueue(w);
#pragma omp critical
							print_producer(w);
						}
					}
				}
				printf("Producer #%d off work.\n", omp_get_thread_num());
#pragma omp critical
				done++;
			} else {
				// Comsumer
				printf("Comsumer #%d at work.\n", omp_get_thread_num());
				word w;
				while (Q.dequeue(w) == 0 || done != (THREAD_COUNT + 1) / 2) {

					if (w.thread != -1)
#pragma omp critical
						print_consumer(omp_get_thread_num(), w);
				}
				printf("Consumer #%d off work.\n", omp_get_thread_num());
			}
		}
	}


	printf("%-16s|%-15s\n", "Attribute", "Value");
	printf("----------------|---------------\n");
	printf("%-16s|%-15d\n", "Thread count", THREAD_COUNT);
	printf("%-16s|%-15d\n", "Message sent", Q.write_count);
	printf("%-16s|%-15d\n", "Message read", Q.read_count);
	printf("%-16s|%ld ms\n", "Time elapsed", mtime() - start);
	printf("Finished. [r] to restart or any other key to exit...\n");
	ch = cin.get();
	if (ch == 'R' || ch == 'r') {
		cin.get();
		done = 0;
		Q.reset();
		goto start;
	}
	cout << "Bye." << endl;
	return 0;
}