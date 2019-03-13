#include <iostream>
#include "myQueue.h"
using namespace std;
void cleanstream(){
	while (cin.get() != '\n')
		continue;
}
void insturct(){
	cout << "Welcome to the Queue Demonstrator. " << endl
		 << "Now you can enter the following commands and operate with a char." << endl
		 << "[A] Append" << endl
		 << "[R] Retrive" << endl
		 << "[S] Serve" << endl
		 << "[L] Return the length" << endl
		 << "[P] Print the queue" << endl
		 << "[C] Clean all elements" << endl
		 << "[H] Help" << endl
		 << "[Q] Quit" << endl;
}

int main(){
	myQueue data;
	insturct();
	char command;
	while((command = toupper(cin.get()))!='Q'){
		cleanstream();
		switch (toupper(command)){
			case 'A':
				char cha;
				cha = cin.get();
				if(data.append(cha)==0){
					cout << "Done." << endl;
				}
				cleanstream();
				break;
			case 'R':
				char chr;
				if((chr = data.retrieve())!=ERROR_QUEUEEMPTY){
					cout << chr << endl;
					cout << "Done." << endl;
				}
				break;
			case 'S':
				if(data.serve()==0){
					cout << "Done." << endl;
				}
				break;
			case 'L':
				cout << data.size() << endl;
				break;
			case 'P':
				data.print();
				break;
			case 'C':
				data.clear();
				cout << "Done." << endl;
				break;
			case 'H':
				insturct();
				break;
			default:
				cout << "Unknown Command." << endl;
		}
	}
	cout << "Bye." << endl;
	return 0;
}