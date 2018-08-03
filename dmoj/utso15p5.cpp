#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MN = 50004, MM = 100005;
struct edge{ll f, s, w;}_; vector<edge> e;
struct pii{ll f, s;}; pii lca[MN][16]; vector<pii> adj[MN];
ll N, M, x, ds[MN], use[MM], dep[MN], anc[MN][16], i, j, p, mn=1<<30, tot, cnt; 
bool cmp(edge i,edge j){return(i.w<j.w);}
ll ld(ll x){if(x!=ds[x]){ds[x]=ld(ds[x]);}return ds[x];}
pii pr(ll i, ll j){pii z={i,j}; return z;}

void dfs(ll u, ll p, ll w){
	dep[u] = dep[p]+1; anc[u][0] = p;
	lca[u][0].f = w; 
	for(pii v : adj[u]){
		if(v.f == p) continue;
		dfs(v.f, u, v.s);
	}
}

pii fs(pii i, pii j){
	if(i.f == j.f) return pr(i.f,max(i.s,j.s));
	else if(i.f > j.f) return pr(i.f,max(i.s,j.f));
	else return pr(j.f,max(i.f,j.s));
}

int main(){
	for(i=1;i<=50000;i++) ds[i] = i;
	for(scanf("%lld%lld",&N,&M),i=0;i<M;i++){
		scanf("%lld%lld%lld",&_.f,&_.s,&_.w);
		e.push_back(_);
	}
	memset(anc, -1, sizeof(anc));
	memset(lca, -1, sizeof(lca));
	sort(e.begin(), e.end(), cmp);
	for(i=0;i<(signed)e.size();i++){
		if(ld(e[i].f) != ld(e[i].s)){
			ds[ld(e[i].f)] = ds[e[i].s];
			pii tmp = {e[i].s, e[i].w};
			adj[e[i].f].push_back(tmp);
			tmp.f = e[i].f; use[i] = 1;
			adj[e[i].s].push_back(tmp);
			tot += e[i].w; cnt++;
		}
	}
	dfs(1, -1, -1);
	for(j=1;j<16;j++){
		for(i=1;i<=N;i++){
			if(anc[i][j-1] != -1){
				lca[i][j] = fs(lca[i][j-1],lca[anc[i][j-1]][j-1]);
				anc[i][j] = anc[anc[i][j-1]][j-1];
			}
		}
	}
	for(i=0;i<M;i++){
		if(!use[i]){
			ll x = e[i].f, y = e[i].s;
			if(dep[y] > dep[x]) swap(x,y);
			pii ed = {-1, -1};
			for(p=15;p>=0;p--){
				if((1<<p) <= dep[x]-dep[y]){
					ed = fs(ed, lca[x][p]);
					x = anc[x][p];
				}
			}
			if(x != y){
				for(p=15;p>=0;p--){
					if(anc[x][p] != anc[y][p]){
						ed = fs(ed, lca[x][p]);
						ed = fs(ed, lca[y][p]);
						x = anc[x][p]; y = anc[y][p];
					}
				}
				ed = fs(ed, lca[x][0]);
				ed = fs(ed, lca[y][0]);
			}
			if(ed.f == e[i].w && ed.s != -1) mn = min(mn, e[i].w);
			else if(ed.f < e[i].w && ed.f != -1) mn = min(mn, e[i].w-ed.f);
		}
	}
	if(mn == 1<<30 || cnt != N-1) printf("-1\n");
	else printf("%lld\n",tot+mn);
	return 0;
}
