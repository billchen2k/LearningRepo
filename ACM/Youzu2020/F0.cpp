#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

struct node {
	string v;
	vector<node *> next;
	node(string _v) {
		v = _v;
	}
};

int num = 0;

void dfs(node *root) {
	if (root->next.size() == 0) {
		if (root->v.size() > 3) {
			if (root->v.substr(root->v.size() - 4) == ".eoj") {
				num++;
			}
		}
		return;
	}
	for (auto i : root->next) {
		dfs(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	int len;
	cin >> len;
	node *root = new node("/");
	while (len--) {
		string s;
		cin >> s;
		replace(s.begin(), s.end(), '/', ' ');
		stringstream ss(s);
		string temp;
		node *next;
		node *p = root;
		while (ss >> temp) {
			int flag = 1;
			for (auto i : p->next) {
				if (i->v == temp) {
					p = i;
					flag = 0;
					break;
				}
			}
			if (flag) {
				node *newn = new node(temp);
				p->next.emplace_back(newn);
				p = newn;
			}
		}

	}
	dfs(root);
	cout << num;
}