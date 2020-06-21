/**
 * @file TSP1.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 使用 MPI 实现的一个树搜索问题。在这个实现中，每个进程一旦发现新的最佳回路后，要将最佳回路的代价发送给其他所有进程。其他进程相应剪枝。
 * @version 0.1
 * @date 2020-06-10 16:09
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <stack>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#define MAXL 100
#define NO_CITY 0x1f2f3f
#define INF 0x1f1f1f1f
#define ROOT 0
using namespace std;

/**
 * @brief 以邻接矩阵表示的图
 */
int G[MAXL][MAXL];
bool visited[MAXL];
bool cut[MAXL];
int gsize = 0;
long start;
/**
 * @brief 读取文件，初始化图。
 * 
 */
void init(char *graph) {
	fill(cut, cut + MAXL, 0);
	fstream fin;
	fin.open(graph, ios::in);
	fill(visited, visited + MAXL, 0);
	for (int i = 0; i < MAXL; i++) {
		for (int j = 0; j < MAXL; j++) {
			G[i][j] = 0;
		}
	}
	int a, b, c;
	while (!fin.eof()) {
		fin >> a >> b >> c;
		G[a][b] = c;
		gsize = max(gsize, a);
	}
	gsize++;
}
/**
 * @brief 打印路径
 * 
 * @param route 路径向量
 * @param cost 路径总花费
 */
void print_road(vector<int> route, int cost) {
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	printf("<Thread %d>: ", world_rank);
	for (auto i : route) {
		printf("%d->", i);
	}
	printf("0, cost = %d\n", cost);
}

/**
 * @brief 返回当前的毫秒级时间，不受线程影响。
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
 * @brief 主要的搜索函数。
 * 
 * @param rank 进程序号
 */
void tsp(int rank) {
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	stack<int> s;
	vector<int> best;
	vector<int> current;
	int bestcost = INF;
	int bestcost_global = INF;
	for (int i = gsize - 1; i > 0; i--) {
		if (i % (world_size - 1) == rank - 1) {
			s.push(i);
		}
	}
	int cost = 0;
	current.push_back(0);
	while (!s.empty()) {
		int root = s.top();
		s.pop();
		if (root == NO_CITY) {
			int tmp = current.back();
			visited[current.back()] = 0;
			current.pop_back();
			cost -= G[current.back()][tmp];
		} else {
			if (cost <= bestcost) {
				cost += G[current.back()][root];
				current.push_back(root);
				visited[root] = 1;
			} else {
				// 剪枝操作
				continue;
			}
			if (current.size() == gsize) {
				cost += G[current.back()][0];
				// print_road(current, cost);
				if (cost < bestcost) {
					best = current;
					bestcost = cost;
				}
				if (bestcost < bestcost_global) {
					bestcost_global = bestcost;
					MPI_Bcast(&bestcost_global, 1, MPI_INT, rank, MPI_COMM_WORLD);
					bestcost = min(bestcost, bestcost_global);
					printf("\033[1;35m<Thread %d>: Broadcasting shortest cost %d...\033[0m\n", rank, bestcost);
				}
				cost -= G[current.back()][0];
				int tmp = current.back();
				visited[current.back()] = 0;
				current.pop_back();
				cost -= G[current.back()][tmp];
			} else {
				s.push(NO_CITY);
				for (int i = 1; i < gsize; i++) {
					if (!visited[i]) {
						s.push(i);
					}
				}
			}
		}
	}
	printf("<Thread %d>: --------BEST TOUR FOR THREAD %d -------\n", rank, rank);
	print_road(best, bestcost);
	MPI_Send(&bestcost, 1, MPI_INT, ROOT, 1, MPI_COMM_WORLD);
}

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (argc > 1) {
		char *graphfile = argv[1];
		init(graphfile);
	} else {
		if (world_rank == 0)
			printf("Graph file not specified, using graph12.in...\n");
		init("graph12.in");
	}
	start = mtime();

	if (world_rank != ROOT) {
		tsp(world_rank);
	} else {
		printf("Calculation started.\n");
		int bestofbest = INF;
		int buf;
		for (int i = 1; i < world_size; i++) {
			MPI_Recv(&buf, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("\033[1;34m<Thread 0>: Received result from thread <%d>: %d\033[0m\n", i, buf);
			bestofbest = min(bestofbest, buf);
		}
		printf("\033[1;44m<Thread 0>: Shortest cost of all: %d\033[0m\n", bestofbest);
		printf("<Thread 0>: Time elapsed: %ld ms.\n", mtime() - start);
	}
	MPI_Finalize();
}
