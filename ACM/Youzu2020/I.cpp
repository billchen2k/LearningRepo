#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

using namespace std;
// std::vector<size_t> build(const std::string &s) {
// 	std::vector<std::pair<std::string, size_t>> suffixes;
// 	for (size_t i = 0; i < s.length(); ++i) {
// 		suffixes.emplace_back(s.substr(i), i);
// 	}
// 	std::sort(suffixes.begin(), suffixes.end());
// 	std::vector<size_t> sa(s.length());
// 	for (size_t i = 0; i < s.length(); ++i) {
// 		sa[i] = suffixes[i].second;
// 	}
// 	return sa;
// }

int main(){
	int l, p;
	cin >> l >> p;
	string s = "";
	string a(p, 'a');
	string b(l - p, 'z');
	s = a + b;
	s[0] = 'n';
	cout << s;
	// build(s);
	return 0;
}