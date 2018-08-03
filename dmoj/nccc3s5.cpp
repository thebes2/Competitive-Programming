#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MP = 2e6+6, M=2e6;
ll cnt, tot, N, i, x, y;
struct seg{ll cnt, cost, lazy, ex;}st[3*MP];
string s;

void push(ll i, ll s, ll e){
	if(st[i].lazy == -1){
		if(s != e) st[2*i].lazy=st[2*i+1].lazy=-1;
		if(s != e) st[2*i].ex = st[2*i+1].ex = 0;
		st[i].cnt = st[i].cost = 0;
		st[i].lazy=0;
	}
	if(st[i].ex==0) return;
	st[i].cnt += (e-s+1)*st[i].ex;
	st[i].cost += (e*e+e-(s-1)*(s-1)-s+1)/2*st[i].ex;
	if(s != e){
		st[2*i].ex += st[i].ex;
		st[2*i+1].ex += st[i].ex;
	}
	st[i].lazy = st[i].ex = 0; 
}

void upd1(ll i, ll s, ll e, ll ind, ll num){
	push(i,s,e);
	if(s != e){
		if((s+e)/2 < ind) upd1(2*i+1,(s+e)/2+1,e,ind,num),push(2*i,s,(s+e)/2);
		else upd1(2*i,s,(s+e)/2,ind,num),push(2*i+1,(s+e)/2+1,e);
		st[i].cost = st[2*i].cost+st[2*i+1].cost;
		st[i].cnt = st[2*i].cnt+st[2*i+1].cnt;
	}
	else{
		st[i].cnt += num;
		st[i].cost += num*ind;
	}
}

void upd2(ll i, ll s, ll e, ll ss, ll se, ll num){
	push(i,s,e);
	if(s >= ss && e <= se){
		st[i].ex = num; 
		push(i,s,e);
	}
	else{
		if((s+e)/2 < ss) upd2(2*i+1,(s+e)/2+1,e,ss,se,num),push(2*i,s,(s+e)/2);
		else if((s+e)/2 >= se) upd2(2*i,s,(s+e)/2,ss,se,num),push(2*i+1,(s+e)/2+1,e);
		else{upd2(2*i,s,(s+e)/2,ss,se,num); upd2(2*i+1,(s+e)/2+1,e,ss,se,num);}
		st[i].cost = st[2*i].cost+st[2*i+1].cost;
		st[i].cnt = st[2*i].cnt+st[2*i+1].cnt;
	}
}

ll qu1(ll i, ll s, ll e, ll k){
	push(i,s,e);
	if(s == e){
		ll amt = k/s;
		amt = min(amt,st[i].cnt);
		st[i].cnt -= amt;
		st[i].cost -= s*amt;
		return amt;
	}
	else{
		push(2*i,s,(s+e)/2);
		push(2*i+1,(s+e)/2+1,e);
		ll x = 0;
		if(st[2*i].cost <= k){
			x = st[2*i].cnt;
			k -= st[2*i].cost;
			st[2*i].lazy = -1; st[2*i].ex=0; push(2*i,s,(s+e)/2);
			x += qu1(2*i+1,(s+e)/2+1,e,k);
		}
		else x = qu1(2*i,s,(s+e)/2,k);
		st[i].cost = st[2*i].cost+st[2*i+1].cost;
		st[i].cnt = st[2*i].cnt+st[2*i+1].cnt;
		return x;
	}
}

ll qu2(ll i, ll s, ll e, ll k){
	push(i,s,e);
	if(s == e){
		k = min(k,st[i].cnt);
		st[i].cnt -= k;
		st[i].cost -= s*k;
		return k*s;
	}
	else{
		ll x = 0;
		push(2*i,s,(s+e)/2);
		push(2*i+1,(s+e)/2+1,e);
		if(st[2*i].cnt <= k){
			x = st[2*i].cost;
			k -= st[2*i].cnt;
			st[2*i].lazy = -1; st[2*i].ex=0; push(2*i,s,(s+e)/2);
			x += qu2(2*i+1,(s+e)/2+1,e,k);
		}
		else x = qu2(2*i,s,(s+e)/2,k);
		st[i].cost = st[2*i].cost+st[2*i+1].cost;
		st[i].cnt = st[2*i].cnt+st[2*i+1].cnt;
		return x;
	}
}

ll qu3(ll i, ll s, ll e, ll k){
	push(i,s,e);
	if(s == e){
		k = min(k,st[i].cnt);
		st[i].cnt -= k;
		st[i].cost -= s*k;
		return k*s;
	}
	else{
		ll x = 0;
		push(2*i,s,(s+e)/2);
		push(2*i+1,(s+e)/2+1,e);
		if(st[2*i+1].cnt <= k){
			x = st[2*i+1].cost;
			k -= st[2*i+1].cnt;
			st[2*i+1].lazy = -1; st[2*i+1].ex=0; push(2*i+1,(s+e)/2+1,e);
			x += qu3(2*i,s,(s+e)/2,k);
		}
		else x = qu3(2*i+1,(s+e)/2+1,e,k);
		st[i].cost = st[2*i].cost+st[2*i+1].cost;
		st[i].cnt = st[2*i].cnt+st[2*i+1].cnt;
		return x;
	}
}

ll qu4(ll i, ll s, ll e, ll k){
	push(i,s,e);
	if(s == e){
		if(k>st[i].cnt) return -1;
		else return s;
	}
	else{
		push(2*i,s,(s+e)/2);
		if(st[2*i].cnt<k){
			k -= st[2*i].cnt;
			return qu4(2*i+1,(s+e)/2+1,e,k);
		}
		else return qu4(2*i,s,(s+e)/2,k);
	}
}

int main(){
	for(scanf("%lld",&N);i<N;i++){
		cin >> s;
		if(s == "NUMCONES") printf("%lld\n",st[1].cnt);
		else if(s == "TOTALCOST") printf("%lld\n",st[1].cost);
		else if(s == "COST"){
			scanf("%lld",&x);
			printf("%lld\n",qu4(1,1,M,x));
		}
		else if(s == "ADD"){
			scanf("%lld%lld",&x,&y);
			upd1(1,1,M,y,x);
		}
		else if(s == "ADDRANGE"){
			scanf("%lld%lld",&x,&y);
			upd2(1,1,M,x,y,1);
		}
		else if(s == "BUYAMT"){
			scanf("%lld",&x);
			printf("%lld\n",qu1(1,1,M,x));
		}
		else if(s == "BUYLOW"){
			scanf("%lld",&x);
			printf("%lld\n",qu2(1,1,M,x));
		}
		else if(s == "BUYHIGH"){
			scanf("%lld",&x);
			printf("%lld\n",qu3(1,1,M,x));
		}
	}
	return 0;
}
