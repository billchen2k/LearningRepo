#include <algorithm>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
using namespace std;
string a = "01689";
string b = "01986";

vector<int> assignBikes(vector<vector<int>> &workers, vector<vector<int>> &bikes) {
	vector<vector<int>> distance;
	for (int i = 0; i < workers.size(); i++) {
		for (int j = 0; j < workers.size(); j++) {
			distance[i][j] = abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][0]);
		}
	}
	int workernow = 0, bikenow = 0;
	vector<int> output;
	int store[1000];
	int assigned = 0;
	while (assigned < workers.size()) {
		workernow = bikenow = 0;
		for (int i = 0; i < workers.size() - assigned; i++) {
			for (int j = 0; j < workers.size() - assigned; j++) {
				if (distance[i][j] < distance[workernow][bikenow]) {
					workernow = i;
					bikenow = j;
				}
			}
		}
		store[workernow] = bikenow;
		assigned++;
		distance.erase(distance.begin() + workernow);
		for (int i = 0; i < workers.size() - assigned;i++){
			distance[i].erase(distance[i].begin() + bikenow);
		}
    }
    for (int i = 0; i < assigned;i++){
	    output.push_back(store[i]);
    }
    return output;
}
int main() {
    vector<vector<int>> a = {}
}