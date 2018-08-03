#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MN = 202, mod = 1e9+7;
ll dp[MN][2][MN], N, W, M, i, x, y, arr[MN], d[MN], s[MN], arr1[MN];
vector<tuple<int,int>> e[MN];

void solve(ll n){
	if(s[n]==1) return;
	else s[n]=1;
	dp[n][0][0]=dp[n][1][1]=1;
	for(auto v : e[n]){
		solve(get<0>(v));
		ll a=get<0>(v),b=get<1>(v);
		memset(arr, 0, sizeof(arr));
		memset(arr1, 0, sizeof(arr1));
		for(int i=W;i>=0;i--){
			for(int j=0;j<=i;j++){
				arr[i]=(arr[i]+dp[n][1][j]*dp[a][b][i-j])%mod;
				arr1[i]=(arr1[i]+dp[n][0][j]*(dp[a][0][i-j]+dp[a][1][i-j]))%mod;
			}
		}
		copy(arr, arr+MN, dp[n][1]);
		copy(arr1, arr1+MN, dp[n][0]);
	}
}

int main(){
	for(scanf("%lld%lld%lld",&N,&W,&M);i<M;i++){
		char c;scanf(" %c%lld%lld",&c,&x,&y);
		e[x].push_back({y,(c=='D')});d[y]++;
	}
	for(i=1;i<=N;i++){
		if(!d[i]){
			solve(i);
			e[0].push_back({i,0});
		}
	}
	solve(0);
	printf("%lld\n",dp[0][0][W]);
	return 0;
}
