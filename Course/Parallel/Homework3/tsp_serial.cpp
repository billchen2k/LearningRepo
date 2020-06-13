/**
 * @file TSP1.cpp
 * @author Bill Chen (Bill.Chen@live.com)
 * @brief 使用 MPI 实现的一个树搜索问题。在这个实现中，使用的是一个简单的串行程序。
 * @version 0.1
 * @date 2020-06-10 16:09
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#define MAXL 100
#define NO_CITY 0x1f2f3f
#define INF 0x1f1f1f1f
using namespace std;

/**
 * @brief 以邻接矩阵表示的图
 */
int G[MAXL][MAXL];
bool visited[MAXL];

int gsize = 0;

/**
 * @brief 读取文件，初始化图。
 * 
 */
void init() {
	fstream fin;
	fin.open("/Users/billchen/OneDrive/Workspace/LearningRepo/Course/Parallel/Homework3/graph10.in", ios::in);
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

int main() {
	init();
	long start = mtime();
	stack<int> s;
	vector<int> best;
	vector<int> current;
	int bestcost = INF;
	// for (int i = gsize - 1; i > 0; i--) {
	// 	s.push(i);
	// }
	s.push(8);
	int cost = 0;
	current.push_back(0);
	current.push_back(3);
	current.push_back(2);
	while (!s.empty()) {
		int root = s.top();
		s.pop();
		if (root == NO_CITY) {
			int tmp = current.back();
			visited[current.back()] = 0;
			current.pop_back();
			cost -= G[current.back()][tmp];
		} else {
			cost += G[current.back()][root];
			current.push_back(root);
			visited[root] = 1;
			if (current.size() == gsize) {
				cost += G[current.back()][0];
				print_road(current, cost);
				if (cost < bestcost) {
					best = current;
					bestcost = cost;
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

	printf("--------BEST-------\n");
	print_road(best, bestcost);
	printf("Time elapsed: %ld ms.\n", mtime() - start);
}
