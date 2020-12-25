#include <bits/stdc++.h>
#define sq(x) (x)*(x)
using namespace std;

const int MN = 3000, MM = 200005;
struct pii{int f, s;}n[MN][MN],a[MN][MN];
int N, S, M, Q, K, i, j, k, x, cnt, bit[MM];
pii pr(int f,int s){pii z={f,s}; return z;}
struct z{pii f, s;}e[5],c; set<int> s[MN];

void upd(int p, int v){for(;p<=S;p+=p&(-p))bit[p]+=v;}
int qu(int p){int r=0;for(;p>0;p-=p&(-p))r+=bit[p]; return r;}

int main(){
	for(scanf("%d%d%d",&N,&K,&S);i<S;i++){
		for(scanf("%d",&M),j=0;j<M;j++){
			scanf("%d%d",&e[j].s.f,&e[j].s.s);
			e[j].f.f = max(1,e[j].s.f-K+1);
			e[j].f.s = max(1,e[j].s.s-K+1);
		}
		for(j=1;j<(1<<M);j++){
			c.f=pr(1,1); c.s=pr(1<<30,1<<30);
			for(cnt=0,k=0;k<M;k++){
				if((1<<k)&j){
					cnt++;
					c.f.f = max(e[k].f.f,c.f.f);
					c.f.s = max(e[k].f.s,c.f.s);
					c.s.f = min(e[k].s.f,c.s.f);
					c.s.s = min(e[k].s.s,c.s.s);
				}
			}
			if(c.f.f <= c.s.f && c.f.s <= c.s.s){
				int tmp = (cnt%2)? 1:-1;
				a[c.f.f][c.f.s].s+=tmp;
				a[c.f.f][c.s.s+1].s-=tmp;
				a[c.s.f+1][c.f.s].s-=tmp;
				a[c.s.f+1][c.s.s+1].s+=tmp;
			}
		}
	}
	for(i=1;i<=(N-K+1);i++){
		for(j=1;j<=(N-K+1);j++){
			a[i][j].f=a[i][j].s+a[i][j-1].f+a[i-1][j].f-a[i-1][j-1].f;
			s[i].insert(j); if(a[i][j].f)upd(a[i][j].f,1);
		}
	}
	for(scanf("%d",&Q);Q>0;Q--){
		scanf("%d",&x);
		if(x == 2){
			scanf("%d",&x);
			if(x > S) printf("0.0000000\n");
			else printf("%.7lf\n",(double)(qu(S)-qu(x-1))/(double)(sq(N-K+1)));
		}
		else{
			scanf("%d%d",&c.s.f,&c.s.s);
			c.f.f = max(1,c.s.f-K+1);
			c.f.s = max(1,c.s.s-K+1);
			for(i=c.f.f;i<=c.s.f;i++){
				if(s[i].empty()) continue;
				auto v = s[i].lower_bound(c.f.s);
				while(v!=s[i].end() && *v <= c.s.s){
					if(a[i][*v].f) upd(a[i][*v].f,-1);
					auto it = v; v++; s[i].erase(it);
				}
			}
		}
	}
	return 0;
}
