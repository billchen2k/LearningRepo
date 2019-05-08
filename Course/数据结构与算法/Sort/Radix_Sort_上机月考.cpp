// 2019.5.8 上机月考

#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int ENTRY_COUNT = 10;
const int MAX_CHARS = 28;
string str[] = {"rat", "mop", "cat", "map", "car", "top", "cot", "tar", "rap", "mat"};
vector<string> oriData(str, str + ENTRY_COUNT);

void printer(vector<string> &toprint) {
	for (int i = 0; i < toprint.size();i++) {
		cout << toprint[i] << " ";
	}
	cout << endl;
}

// 这两个函数第一个参数为总列表，含有所有元素
// 第二个参数为拆分之后的所有数组
void connect(vector<string> &data, vector<string> *queues) {
	data.clear();
	for (int i = 0; i < MAX_CHARS; i++){
		data.insert(data.end(), queues[i].begin(), queues[i].end());
		queues[i].clear();
	}
}

void radix_sort(vector<string> &data,vector<string> *queues) {
	for (int i = data[0].size() - 1; i >= 0; i--){
		for (int j = 0; j < data.size(); j++){
			if (data[j][i] >= 'a' && data[j][i] <= 'z') {
				queues[data[j][i] - 'a' + 1].push_back(data[j]);
			}
            else if (data[j][i] == ' ') {
				queues[0].push_back(data[j]);
			}
            else{
				queues[MAX_CHARS - 1].push_back(data[j]);
			}
		}
		cout << "第 " << i + 1 << " 次排序：";
		printer(data);
		connect(data, queues);
    }
}

int main() {
	vector<string> data;
	vector<string> queues[MAX_CHARS];
	cout << "请输入 " << ENTRY_COUNT << " 个长度为 3 的字符串，或者输入 i，使用一个内置的字符串:" << endl;
	for (int i = 0; i < ENTRY_COUNT; i++) {
		string temp;
		cin >> temp;
		if (i == 0 && temp == "i") {
			data.assign(oriData.begin(), oriData.end());
			break;
		}
		data.push_back(temp);
	}
	radix_sort(data, queues);
	cout << "使用 radix_sort() 之后：" << endl;
	printer(data);
	return 0;
}