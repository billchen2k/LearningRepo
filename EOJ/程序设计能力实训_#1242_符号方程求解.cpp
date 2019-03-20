#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(){
	char varied = '%';
	vector<int> position;
	int leftnum = 0, rightnum = 0;
	string input, temp;
	getline(cin, input);
	int equalPos = input.find('=');
	int pos = input.find('+', 0);
	while (input.find('+', pos) != string::npos){
		position.push_back(input.find('+', pos));
		pos = input.find('+', pos + 1);
	}
	pos = input.find('-', 0);
	while (input.find('-', pos) != string::npos){
		position.push_back(input.find('-', pos));
		pos = input.find('-', pos + 1);
	}
	position.push_back(equalPos);
	position.push_back(0);
	position.push_back(input.length());
	sort(position.begin(), position.end());
	for (int i = 0; i <= position.size() - 1; i++){
		string temp;
		temp = input.substr(position[i], position[i + 1] - position[i]);
		if (position[i] < equalPos){
			if (temp.length() == 0)
				;
			else if (temp[temp.length() - 1] >= 'a' && temp[temp.length() - 1] <= 'z'){
				varied = temp[temp.length() - 1];
				if (temp.length() == 1 || (temp.length() == 2 && temp[0] == '+'))
					leftnum += 1;
				else if (temp.length() == 2 && temp[0] == '-')
					leftnum -= 1;
				else
					leftnum += atoi((temp.substr(0, temp.length() - 1)).c_str());
			}
			else{
				rightnum -= atoi(temp.c_str());
			}
		}
		else if (position[i] == equalPos)
		{
			position[i]++;
			i--;
			continue;
		}
		else{
			if (temp.length() == 0)
				;
			else if (temp[temp.length() - 1] >= 'a' && temp[temp.length() - 1] <= 'z'){
				varied = temp[temp.length() - 1];
				if (temp.length() == 1 || (temp.length() == 2 && temp[0] == '+'))
					leftnum -= 1;
				else if (temp.length() == 2 && temp[0] == '-')
					leftnum += 1;
				else
					leftnum -= atoi((temp.substr(0, temp.length() - 1)).c_str());
			}
			else{
				rightnum += atoi(temp.c_str());
			}
		}
	}
	printf("%c=%.3f", varied, (double)rightnum / (double)leftnum);
	return 0;
}
