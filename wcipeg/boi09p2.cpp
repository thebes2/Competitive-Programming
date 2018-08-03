#include <bits/stdc++.h>
using namespace std;

const int MN = 1e5+5;
int vis[MN], N, i, j, x, ans;
vector<int> adj[MN];

void dfs(int n){
	vis[n] = 1;
	for(auto v : adj[n])
		if(!vis[v]) dfs(v);
}

int main(){
	for(j=0;j<2;j++){
		for(scanf("%d",&N),i=1;i<=N;i++){
			scanf("%d",&x);
			adj[x].push_back(i);
			adj[i].push_back(x);
		}
		for(i=1;i<=N;i++){
			if(!vis[i]){
				dfs(i); ans++;
			}
		}
		printf("%d ",ans); ans=0;
		memset(vis, 0, sizeof(vis));
		for(i=1;i<=N;i++) adj[i].clear();
	}
	return 0;
}
