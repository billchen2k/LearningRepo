#include <iostream>
#include <queue>
#include <unistd.h>
#include "Random.h"
using namespace std;
typedef int feedback;
const int success = 1;
const int fail = 0;
const int USPEED_SHORT = 1000;
const int USPEED_LONG = 1000;
enum flightStatus{
	null,
	toLand,
	toTakeoff
};
enum runawayAct{
	idle,
	letTakeoff,
	letLand
};
string percentage(int A, int B){
	char *temp = new char[100];
	sprintf(temp, "%3.2f%%", (double)A / (double)B * 100);
	string output = temp;
	return output;
}
class Plane{
  private:
	int ID;
	int comingTime;
	flightStatus status;
  public:
  	Plane(){
		ID = -1;
		comingTime = -1;
		status = null;
	}
	Plane(int _ID, int _comingTime, flightStatus _status){
		usleep(USPEED_SHORT);
		ID = _ID;
		comingTime = _comingTime;
		status = _status;
		cout << "[PLANE MESSAGE] Plane NO." << ID << " is applying to " << ((status == toLand) ? "land " : "take off ") << endl;
	}
	feedback land(int currentTime){
		usleep(USPEED_LONG);
		cout << "\033[42m[PLANE MESSAGE] Plane NO." << ID << " has landed safely.\033[0m" << endl
			 << "                Waiting time before landing: " << currentTime - comingTime << "." << endl;
	}
	feedback takeoff(int currentTime){
		usleep(USPEED_LONG);
		cout << "\033[42m[PLANE MESSAGE] Plane NO." << ID << " has taken off.\033[0m" << endl
			 << "                Waiting time before taking off: " << currentTime - comingTime << "." << endl;
	}
	feedback reject(int currentTime){
		usleep(USPEED_LONG);
		if(status == toLand){
			cout << "\033[41m[AIRPORT MESSAGE] Plane NO." << ID << "'s landing request is rejected.\033[0m" << endl
				 << "                  It has been directed to other airports." << endl;
		}
		else{
			cout << "\033[41m[AIRPORT MESSAGE] Plane NO." << ID << " 's taking off request is rejected.\033[0m" << endl
				 << "                  This flight is delayed." << endl;
		}
	}
	int getTime(){
		return comingTime;
	}
};

class Runaway{
  private:
	queue<Plane> landingQueue;
	queue<Plane> takeoffQueue;
	int limit;
	runawayAct act;
	int landingRequests;
	int landingAccepted;
	int landingRejected;
	int takeoffRequests;
	int takeoffAccepted;
	int takeoffRejected;
	int idleUnit;
	int landingWaitedTime;
	int takeoffWaitedTime;

