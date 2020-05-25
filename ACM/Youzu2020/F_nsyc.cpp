#include <algorithm>
#include <iostream>
#include <queue>
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
		d = 0;
	}
	int d = 0;
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
	vector<string> d;
	vector<string> r;
	node *root = new node("/");
	while (len--) {
		string s;
		cin >> s;
		replace(s.begin(), s.end(), '/', ' ');
		stringstream ss(s);
		string temp;
		node *p = root;
		while (ss >> temp) {
			int yes = 0;
			if (temp.size() > 3) {
				if (temp.substr(temp.size() - 4) == ".eoj") {
					yes = 1;
				}
			}
			int flag = 1;
			for (int t = 0; t < p->next.size(); t++) {
				node *i = p->next[t];
				if (i->v == temp) {
					p = i;
					flag = 0;
					if (i->d == 0) {
						i->d = 1;
						if (yes) {
							num--;
						}
					}
					break;
				}
			}
			if (flag) {
				node *newn = new node(temp);
				p->next.push_back(newn);
				p = newn;
				if (yes) {
					num++;
				}
			}
		}
	}
	//dfs(root);
	cout << num;
}