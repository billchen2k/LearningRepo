#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

typedef pair<int, int> P;

char MAP[10][10];

vector<P> furs;

char dirs[4] = {'U', 'L', 'R', 'D'};
vector<P> dirp = {make_pair(-1, 0), make_pair(0, -1), make_pair(0, 1), make_pair(1, 0)};
vector<P> outOrder;
vector<char> outDirection;

void move(P fur, int d, int f) {
	int i = fur.first, j = fur.second;
	while (MAP[i + dirp[d].first][j + dirp[d].second] != 'O') {
		i += dirp[d].first;
		j += dirp[d].second;
	}
	MAP[fur.first][fur.second] = 'X';
	MAP[i + dirp[d].first][j + dirp[d].second] = 'X';
	MAP[i][j] = 'O';
	furs[f] = P(i, j);
}

int getNext(int i){
	i = (i < furs.size() - 1) ? i + 1 : 0;
	while(find(outOrder.begin(), outOrder.end(), furs[i]) != outOrder.end()){
		i = (i < furs.size() - 1) ? i + 1 : 0;
	}
	return i;
}

bool check(P fur, int d) {
	// Bondary check
	if (fur.first + dirp[d].first < 0 || fur.second + dirp[d].second < 0) {
		return false;
	}
	// Adjacent check
	if (MAP[fur.first + dirp[d].first][fur.second + dirp[d].second] == 'O') {
		return false;
	}
	// Target check
	int i = fur.first, j = fur.second;
	do {
		i += dirp[d].first;
		j += dirp[d].second;
		if (MAP[i][j] == 'O') {
			return true;
		}
	} while (i < 7 && j < 8 && i > 0 && j > 0);
	return false;
}

char now[10][10];
vector<P> nowfurs;
int done;
bool dfs(int f) {
	if (outOrder.size() + 1 == furs.size()) {
		// print result
		for (int i = 0; i < outOrder.size(); i++) {
			printf("%d %d %c\n", outOrder[i].first, outOrder[i].second, outDirection[i]);
		}
		return true;
	}
	for (int i = 0; i < 4; i++) {
		if (check(furs[f], i)) {
			outOrder.push_back(furs[f]);
			outDirection.push_back(dirs[i]);
			// Backup status
			memcpy(now, MAP, sizeof(MAP));
			nowfurs.clear();
			nowfurs.assign(furs.begin(), furs.end());
			move(furs[f], i, f);
			if (dfs(getNext(f))) {
				return true;
			}
			else{
				return false;
			}
		}
	}
	// All direction fails
	if(outOrder.size() != 0){
		// Drawback
		outOrder.pop_back();
		outDirection.pop_back();
		// Restore map status
		memcpy(MAP, now, sizeof(MAP));
		furs.clear();
		furs.assign(nowfurs.begin(),nowfurs.end());
		dfs(f);
	}
	else{
		// Don't move this time
		dfs(getNext(f));
	}
	return false;
}

void clear(){
	done = 0;
	memset(MAP, 0, sizeof(MAP));
	memset(now, 0, sizeof(now));
	outOrder.clear();
	furs.clear();
	outDirection.clear();
}

int main() {
	while (!cin.eof()) {
		clear();
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 8; j++) {
				char tmp;
				tmp = cin.get();
				MAP[i][j] = tmp;
				if (tmp == 'O') {
					furs.push_back(P(i, j));
				}
			}
			cin.get();
		}
		dfs(0);
		cout << "Done." << endl;
	}
	return 0;
}