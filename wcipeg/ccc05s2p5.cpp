#include <bits/stdc++.h>
using namespace std;

const int SIZE = 20005;
int N, i, x, y, dp[2][2], pos[SIZE][2];

int main(){
	for(scanf("%d",&N),i=1;i<=N;i++)
		scanf("%d%d",&pos[i][0],&pos[i][1]);
	dp[N%2][0] = N-pos[N][0]; dp[N%2][1] = N-pos[N][1];
	for(i=N-1;i>0;i--){
		dp[i%2][0] = dp[(i+1)%2][0]+abs(pos[i][0]-pos[i+1][1]);
		dp[i%2][0] = min(dp[i%2][0],dp[(i+1)%2][1]+abs(pos[i][0]-pos[i+1][0]))+pos[i+1][1]-pos[i+1][0];
		dp[i%2][1] = dp[(i+1)%2][0]+abs(pos[i][1]-pos[i+1][1]);
		dp[i%2][1] = min(dp[i%2][1],dp[(i+1)%2][1]+abs(pos[i][1]-pos[i+1][0]))+pos[i+1][1]-pos[i+1][0];
	}
	printf("%d\n",dp[1][1]+pos[1][1]+N-2);
	return 0;
}