  public:
	Runaway(int _limit){
		limit = _limit;
		landingRequests = 0;
		landingAccepted = 0;
		takeoffRequests = 0;
		takeoffAccepted = 0;
		takeoffRejected = 0;
		idleUnit = 0;
		landingWaitedTime = 0;
		takeoffWaitedTime = 0;
	}
	feedback CanLand(const Plane &current){
		landingRequests++;
		feedback result;
		if (landingQueue.size() < limit){
			result = success;
			landingQueue.push(current);
		}
		else{
			result = fail;
			landingRejected++;
		}
		return result;
	}
	feedback CanTakeoff(const Plane &current){
		takeoffRequests++;
		feedback result;
		if (takeoffQueue.size() < limit){
			result = success;
			takeoffQueue.push(current);
		}
		else{
			result = fail;
			takeoffRejected++;
		}
		return result;
	}
	runawayAct Act(int timeNow, Plane &moving){
		runawayAct result;
		if (!landingQueue.empty()){
			landingAccepted++;
			moving = landingQueue.front();
			landingWaitedTime += timeNow - moving.getTime();
			landingQueue.pop();
			return letLand;
		}
		else if(!takeoffQueue.empty()){
			takeoffAccepted++;
			moving = takeoffQueue.front();
			takeoffWaitedTime += timeNow - moving.getTime();
			takeoffQueue.pop();
			return letTakeoff;
		}
		else{
			idleUnit++;
			return idle;
		}
	}
	void SumUp(int simulationTime){
		cout << endl;
		cout << "\033[36m=============== SIMULATION RESULTS ===============\033[0m" << endl
			 << "\033[5;3mCalculating...\033[0m" << endl;
		sleep(2);
		cout
			<< "\033[1ATotal simulation time:                         " << simulationTime << endl
			<< "Total flights simulated:                       " << landingRequests + takeoffRequests << endl
			<< "Total flights required to land:                " << landingRequests << endl
			<< "Landing request accepted:                      " << landingAccepted << endl
			<< "Landing request rejected:                      " << landingRejected << endl
			<< "Total flights required to take off:            " << takeoffRequests << endl
			<< "Taking off request accepted:                   " << takeoffAccepted << endl
			<< "Taking off request rejected:                   " << takeoffRejected << endl
			<< "Flights still left in landing queue:           " << landingQueue.size() << endl
			<< "Flights still left in taking off queue:        " << takeoffQueue.size() << endl
			<< "Average waiting time in landing queue:         " << (float)landingWaitedTime / (float)landingAccepted << endl
			<< "Average waiting time in taking off queue:      " << (float)takeoffWaitedTime / (float)takeoffAccepted << endl
			<< "Average observing time for landing flights:    " << (float)landingRequests / (float)simulationTime << endl
			<< "Average observing time for taking off flights: " << (float)takeoffRequests / (float)simulationTime << endl
			<< "Ratio for successfully landed flights:         " << percentage(landingAccepted, landingRequests) << endl
			<< "Ratio for successfully took off flights:       " << percentage(landingAccepted, landingRequests) << endl
			<< "Ratio of runaway idle time:                    " << percentage(idleUnit, simulationTime) << endl
			<< endl
			<< "\033[3;2mSimulation finished.\033[0m" << endl;
	}
};
void initilize(int &totalTime, int &queueLimit, float &arrivingRate, float &departureRate){
	cout << "\033[2J\033[0;0H";
	cout << "Welcome to the \033[46mAIRPORT SIMULATOR\033[0m." << endl;
	sleep(1);
	cout << "\033[36mPlease enter how many time units you will simulate:\033[0m\n"
		 << flush;
	cin >> totalTime;
	cout << "\033[36mHow many flights can be waiting to land or takeoff?\033[0m" << endl
		 << flush;
	cin >> queueLimit;
	cout << "\033[36mWhat is the expected arriving flights per unit time?\033[0m" << endl
		 << flush;
	cin >> arrivingRate;
	cout << "\033[36mWhat is the expected departing flights per unit time?\033[0m" << endl
		 << flush;
	cin >> departureRate;
}

int main(){
START:
	float arrivingRate, departureRate;
	int totalTime, queueLimit;
	initilize(totalTime, queueLimit, arrivingRate, departureRate);
	int currentTime;
	int planeID = 0;
	Random randomSeed;
	Runaway airport(queueLimit);
	for (currentTime = 0; currentTime < totalTime; currentTime++){
		cout << "\033[2m----- Current excution time: " << currentTime << " -----\033[0m" << endl;
		int comingPerUnit = randomSeed.poisson(arrivingRate);
		for (int num = 0; num < comingPerUnit; num++, planeID++){
			Plane currentPlane(planeID, currentTime, toLand);
			if(airport.CanLand(currentPlane)==fail){
				currentPlane.reject(currentTime);
			}
		}
		int departingPerUnit = randomSeed.poisson(departureRate);
		for (int num = 0; num < departingPerUnit; num++, planeID++){
			Plane currentPlane(planeID, currentTime, toTakeoff);
			if(airport.CanTakeoff(currentPlane)==fail){
				currentPlane.reject(currentTime);
			}
		}
		Plane movingPlane;
		switch (airport.Act(currentTime, movingPlane)){
		case letLand:
			movingPlane.land(currentTime);
			break;
		case letTakeoff:
			movingPlane.takeoff(currentTime);
			break;
		case idle:
			cout << "\033[46m[AIRPORT MESSAGE]: Runaway is idle.\033[0m" << endl;
			break;
		}
	}
	airport.SumUp(totalTime);
	char ch;
	cout << "\033[36mDo you want to initialize another simulation? \n([R] or [r] to restart, any other key to exit.)\033[0m" << endl;
	while(cin.get()!='\n')
		;
	if (toupper(ch = cin.get()) == 'R')
		goto START;
	return 0;
}