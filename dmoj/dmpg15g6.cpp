#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int MN = 2e5+5;
vector<vector<int>> pos;
int N, M, S, Q, i, cnt[MN], arr[MN], idx[MN], nxt, x, y;
map<int,int> mp;

int main(){
	for(scanf("%d%d",&N,&M),i=1;i<=N;i++)
		scanf("%d",&arr[i]),cnt[arr[i]]++;
	S = ceil(sqrt(N+0.0));
	memset(idx,-1,sizeof(idx));
	for(i=1;i<=N;i++){
		if(cnt[arr[i]]<S) continue;
		if(idx[arr[i]]==-1) 
			idx[arr[i]]=nxt++,pos.pb(vector<int>());
		pos[idx[arr[i]]].pb(i);
	}
	int fnd = 1;
	for(scanf("%d",&Q);Q;Q--){
		scanf("%d%d",&x,&y);
		fnd = 0;
		if(y-x+1<3*S){
			mp.clear();
			for(i=x;i<=y;i++)
				mp[arr[i]]++;
			for(auto v : mp){
				if(v.second>=ceil(2*(y-x+1)/3.0)) fnd += 2;
				else if(v.second>=ceil((y-x+1)/3.0)) fnd ++;
			}
		}
		else{
			for(i=0;i<(signed)pos.size();i++){
				int p1=lower_bound(pos[i].begin(),pos[i].end(),x)-pos[i].begin();
				int p2=upper_bound(pos[i].begin(),pos[i].end(),y)-pos[i].begin();
				int len = p2 - p1;
				if(len>=ceil(2*(y-x+1)/3.0)) fnd+=2;
				else if(len>=ceil((y-x+1)/3.0)) fnd++;
			}
		}
		printf("%s\n",(fnd>=2)?"YES":"NO");
	}
	return 0;
}
