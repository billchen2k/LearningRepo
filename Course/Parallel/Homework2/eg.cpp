#include <iostream>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int thread_count;
int send_max;
int done_sending;

struct MesgQueue {
	int *mesg;
	int enqueued, dequeued;
	omp_lock_t front_mutex, back_mutex;
};
struct MesgQueue *Msg;

void Enqueue(int dest, int mesg) {
	int cur_p = omp_get_thread_num();
	printf("Thread %d send message %d to %d success!\n",cur_p, mesg, dest);
	Msg[dest].mesg[Msg[dest].enqueued] = mesg;
	Msg[dest].enqueued++;
}

void Dequeue(int dest) {
	printf("Thread %d receive message %d success!\n", dest, Msg[dest].mesg[Msg[dest].dequeued]);
	Msg[dest].dequeued++;
}

void Send_msg() {
	int mesg = rand();
	int dest = rand() % thread_count;
	//#pragma omp critical
	omp_set_lock(&Msg[omp_get_thread_num()].back_mutex);
	Enqueue(dest, mesg);
	omp_unset_lock(&Msg[omp_get_thread_num()].back_mutex);
}

void Try_receive() {
	int cur_p = omp_get_thread_num();
	int queue_size = Msg[cur_p].enqueued - Msg[cur_p].dequeued;
	if (queue_size == 0)
		return;

	else if (queue_size == 1) {
		//#pragma omp critical
		Dequeue(cur_p);
	} else {
		Dequeue(cur_p);
	}
}

int Done() {
	int cur_p = omp_get_thread_num();
	int queue_size = Msg[cur_p].enqueued - Msg[cur_p].dequeued;
	if (queue_size == 0 && done_sending == thread_count)
		return 1;
	else
		return 0;
}

void init(MesgQueue *MQ) {
	MQ->mesg = new int[send_max];
	MQ->dequeued = 0;
	MQ->enqueued = 0;
	omp_init_lock(&(MQ->front_mutex));
	omp_init_lock(&(MQ->back_mutex));
}

void destroy() {
	delete[] Msg;
}

int main(int argc, char *argv[]) {

	// if (argc != 2)
	// 	printf("Error Command!\n"), exit(0);
	// thread_count = strtol(argv[1], NULL, 10);
	thread_count = 2;
	printf("thread_count = %d, Input the number of message:\n", thread_count);
	cin >> send_max;

	Msg = new MesgQueue[thread_count];

	srand((unsigned)time(NULL));
	int sent_msgs, i;
	clock_t s = clock();
#pragma omp parallel num_threads(thread_count)
	{
#pragma omp for
		for (i = 0; i < thread_count; ++i)
			init(&Msg[omp_get_thread_num()]);

#pragma omp barrier

#pragma omp for private(sent_msgs)
		for (i = 0; i < thread_count; ++i) {

			for (sent_msgs = 0; sent_msgs < send_max; ++sent_msgs) {
				Send_msg();
				Try_receive();
			}
		 printf("thread %d send message done!\n", omp_get_thread_num());
#pragma omp atomic
			done_sending++;

			while (!Done()) {
				Try_receive();
			}
		}
	}
	destroy();
	clock_t e = clock();
	printf("Running time is: %dms\n", e - s);
	return 0;
}