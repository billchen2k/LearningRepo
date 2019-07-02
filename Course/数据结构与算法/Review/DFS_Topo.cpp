#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define maxn 100 //最大顶点个数
int n, m;	//顶点数，边数

struct arcnode //边结点
{
	int vertex;    //与表头结点相邻的顶点编号
	arcnode *next; //指向下一相邻接点
	arcnode() {}
	arcnode(int v) : vertex(v), next(NULL) {}
};

struct vernode //顶点结点，为每一条邻接表的表头结点
{
	int vex;	 //当前定点编号
	arcnode *firarc; //与该顶点相连的第一个顶点组成的边
} Ver[maxn];

void Init() //建立图的邻接表需要先初始化，建立顶点结点
{
	for (int i = 1; i <= n; i++) {
		Ver[i].vex = i;
		Ver[i].firarc = NULL;
	}
}

void Insert(int a, int b) //插入以a为起点，b为终点，无权的边
{
	arcnode *q = new arcnode(b);
	if (Ver[a].firarc == NULL)
		Ver[a].firarc = q;
	else {
		arcnode *p = Ver[a].firarc;
		while (p->next != NULL)
			p = p->next;
		p->next = q;
	}
}

#define INF 9999
bool visited[maxn];	 //标记顶点是否被考察，初始值为false
int parent[maxn];	   //parent[]记录某结点的父亲结点，生成树，初始化为-1
int d[maxn], time, f[maxn]; //时间time初始化为0，d[]记录第一次被发现时，f[]记录结束检查时
int topoSort[maxn];
int cnt;
void dfs(int s) //深度优先搜索（邻接表实现），记录时间戳，寻找最短路径
{
	//cout << s << " ";
	visited[s] = true;
	time++;
	d[s] = time;
	arcnode *p = Ver[s].firarc;
	while (p != NULL) {
		if (!visited[p->vertex]) {
			parent[p->vertex] = s;
			dfs(p->vertex);
		}
		p = p->next;
	}
	time++;
	f[s] = time;
	topoSort[cnt++] = s;
}
void dfs_travel() //遍历所有顶点，找出所有深度优先生成树，组成森林
{
	for (int i = 1; i <= n; i++) //初始化
	{
		parent[i] = -1;
		visited[i] = false;
	}
	time = 0;
	for (int i = 1; i <= n; i++) //遍历
		if (!visited[i])
			dfs(i);
	//cout << endl;
}
void topological_Sort() {
	cnt = 0;
	dfs_travel();
	for (int i = cnt - 1; i >= 0; i--)
		cout << topoSort[i] << " ";
	cout << endl;
}
int main() {
	int a, b, w;
	cout << "Enter n and m：";
	cin >> n >> m;
	Init();
	while (m--) {
		cin >> a >> b; //输入起点、终点
		Insert(a, b);  //插入操作
	}
	topological_Sort();
	return 0;
}
