#include <bits/stdc++.h>
using namespace std;

const int SIZE = 100005, LOGN = 20;
int vis[SIZE][2], st[SIZE], e[SIZE], N, M, Q, i, j, I, J, K, x, y;
vector<int> vec[SIZE]; int c1, c2, lca[SIZE][LOGN+1], df[SIZE], dep[SIZE];

void connect(int u, int p){
	vis[u][0] = vis[u][1] = ++j; st[u] = 1;
	for(int i=0;i<(signed)vec[u].size();i++){
		int v = vec[u][i];
		if(!vis[v][0] && v != p){connect(v,u); vis[u][1]=min(vis[u][1],vis[v][1]);}
		else if(st[v] && v != p){vis[u][1]=min(vis[u][1],vis[v][0]);}
	}
	e[u] = ++j;
}

void dfs(int n, int p, int d){
	lca[n][0] = p; df[n] = 1; dep[n] = d;
	for(int i=0;i<(signed)vec[n].size();i++){
		if(!df[vec[n][i]]) dfs(vec[n][i],n,d+1);
	}
}

int advance(int x, int dif){
	int ptr = 20;
	while(ptr >= 0){
		if((1<<ptr) <= dif){dif -= 1<<ptr; x = lca[x][ptr];}
		ptr--;
	}
	return x;
}

int main(){
	for(scanf("%d%d",&N,&M),i=1;i<=M;i++){
		scanf("%d%d",&x,&y);
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	memset(lca, -1, sizeof(lca));
	connect(1, 0); dfs(1, -1, 1);
	for(i=1;i<=LOGN;i++){
		for(j=1;j<=N;j++){
			if(lca[j][i-1] != -1) 
				lca[j][i] = lca[lca[j][i-1]][i-1];
		}
	}
	for(scanf("%d",&Q),i=1;i<=Q;i++){
		scanf("%d",&I);
		if(I == 1){
			scanf("%d%d%d%d",&J,&K,&x,&y);
			if(vis[y][0] > vis[x][0]){int s = x; x = y; y = s; }
			c1 = (vis[x][0] <= vis[J][0] && e[x] >= e[J]);
			c2 = (vis[x][0] <= vis[K][0] && e[x] >= e[K]);
			if(c1 == c2) printf("yes\n");
			else if(vis[x][1] <= vis[y][0]) printf("yes\n");
			else printf("no\n");
		}
		else{
			scanf("%d%d%d",&J,&K,&x);
			c1 = (vis[x][0] <= vis[J][0] && e[x] >= e[J]);
			c2 = (vis[x][0] <= vis[K][0] && e[x] >= e[K]);
			if(c1 == 0 && c2 == 0) printf("yes\n");
			else if(c1 != c2 && c1 == 1 && vis[advance(J,dep[J]-dep[x]-1)][1] < vis[x][0]) printf("yes\n");
			else if(c1 != c2 && c2 == 1 && vis[advance(K,dep[K]-dep[x]-1)][1] < vis[x][0]) printf("yes\n");
			else if(c1 == c2 && c1 == 1){
				if(dep[J] > dep[K]){int s=K; K=J; J=s;}
			    int z1 = advance(J, dep[J]-dep[x]-1);
			    int z2 = advance(K, dep[K]-dep[x]-1);
			    if(z1 == z2) printf("yes\n");
			    else if(vis[z1][1] < vis[x][0] && vis[z2][1] < vis[x][0]) printf("yes\n");
				else printf("no\n");
			}
			else printf("no\n");
		}
	}
	return 0;
}
