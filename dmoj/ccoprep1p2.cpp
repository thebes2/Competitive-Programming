#include <bits/stdc++.h>
using namespace std;

typedef long long ll; const ll MN = 404;
ll N, S, a[MN], crt[MN], low[MN][2], vis[MN], cmp[MN], sz[MN], cnt[MN], i, x, y, u[MN];
vector<ll> adj[MN]; queue<ll> Q; pair<ll,ll> ans;

void dfs(ll n, ll p, ll d){
	low[n][0] = low[n][1] = d;ll cnt = 0;
	for(ll i=0;i<(signed)adj[n].size();i++){
		ll v = adj[n][i];
		if(!low[v][0]){
			cnt++; dfs(v, n, d+1); low[n][1] = min(low[n][1],low[v][1]);
			if(p == -1 && cnt > 1) crt[n] = 1;
			if(p != -1 && low[v][1] >= d) crt[n] = 1;
		}
		else if(v != p) low[n][1] = min(low[n][1],low[v][0]);
	}
}

void comp(ll st){
	Q.push(st); vis[st] = 1; S++;
	while(!Q.empty()){
		ll cur = Q.front(); Q.pop(); cmp[cur] = S; sz[S]++;
		for(ll i=0;i<(signed)adj[cur].size();i++){
			if(!vis[adj[cur][i]] && !crt[adj[cur][i]]){
				vis[adj[cur][i]] = 1;
				Q.push(adj[cur][i]);
			}
		}
	}
}

ll fact(ll n){return(n==1)?1:n*fact(n-1);}

int main(){
	scanf("%lld",&N);
	while(N != 0){
		ans = make_pair(0,1);
		for(i=0;i<N;i++){
			scanf("%lld%lld",&x,&y); a[x]=1; a[y]=1;
			adj[x].push_back(y); adj[y].push_back(x);
		}
		for(i=1;i<=400;i++){
			if(!low[i][0] && a[i]) dfs(i,-1,1);
		}
		for(i=1;i<=400;i++){
			if(!vis[i] && !crt[i] && a[i]) comp(i);
		}
		for(i=1;i<=400;i++){
			if(crt[i] && a[i]){
				for(ll j=0;j<(signed)adj[i].size();j++){
					if(!u[cmp[adj[i][j]]]){
						cnt[cmp[adj[i][j]]]++;
						u[cmp[adj[i][j]]] = 1;
					}
				}
			}
			for(ll j=1;j<=400;j++) u[j] = 0;
		}
		for(i=1;i<=S;i++){
			if(cnt[i] == 0){
				ans.first += 2;
				ans.second *= (sz[i]==1)?1:sz[i]*(sz[i]-1)/2;
			}
			else if(cnt[i] == 1){
				ans.first ++;
				ans.second *= sz[i];
			}
		}
		printf("%lld %lld\n",ans.first,ans.second);
		for(i=0;i<=400;i++){
			vis[i] = cmp[i] = sz[i] = a[i] = crt[i] = low[i][0] = low[i][1] = cnt[i] = 0;
			adj[i].clear();
		}
		scanf("%lld",&N); S = 0;
	}
	return 0;
}
