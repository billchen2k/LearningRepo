#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

struct www {
	int a, b;
    www(int _a, int _b){
	    a = _a;
	    b = _b;
    }
};

struct cmp{
    bool operator() (www wa, www wb){
	    return wa.a > wb.a;
    }
};

int main() {
	priority_queue<www, vector<www>, cmp> q;
	q.push(www(1, 2));
	q.push(www(3, 2));
	q.push(www(2, 4));
    while(!q.empty()){
	    www w = q.top();
	    q.pop();
	    cout << w.a << w.b << endl;
    }
	return 0;
}