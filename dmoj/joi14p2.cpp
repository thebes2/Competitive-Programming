#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MN = 200005;
struct pii{ll f, s, l;}a[MN];
ll st[3*MN], q[MN], N, K, M, i, j, n, bit[MN];
long long ans; map<int,int> p;

bool cmp(pii i,pii j){return(i.l<j.l);}
ll qu(ll p){ll r=0;for(;p>0;p-=p&(-p))r+=bit[p]; return r;}
void up(ll p){for(;p<=M;p+=p&(-p))bit[p]++;}

void upd(ll i,ll s,ll e,ll ind, ll k){
	if(s != e){
		if((s+e)/2 < ind) upd(2*i+1,(s+e)/2+1,e,ind,k);
		else upd(2*i,s,(s+e)/2,ind,k);
		st[i] = max(st[2*i],st[2*i+1]);
	}
	else st[i] = k;
}

ll rmq(ll i,ll s,ll e,ll ss,ll se){
	if(ss > se) return -1;
	if(s >= ss && e <= se) return st[i];
	else if((s+e)/2 < ss) return rmq(2*i+1,(s+e)/2+1,e,ss,se);
	else if((s+e)/2 >= se) return rmq(2*i,s,(s+e)/2,ss,se);
	else return max(rmq(2*i+1,(s+e)/2+1,e,ss,se),rmq(2*i,s,(s+e)/2,ss,se));
}

int main(){
	for(scanf("%lld%lld",&N,&K),i=1;i<=N;i++)
		scanf("%lld%lld",&a[i].f,&a[i].s);
	for(i=1;i<=K;i++){
		scanf("%lld",&q[i]);
		p[q[i]]=0;
	}
	for(auto v=p.begin();v!=p.end();v++) v->second = ++n;
	M = p.size();
	for(i=1;i<=K;i++)
		upd(1,1,M,p[q[i]],i);
	for(i=1;i<=N;i++){
		ll l, r;
		auto it = p.lower_bound(max(a[i].f,a[i].s)); --it;
		r = (it==p.end())? -1:it->second;
		it = p.lower_bound(min(a[i].f,a[i].s));
		l = (it==p.end())? 1<<30:it->second;
		a[i].l = rmq(1,1,M,l,r);
	}
	sort(a+1, a+N+1, cmp);
	for(i=N,j=K;i>=1&&a[i].l!=-1;i--){
		while(j>a[i].l){up(p[q[j]]);j--;}
		if(a[i].f < a[i].s) swap(a[i].f,a[i].s);
		auto tmp = p.lower_bound(a[i].f);
		ll ind = (tmp==p.end())? M:tmp->second-1;
		ll t = (qu(M)-qu(ind))%2;
		ans += (t)? a[i].s : a[i].f;
	}
	while(j > 0){up(p[q[j]]); j--;}
	for(;i>=1;i--){
		auto tmp = p.lower_bound(max(a[i].s,a[i].f));
		ll ind = (tmp==p.end())? M:tmp->second-1;
		ll t = (qu(M)-qu(ind))%2;
		ans += (t)? a[i].s : a[i].f;
	}
	printf("%lld\n",ans);
	return 0;
}
