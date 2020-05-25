#include <algorithm>
#include <cstdio>
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
	int len;
	scanf("%d", &len);
	vector<string> d;
	vector<string> r;
	node *root = new node("/");
	while (len--) {
		char s[1000005];
		scanf("%s", s);
		int slen = 0;
		for (int i = 0; i < strlen(s); i++) {
			if (s[i] == '/') {
				s[i] = ' ';
				slen++;
			}
		}
		char temp[1000005];
		char *sp = s;
		node *next;
		node *p = root;
		while (slen--) {
			int add;
			sscanf(sp, "%s%n", temp, &add);
			sp = sp + add;
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

		// node *next;
		// node *p = root;
		// while (ss >> temp) {
		// 	int flag = 1;
		// 	for (auto i : p->next) {
		// 		if(i->v == temp){
		// 			p = i;
		// 			flag = 0;
		// 			break;
		// 		}
		// 	}
		// 	if(flag) {
		// 		node *newn = new node(temp);
		// 		p->next.emplace_back(newn);
		// 		p = newn;
		// 	}
		// }

		// if (s.size() > 3) {

		// 	int pos = 0;
		// 	vector<int> poss;
		// 	while ((pos = s.find(".eoj", pos)) != string::npos) {
		// 		if (pos + 4 == s.size()) {
		// 			poss.push_back(pos);
		// 		} else if (s[pos + 4] == '/') {
		// 			poss.push_back(pos);
		// 		}
		// 		pos++;
		// 	}
		// 	for (int i = 0; i < poss.size(); i++) {
		// 		if (poss[i] != s.size() - 4) {
		// 			d.push_back(s.substr(0, poss[i] + 4));
		// 			auto ii = r.begin();
		// 			ii = find(r.begin(), r.end(), s.substr(0, poss[i] + 4));
		// 			if (ii != r.end()) {
		// 				r.erase(ii);
		// 				num--;
		// 			}
		// 		} else {
		// 			if (find(d.begin(), d.end(), s) == d.end()) {
		// 				r.push_back(s);
		// 				num++;
		// 			}
		// 		}
		// 	}

		// 	if (s.substr(s.size() - 4) == ".eoj") {
		// 		num++;
		// 	}
		// 	vector<string> sv;
		// replace(s.begin(), s.end(), '/', ' ');
		// stringstream ss(s);
		// string temp;
		// while (ss >> temp) {
		// 	sv.push_back(temp);
		// }
		// for (int i = 0; i < sv.size() - 1; i++) {
		// 	if(sv[i].size() < 4){
		// 		continue;
		// 	}
		// 	if (sv[i].substr(sv[i].size() - 4) == ".eoj") {
		// 		d.push_back(sv[i]);
		// 	}
		// }
		// if (sv[sv.size() - 1].size() < 5) {
		// 	continue;
		// }
		// if (sv[sv.size() - 1].substr(sv[sv.size() - 1].size() - 4) == ".eoj") {
		// 	if (find(d.begin(), d.end(), sv[sv.size() - 1]) == d.end()) {
		// 		num++;
		// 	}
		// }
		// }
	}
	dfs(root);
	cout << num;
}