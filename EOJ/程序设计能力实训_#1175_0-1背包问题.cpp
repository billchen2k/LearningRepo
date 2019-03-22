#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n, M, len;
    cin >> len;
    while(len--){
        cin >> n >> M;
        int weight[100001];
        int price[100001];
        for (int i = 0; i < n; i++){
            cin >> weight[i] >> price[i];
        }
        int **mem = new int *[21];
        for (int i = 0; i < 21;i++){
            mem[i] = new int[100001];
        }
        memset(mem[0], 0, 100001);
        for (int i = 1; i <= n; i++){
            for (int j = 0; j <= M; j++){
                if (weight[i-1] > j){
                    mem[i][j] = mem[i - 1][j];
                }
                else{
                    mem[i][j] = max(mem[i - 1][j], price[i - 1] + mem[i - 1][j - weight[i - 1]]);
                }
            }
        }
        cout << mem[n][M] << endl;
        return 0;
    }
}