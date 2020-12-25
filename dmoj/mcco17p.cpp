#include <bits/stdc++.h>
using namespace std;

const int MN = 150005;
int ds[MN], dep[MN], sc[MN], p[MN], N, M, Q, i, x;
struct pii{int f, s;}bd[MN], b[MN], q[MN]; bool done;
vector<int> adj[MN]; struct qur{int x,y,id;}_;
pii pr(int a,int b){pii z={a,b}; return z;}
queue<qur> qu[MN];

void reset(int n){for(int i=1;i<=n;i++) sc[i]=ds[i]=i;}
int ld(int n){
	if(ds[n] != n) ds[n] = ld(ds[n]);
	return ds[n];
}
int scc(int n){
	if(sc[n] != n) sc[n] = scc(sc[n]);
	return sc[n];
}
void dfs(int n, int pre, int d){
	p[n] = pre; dep[n] = d;
	for(int v : adj[n]){
		if(v != pre) dfs(v, n, d+1);
	}
}

int main(){
	scanf("%d%d%d",&N,&M,&Q);
	for(reset(N),i=1;i<=M;i++){
		int x,y; scanf("%d%d",&x,&y); x++; y++;
		if(ld(x) != ld(y)){
			adj[x].push_back(y);
			adj[y].push_back(x);
			ds[ld(x)] = ld(y);
		}
		bd[i].f = x; bd[i].s = y;
	}
	for(i=1;i<=N;i++){
		if(p[i] == 0) dfs(i, -1, 1);
	}
	for(i=1;i<=Q;i++){
		scanf("%d%d",&q[i].f,&q[i].s);
		q[i].f++; q[i].s++;
		b[i].f = 1; b[i].s = M+1;
	}
	while(!done){
		done = 1; x = 1;
		for(i=1;i<=Q;i++){
			if(b[i].f != b[i].s){
				done = 0; int m = (b[i].f+b[i].s)/2;
				qur z = {q[i].f, q[i].s, i}; qu[m].push(z);
			}
		}
		for(i=1,reset(N);i<=M;i++){
			int x = bd[i].f, y = bd[i].s;
			if(ld(x) != ld(y)) ds[ld(x)]=ld(y);
			else{
				// find
				while(scc(x) != scc(y)){
					if(dep[sc[y]] > dep[sc[x]]) swap(x,y);
					x = p[sc[x]];
				}
				int lca = scc(x);
				x = bd[i].f; y = bd[i].s;
				// merge
				while(scc(x) != scc(y)){
					if(dep[sc[y]] > dep[sc[x]]) swap(x,y);
					int tmp = scc(x); x=p[sc[scc(x)]];
					sc[tmp] = lca; 
				}
			}
			while(!qu[i].empty()){
				qur _ = qu[i].front(); qu[i].pop();
				if(scc(_.x) == scc(_.y)) b[_.id].s=(b[_.id].s+b[_.id].f)/2;
				else b[_.id].f = (b[_.id].f+b[_.id].s)/2+1;
			}
		}
	}
	for(i=1;i<=Q;i++){
		if(b[i].f == M+1) printf("-1\n");
		else printf("%d\n",b[i].f-1);
	}
	return 0;
}
