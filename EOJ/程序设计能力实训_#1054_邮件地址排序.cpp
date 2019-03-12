#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef struct{
	string username;
	string domain;
} email;
int cmp(const void *pa, const void *pb)
{
	email *pta = (email *)pa;
	email *ptb = (email *)pb;
	if (pta->domain != ptb->domain){
		int a = (pta->domain < ptb->domain);
		return pta->domain > ptb->domain ? 1 : -1;
	}
	else
		return pta->username < ptb->username ? 1 : -1;
}
bool cmpq(email a, email b){
	if (a.domain != b.domain){
		return a.domain < b.domain;
	}
	else
		return a.username > b.username;
}
int main()
{
	int len;
	scanf("%d", &len);
	email *data;
	data = new email[len];
	while (cin.get() != '\n')
		continue;
	for (int i = 0; i < len; i++){
		char ch;
		while((ch=cin.get())!='@'){
			data[i].username += ch;
		}
		while ((ch = cin.get()) != '\n' && ch != EOF){
			data[i].domain += ch;
		}
	}
	sort(data, data + len, cmpq);
	//qsort(data, len, sizeof(data[0]), cmp);
	for (int k = 0; k < len; k++)
		cout << data[k].username << "@" << data[k].domain << endl;
	return 0;
}
