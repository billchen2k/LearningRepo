#include <iostream>
using namespace std;
typedef int errorCode;
constexpr int ERROR_QUEUEFULL = 6901;
constexpr int ERROR_QUEUEEMPTY = 6902;
const int MAXL = 1000;
class myQueue
{
  private:
	char data[MAXL];
	int frontPos = 0;
	int rearPos = 0;

  public:
	char retrieve()
	{
		if (frontPos == rearPos)
		{
			cout << "Error: Queue is empty.";
			return ERROR_QUEUEEMPTY;
		}
		else
			return data[rearPos];
	}
	errorCode serve()
	{
		if ((rearPos + 1) % MAXL == frontPos || rearPos == frontPos)
		{
			cout << "Error: Queue is empty.";
			return ERROR_QUEUEEMPTY;
		}
		else
		{
			rearPos = (rearPos + 1) % MAXL;
			return 0;
		}
	}
	errorCode append(char c)
	{
		if ((frontPos + 1) % MAXL == rearPos)
		{
			cout << "Error: Queue is full.";
			return ERROR_QUEUEFULL;
		}
		else
		{
			data[frontPos] = c;
			frontPos = (frontPos + 1) % MAXL;
			return 0;
		}
	}
	int size()
	{
		return (frontPos - rearPos >= 0) ? (frontPos - rearPos) : (rearPos - frontPos);
	}
	bool isEmpty()
	{
		return frontPos == rearPos ? true : false;
	}
	void clear()
	{
		frontPos = rearPos = 0;
	}
	errorCode print()
	{
		if (size() == 0)
		{
			return ERROR_QUEUEEMPTY;
		}
		else
		{
			for (int i = rearPos; i < (rearPos + size()) % MAXL; i = (i + 1) % MAXL)
				cout << data[i] << " ";
		}
		cout << endl;
	}
};
