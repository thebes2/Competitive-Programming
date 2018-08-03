#include <bits/stdc++.h>
using namespace std;

const int MN = 303;
long double c[MN][MN], cnt, ex;
int T, N, K, i, j, val[MN], num[MN][MN], x, y, d[MN][MN];
vector<int> adj[MN]; set<int> l;

void dfs(int n, int src, int ds, int p){
	bool fnd = (l.find(val[n])!=l.end());
	if(!fnd) l.insert(val[n]);
	d[src][n] = ds;
	num[src][n] = l.size();
	for(auto v : adj[n])
		if(v != p) dfs(v, src, ds+1, n);
	if(!fnd) l.erase(val[n]);
}

int main(){
	for(i=0;i<MN;i++){
		c[i][0] = c[i][i] = 1;
		for(j=1;j<i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	for(scanf("%d",&T);T;T--){
		cnt = ex = 0;
		for(scanf("%d%d",&N,&K),i=1;i<N;i++){
			scanf("%d%d",&x,&y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		if(K==1){printf("1\n"); continue;}
		for(i=1;i<=N;i++)
			scanf("%d",&val[i]);
		for(i=1;i<=N;i++)
			dfs(i,i,0,0);
		for(i=1;i<=N;i++){
			for(j=i+1;j<=N;j++){
				int dist = d[i][j];
				int count = 0;
				for(int k=1;k<=N;k++){
					if(k==i||k==j) continue;
					if(d[k][i]<dist||(d[k][i]==dist&&k>j)){
						if(d[k][j]<dist||(d[k][j]==dist&&k>i)) count++;
					}
				}
				if(count>=K-2){
					ex += num[i][j]*c[count][K-2];
					cnt += c[count][K-2];
				}
			}
		}
		printf("%.7Lf\n",ex/cnt);
		for(i=1;i<=N;i++) adj[i].clear();
	}
	return 0;
}
