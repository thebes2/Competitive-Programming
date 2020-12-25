#include <iostream>
using namespace std;

const int MN = 2000005;
struct node{int a[2], b[2], l;}st[3*MN];

void upd(int i, int t, int s, int e){
    if(s == e){
		if(t == 0){
			st[i].a[0] = max(st[i].a[0], st[i].b[0]);
			st[i].a[1] = max(st[i].a[0], st[i].a[1]);
		}
		else if(t == 1){
			st[i].a[1] = min(st[i].a[1], st[i].b[1]);
			st[i].a[0] = min(st[i].a[1], st[i].a[0]);
		}
	}
    if(s != e){
        for(int k=0;k<2;k++){
            if(st[2*i+k].l == -1){
                st[2*i+k].l = t; 
                st[2*i+k].b[t] = st[i].b[t];
            }
            else if(st[2*i+k].l == t){
                if(t == 0){st[2*i+k].b[0]=max(st[2*i+k].b[0],st[i].b[0]);}
                else if(t == 1){st[2*i+k].b[1]=min(st[2*i+k].b[1],st[i].b[1]);}
            }
            else if(st[2*i+k].l != t){
                st[2*i+k].l = !st[2*i+k].l;
                if(st[2*i+k].b[t] == -1) st[2*i+k].b[t] = st[i].b[t];
                else if(t == 0) st[2*i+k].b[0] = max(st[i].b[0],min(st[2*i+k].b[1],st[2*i+k].b[0]));
                else st[2*i+k].b[1] = min(st[i].b[1],max(st[2*i+k].b[0],st[2*i+k].b[1])); 
            }
        }
    }
    st[i].b[t] = -1;
}

void shift(int i, int s, int e){
    if(st[i].b[!st[i].l] != -1) upd(i, !st[i].l, s, e);
    if(st[i].b[st[i].l] != -1) upd(i, st[i].l, s, e);
	st[i].l = -1;
}

void update(int i, int s, int e, int ss, int se, int t, int h){
    if(st[i].l != -1) shift(i,s,e);
    if(s >= ss && e <= se){
        st[i].l = t; st[i].b[t] = h;
        shift(i,s,e);
    }
    else{
        if((s+e)/2 < ss) update(2*i+1,(s+e)/2+1,e,ss,se,t,h);
        else if((s+e)/2 >= se) update(2*i,s,(s+e)/2,ss,se,t,h);
        else{update(2*i+1,(s+e)/2+1,e,ss,se,t,h);update(2*i,s,(s+e)/2,ss,se,t,h);}
    }
}

void ans(int i, int s, int e, int *ret){
    if(st[i].l != -1) shift(i,s,e);
    if(s != e){
        ans(2*i,s,(s+e)/2,ret); 
        ans(2*i+1,(s+e)/2+1,e,ret);
    }
    else ret[s] = st[i].a[0];
}

void buildWall(int n, int k, int *op, int *l, int *r, int *h, int *ret){
    for(int i=0;i<3*MN;i++){
        st[i].b[0] = st[i].b[1] = st[i].l = -1;
    }
    for(int i=0;i<k;i++){
        update(1,0,n-1,l[i],r[i],op[i]-1,h[i]);
    }
    ans(1,0,n-1,ret);
}
