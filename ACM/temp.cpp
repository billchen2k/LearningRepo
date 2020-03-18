#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	map<string, int> mymap;
	mymap.insert(make_pair("abc", 2));
	mymap.insert(make_pair("rcd", 3));
	mymap["tester"] = 4;
	mymap["tester"] = 5;
	for (map<string, int>::iterator it = mymap.begin(); it != mymap.end(); it++) {
		cout << it->first << ":" << it->second << endl;
		cout << mymap.count("abc");
	}
}