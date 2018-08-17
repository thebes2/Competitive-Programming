#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MN=2002,LG=45;
ll N, A, B, ans, i, j, k, psa[MN], mn[MN];
bitset<MN> dp[MN];
bool idk(ll m){
	for(i=2;i<=N+1;i++) mn[i]=1<<30;
	for(i=1;i<=N;i++){
		for(j=i+1;j<=N+1;j++){
			if((m|(psa[j-1]-psa[i-1]))!=m) continue;
			mn[j] = min(mn[j], mn[i]+1);
		}
	}
	return mn[N+1]<=B;
}
bool check(ll m){
	if(A==1) return idk(m);
	for(i=1;i<=N;i++) dp[i].reset();
	dp[0][0] = 1;
	for(i=1;i<=N;i++){
		for(j=i;j>=1;j--){
			if((m|(psa[i]-psa[j-1]))!=m) continue;
			for(k=0;k<B;k++) if(dp[j-1][k]) dp[i][k+1]=1;
		}
	}
	for(i=A;i<=B;i++) if(dp[N][i]) return 1;
	return 0;
}

int main(){
	scanf("%lld%lld%lld",&N,&A,&B);
	for(i=1;i<=N;i++)
		scanf("%lld",&psa[i]),psa[i]+=psa[i-1];
	ans = (1LL<<LG)-1;
	for(int i=LG-1;i>=0;i--){
		ans -= (1LL<<i);
		if(!check(ans)) ans += 1LL<<i;
	}
	printf("%lld\n",ans);
	return 0;
}
