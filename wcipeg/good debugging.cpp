#include <bits/stdc++.h>
using namespace std;

const int MN = 1000006;
struct pii{int f, s;}st[3*MN];
int N, M, L, i, x, y;

void build(int i, int s, int e){
	st[i].f = e-s+1;
	if(s!=e){build(2*i,s,(s+e)/2);build(2*i+1,(s+e)/2+1,e);}
}

void push(int i, int s, int e){
	st[i].s %= 2;
	if(st[i].s) st[i].f = (e-s+1)-st[i].f;
	if(s != e && st[i].s){st[2*i].s++; st[2*i+1].s++;}
	st[i].s = 0;
}

void upd(int i, int s, int e, int ss, int se){
	if(st[i].s%2) push(i, s, e);
	if(s >= ss && e <= se){
		st[i].s++; push(i, s, e);
	}
	else{
		if((s+e)/2 < ss){
			upd(2*i+1,(s+e)/2+1,e,ss,se);
			push(2*i,s,(s+e)/2); 
		}
		else if((s+e)/2 >= se){
			upd(2*i,s,(s+e)/2,ss,se);
			push(2*i+1,(s+e)/2+1,e);
		}
		else{
			upd(2*i,s,(s+e)/2,ss,se);
			upd(2*i+1,(s+e)/2+1,e,ss,se);
		}
		st[i].f = st[2*i].f+st[2*i+1].f;
	}
}

int qu(int i, int s, int e, int b){
	if(s == e) return(st[i].f<b)? s+1:s;
	push(i, s, e); push(2*i,s,(s+e)/2); push(2*i+1,(s+e)/2+1,e);
	if(st[2*i].f >= b) return qu(2*i, s, (s+e)/2, b);
	else return qu(2*i+1, (s+e)/2+1, e, b-st[2*i].f);
}

int main(){
	scanf("%d%d%d",&N,&M,&L);
	build(1, 1, N);
	for(i=0;i<M;i++){
		scanf("%d%d",&x,&y);
		upd(1, 1, N, x, y);
		int tmp = qu(1, 1, N, L);
		if(tmp == N+1) printf("AC?\n");
		else printf("%d\n",tmp);
	}
	return 0;
}
