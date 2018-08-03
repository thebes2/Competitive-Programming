#include <bits/stdc++.h>
using namespace std;

const int MN = 200005;
int arr[MN], N, Q, i, x, y, cnt, tp=1, vl;
unordered_map<string,int> ind;
string a, b, c; struct pii{int d,s;}_;
pii pr(int d,int s){pii z={d,s}; return z;}
vector<pii> adj[MN];

void dfs(int u, int msk){
	arr[u] = msk;
	for(auto v : adj[u]){
		if(arr[v.d]!=-1 && arr[v.d] != (v.s^msk) && !vl){
			printf("Waterloo\n"); vl = 1; return;
		}
		else if(arr[v.d] == -1) dfs(v.d,v.s^msk);
	}
}

int main(){
	memset(arr, -1, sizeof(arr));
	for(scanf("%d%d",&N,&Q),i=1;i<=N;i++){
		cin >> a >> b >> c;
		if(ind[a] == 0) ind[a] = ++cnt;
		if(ind[b] == 0) ind[b] = ++cnt;
		adj[ind[a]].push_back(pr(ind[b],(c=="intersect")));
		adj[ind[b]].push_back(pr(ind[a],(c=="intersect")));
	}
	for(i=1;i<=cnt;i++){
		if(arr[i] == -1){
			dfs(i, tp); tp += 2;
		}
	}
	if(vl) return 0;
	for(i=0;i<Q;i++){
		cin >> a >> b;
		int x = ind[a], y = ind[b];
		if(x == 0 || y == 0) printf("unknown\n");
		else if(arr[x] == arr[y]) printf("parallel\n");
		else if((arr[x]^1) == arr[y]) printf("intersect\n");
		else printf("unknown\n");
	}
	return 0;
}
