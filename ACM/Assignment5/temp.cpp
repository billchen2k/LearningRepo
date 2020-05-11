#include <iostream>
#include <vector>

using namespace std;

const long MAX_V = 2e5;

struct vertex {
	vector<vertex *> edge;
};

vertex G[MAX_V];