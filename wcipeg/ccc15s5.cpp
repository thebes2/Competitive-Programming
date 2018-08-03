#include <iostream>
#include <algorithm>
using namespace std;

int MAX(int a, int b){return(a>b)?a:b;}
int dp[3002][101][101][2], arr[3001], ex[101], N, M, i;
int comp(int p, int s, int e, int c){
	if(p > N && s > e) return 0;
	if(dp[p][s][e][c] != 0) return dp[p][s][e][c];
	if(s <= e){
		if(c) dp[p][s][e][c] = MAX(dp[p][s][e][c],ex[e]+comp(p,s,e-1,0));
		dp[p][s][e][c] = MAX(dp[p][s][e][c],comp(p,s+1,e,1));
	}
	if(p <= N){
		if(c) dp[p][s][e][c] = MAX(dp[p][s][e][c],arr[p]+comp(p+1,s,e,0));
		dp[p][s][e][c] = MAX(dp[p][s][e][c],comp(p+1,s,e,1));
	}
	return dp[p][s][e][c];
}

int main(){
	for(scanf("%d",&N),i=0;i<N;i++) scanf("%d",&arr[i+1]);
	for(scanf("%d",&M),i=0;i<M;i++) scanf("%d",&ex[i+1]);
	sort(ex+1,ex+M+1);
	printf("%d\n",comp(1,1,M,1));
	return 0;
}
