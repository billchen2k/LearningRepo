#include <iostream>
#include <queue>
#include <unistd.h>
using namespace std;
typedef int feedback;
enum flightStatus {null, arriving, departing};
const int ERROR_FULL = 101;
const int ERROR_
class Runaway{
  private:
	queue<Plane> data;

  public:
	int Append();
};
class Plane{
private:
  int ID;

};
void initilize(int &total_time, int &queue_limit, float &arriving_rate, float &departure_rate){
    cout << "\033[42mPlease enter how many time units you will simulate:\033[0m\n" << flush;
    cin >> total_time;
    cout << "How many flights can be waiting in a queue?" << endl << flush;
    cin >> queue_limit;
    cout << "What is the expected arriving flights per unit time?" << endl << flush;
    cin >> arriving_rate;
    cout << "What is the expected departing flights per unit time?" << endl << flush;
    cin >> departure_rate;
}
int main(){
    float arriving_rate, departure_rate;
	int total_time ,queue_limit;
	cout << "\033[2J\033[0;0H";
    cout << "Welcome to the \033[36mAIRPORT SIMULATOR\033[0m." << endl;
    sleep(1);
    initilize(total_time, queue_limit, arriving_rate, departure_rate);
}
Runaway::Apped(){

}