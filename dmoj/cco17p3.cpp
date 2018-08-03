#include <bits/stdc++.h>
using namespace std;

const int MN=2e5+5, LG=62;
typedef long long ll;
ll N, Q, i, j, k, bit[3*MN], x, y, w, q[MN], val[MN], ans[MN];
pair<ll,ll> p[MN], t[2*MN], a[MN];
bitset<MN> d; map<ll,ll> pos; 

void upd(ll p,ll v){for(;p<=2*N+Q+2;p+=p&-p)bit[p]+=v;}
ll qu(ll p){ll r=0;for(;p>0;p-=p&-p)r+=bit[p]; return r;}
ll rev(ll n){
	ll ret=0;
	for(int i=LG-1;i>=0;i--)
		if((1LL<<i)&n) ret+=(1LL<<(LG-i-1));
	return ret;
}

int main(){
	for(scanf("%lld%lld",&N,&Q),i=1;i<=N;i++){
		scanf("%lld%lld%lld",&x,&y,&w);
		x = rev(x), y = rev(y); val[i]=w;
		a[i] = {y-(y&-y)+1, y+(y&-y)-1}; 
		pos[y+(y&-y)-1]=pos[y-(y&-y)+1]=0;
		t[2*i-1] = {x-(x&-x)+1,i}; t[2*i]={x+(x&-x),i};
	}
	for(i=1;i<=Q;i++){
		scanf("%lld%lld",&x,&y);
		x=rev(x), y=rev(y); pos[y]=0;
		p[i]={x,i}; q[i]=y;
	}
	sort(t+1,t+2*N+1);
	sort(p+1,p+Q+1); i=1;
	for(auto it=pos.begin();it!=pos.end();it++) it->second=i++;
	for(i=j=1;i<=2*N;i++){
		while(p[j].first<t[i].first&&j<=Q){
			int id = p[j].second;
			ans[id]=qu(pos[q[id]]); j++;
		}
		int id=t[i].second;
		upd(pos[a[id].first],(d[id])?-val[id]:val[id]);	
		upd(pos[a[id].second]+1,(d[id])?val[id]:-val[id]);
		d[id].flip();
	}
	for(i=1;i<=Q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
