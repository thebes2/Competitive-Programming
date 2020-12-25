#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,popcnt,avx,mmx,abm,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int MN=505,mod=1e9+7;
int dp[MN][MN], tmp[MN], c[MN][MN], N, K, i, arr[MN];
int f[1000006]={1}; unordered_map<int,int> mp;
int qpow(int b,int exp){
	if(exp==0) return 1;
	else if(exp&1) return (1LL*b*qpow(b,exp-1))%mod;
	else{int r=qpow(b,exp/2);return(1LL*r*r)%mod;}
}
int inv(int fact){
	if(!mp.count(fact)) mp[fact]=qpow(f[fact],mod-2);
	return mp[fact];
}
void mrg(int *&ans,int *t){
	int*tmp=(int*)malloc((K+1)*sizeof(int));
	for(int i=0;i<=K;i++) tmp[i]=0;
	for(int i=0;i<=K;i++){
		for(int j=K;j>=i;j--)
			tmp[j]=(tmp[j]+1LL*ans[j-i]*t[i])%mod;
	}
	ans = tmp;
}

int* idk(int l,int r,int b){
	int* ans=(int*)malloc((K+1)*sizeof(int));
	for(int i=0;i<=K;i++)ans[i]=0;
	ans[0] = 1; int mn = 1<<30, lst = l, i, h;
	for(i=l;i<=r;i++)
		mn = min(mn, arr[i]);
	h = mn-b;
	for(i=l;i<=r;i++){
		if(arr[i]==mn){
			if(i-1>=lst) mrg(ans,idk(lst,i-1,mn));
			lst = i+1;
		}
	}
	if(i-1>=lst) mrg(ans,idk(lst,i-1,mn));
	int *tmp=(int*)malloc((K+1)*sizeof(int));
	for(i=0;i<=K;i++) tmp[i]=0;
	for(i=0;i<=K;i++){
		for(int j=max(0,i-h);j<=i;j++)
			tmp[i]=(tmp[i]+1LL*ans[j]*(1LL*c[r-l+1-j][i-j]*(1LL*f[h]*inv(h-i+j)%mod)%mod)%mod)%mod;
	}
	return tmp;
}

int main(){
	for(i=0;i<MN;i++){
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++)
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
	}
	for(i=1;i<1000006;i++)
		f[i]=(1LL*f[i-1]*i)%mod;
	scanf("%d%d",&N,&K);
	for(i=1;i<=N;i++) scanf("%d",&arr[i]);
	int*wts = idk(1,N,0);
	printf("%d\n",wts[K]);
	return 0;
}
