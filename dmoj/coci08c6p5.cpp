#include <bits/stdc++.h>
using namespace std;

const int MN = 4004;
struct pii{int f, s;}src,des;
pii pr(int x,int y){pii z={x,y}; return z;}
int p[2002][202], arr[2][2002], C, R, Q, i, j, x, d[4004][4004], a[2], b[2];
struct pq{bool operator()(const pii&i,const pii&j){return(i.s>j.s);}};
priority_queue<pii,vector<pii>,pq> q;
long long ans;

int main(){
	memset(d, -1, sizeof(d));
	for(scanf("%d%d",&R,&C),i=1;i<=R;i++){
		for(j=1;j<=C;j++){
			scanf("%d",&x);
			if(j==1) arr[0][i] = x;
			if(j==C) arr[1][i] = x;
			p[i][j] = p[i][j-1]+x;
		}
	}
	des = pr(1, 1); ans += arr[0][1];
	for(i=0;i<2*R;i++){
		q.push(pr(i,0));
		while(!q.empty()){
			pii _ = q.top(); q.pop();
			pii ps = {_.f/2+1, _.f%2};
			if(d[i][_.f]!=-1) continue;
			d[i][_.f] = _.s;
			if(d[i][_.f^1]==-1){
				int ds=(ps.s)?p[ps.f][C-1]:p[ps.f][C]-p[ps.f][1];
				q.push(pr(_.f^1,_.s+ds));
			}
			if(ps.f!=1&&d[i][_.f-2]==-1) q.push(pr(_.f-2,_.s+arr[_.f&1][ps.f-1]));
			if(ps.f!=R&&d[i][_.f+2]==-1) q.push(pr(_.f+2,_.s+arr[_.f&1][ps.f+1]));
		}
	}
	for(scanf("%d",&Q);Q>0;Q--){
		src.f=des.f; src.s=des.s;
		scanf("%d%d",&des.f,&des.s);
		int r1 = (src.f-1)*2, r2 = (des.f-1)*2;
		a[0] = p[des.f][des.s]-p[des.f][1];
		a[1] = p[des.f][C-1]-p[des.f][des.s-1];
		b[0] = p[src.f][src.s-1];
		b[1] = p[src.f][C]-p[src.f][src.s];
		for(i=0;i<2;i++)
			b[i] += min(d[r1+i][r2]+a[0],d[r1+i][r2+1]+a[1]);
		r1 = src.f; r2 = des.f;
		int tmp = (r1==r2)?(src.s>des.s)?p[r1][src.s-1]-p[r1][des.s-1]:
			p[r1][des.s]-p[r1][src.s]:1<<30;
		ans += 1LL*min(min(b[0],b[1]),tmp);
	}
	printf("%lld\n",ans);
	return 0;
}
