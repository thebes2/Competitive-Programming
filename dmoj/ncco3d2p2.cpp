#include <bits/stdc++.h>
using namespace std;

const int MN=303,MM=1005;
int dp[MN][MM], N, M, i;
pair<int,int> arr[MN];

int solve(int n, int s){
	if(n == N+1) return 0;
	if(dp[n][s] != -1) return dp[n][s];
	else dp[n][s] = 1<<30;
	int a = s, b = 0;
	for(int i=n;i<=N&&a+arr[i].first<=M&&b+arr[i].second<=M;i++)
		a+=arr[i].first,b+=arr[i].second,dp[n][s]=min(dp[n][s],solve(i+1,b)+1);
	dp[n][s] = min(dp[n][s], solve(n,0)+1);
	return dp[n][s];
}

int main(){
	for(scanf("%d%d",&M,&N),i=1;i<=N;i++)
		scanf("%d%d",&arr[i].first,&arr[i].second);
	memset(dp, -1, sizeof(dp));
	printf("%d\n",solve(1,0)+2);
	getchar(); getchar();
}
