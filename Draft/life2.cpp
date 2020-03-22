#include"Life.h"
#include<iostream>
using namespace std;

Life::Life(int row, int col) {
	this->row = row;
	this->col = col;
}
void Life::initialize()
{
	int i,j;
	bool flag=false;//初始化，令所有等于0；
	
	for(i=0;i<maxRow+1;i++){
		for(j=0;j<=maxCol+1;j++){
			board[i][j]=0;
		}
	} 
	
	int tmpRow,tmpCol;
	cout<<"请输入初始棋子的坐标，以x，y形式输入，以-1 -1结束"<<endl;
	cin>> tmpRow>> tmpCol;
	//判定
	
	while(tmpRow!=-1&&tmpCol!=-1){
		if(tmpRow>=1&&tmpRow<=maxRow-2){
			if(tmpCol>=1&&tmpCol<+maxCol-2){
				board[tmpRow][tmpCol] = 1;
				flag=true;
			}
			else{
				cout<<"列数输入错误，请重新输入"<<endl;
				flag=false; 
			}
		}
		else{
			cout<<"行数输入错误，请重新输入"<<endl;
			flag=false; 
		}
		if(flag){
			cout<<"请继续输入"<<endl;
			cin>>tmpRow>>tmpCol;
		}
		else{
			cin>>tmpRow>>tmpCol;
		}
	} 
	
}

void Life::show()
{
	int i,j;
	cout<<endl;
	for(i=1;i<maxRow+1;i++){
		for(j=1;j<maxCol+1;j++){
			if (board[i][j]==1){
				cout<<"*";
			}
			else{
				cout<<"-";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

void Life::judge()
{
	int i,j;
	int ii,jj;
	
	int newBoard[maxRow+2][maxCol+2];
	int tmpCount;//计算邻居数；
	for(i=1;i<maxRow+1;i++){
		for(j=1;j<maxCol+1;j++){
			newBoard[i][j]=0;
		}
	} 
	
	for(i=1;i<maxRow+1;i++){
		for(j=1;j<maxCol+1;j++){
			tmpCount=0;
			//算周围8格邻居数 
			for(ii=i-1;ii<=i+1;ii++){
				for(jj=j-1;jj<=j+1;jj++){
					if(board[ii][jj]==1){
						tmpCount++;
					}
				}
			}
			
			tmpCount-=board[i][j];//去掉自己
			//判断下一代生死
			if(tmpCount==2){
				newBoard[i][j]=board[i][j];
			} 
			else if (tmpCount==3){
				newBoard[i][j]=1;
			}
			else{
				newBoard[i][j]=0;
			}
		}
	}
	//将新棋盘赋给旧棋盘
	for(i=1;i<maxRow+1;i++){
		for(j=1;j<maxCol+1;j++){
			board[i][j]=newBoard[i][j];
			
		}
	} 
}

#include"Life.h"
#include<iostream>
using namespace std;

int main(void)
{
	int row, col;
	cin >> row >> col;
	Life l(row, col);
	char tmp;
	cout<<"welcome to life game"<<endl;
	cout<<"this game uses grid of size 20 by 60 in witch"<<endl;
	cout<<"each cell can either be occupied by organism or not"<<endl;
	cout<<"according to the number of neibouring bells which are alive."<<endl;
	cout<<"List the coordinatesfor living cells."<<endl;
	l.initialize();
	l.show();
	cout<<"请输入是否继续（Y/N）？"<<endl;
	cin>>tmp;
	while(tmp!='Y'&&tmp!='y'&&tmp!='N'&&tmp!='n'){
		cout<<"输入错误，请重新输入"<<endl;
		cin>>tmp;
		 
	} 
	while(tmp=='Y'||tmp=='y'){
		l.judge();
		l.show();
		cout<<"请输入是否继续（Y/N）？"<<endl;
		cin>>tmp;
		while(tmp!='Y'&&tmp!='y'&&tmp!='N'&&tmp!='n'){
			cout<<"输入错误，请重新输入"<<endl;
			cin>>tmp;
		}
	}
	cout<<"感谢游玩！"<<endl;
	return 0; 
	
} 




































