#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,popcnt,avx,mmx,abm")
#include <bits/stdc++.h>
#define DEBUG 1
using namespace std;

namespace output{
    void __(short x){cout<<x;}
    void __(unsigned x){cout<<x;}
    void __(int x){cout<<x;}
    void __(long long x){cout<<x;}
    void __(unsigned long long x){cout<<x;}
    void __(double x){cout<<x;}
    void __(long double x){cout<<x;}
    void __(char x){cout<<x;}
    void __(const char*x){cout<<x;}
    void __(const string&x){cout<<x;}
    void __(bool x){cout<<(x?"true":"false");}
    template<class S,class T>
    void __(const pair<S,T>&x){__(DEBUG?"(":""),__(x.first),__(DEBUG?", ":" "),__(x.second),__(DEBUG?")":"");}
    template<class T>
    void __(const vector<T>&x){__(DEBUG?"{":"");bool _=0;for(const auto&v:x)__(_?DEBUG?", ":" ":""),__(v),_=1;__(DEBUG?"}":"");}
    template<class T>
    void __(const set<T>&x){__(DEBUG?"{":"");bool _=0;for(const auto&v:x)__(_?DEBUG?", ":" ":""),__(v),_=1;__(DEBUG?"}":"");}
    template<class T>
    void __(const multiset<T>&x){__(DEBUG?"{":"");bool _=0;for(const auto&v:x)__(_?DEBUG?", ":" ":""),__(v),_=1;__(DEBUG?"}":"");}
    template<class S,class T>
    void __(const map<S,T>&x){__(DEBUG?"{":"");bool _=0;for(const auto&v:x)__(_?DEBUG?", ":" ":""),__(v),_=1;__(DEBUG?"}":"");}
    void pr(){cout<<"\n";}
    template<class S,class... T>
    void pr(const S&a,const T&...b){__(a);if(sizeof...(b))__(' ');pr(b...);}
}

using namespace output;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,char> pic;
typedef pair<double,double> pdd;
typedef pair<ld,ld> pld;
typedef vector<int> vi;
typedef vector<ll> vl;

#define pb push_back
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second

const int MN = 5e5+5;
struct nd{int sm, l, r;}st[20000000];
int N, M, i, j, nxt, rt[MN];
pii arr[MN];

int build(int s,int e){
    int cur=++nxt;
    if(s!=e){
        st[i].l=build(s,(s+e)/2);
        st[i].r=build((s+e)/2+1,e);
    }
    return cur;
}

int upd(int i,int s,int e,int ind){
    int cur=++nxt;
    if(s==e) st[cur].sm=st[i].sm+1;
    else if((s+e)/2<ind){
        st[cur].r=upd(st[i].r,(s+e)/2+1,e,ind);
        st[cur].l=st[i].l;
        st[cur].sm=st[st[cur].l].sm+st[st[cur].r].sm;
    }
    else{
        st[cur].l=upd(st[i].l,s,(s+e)/2,ind);
        st[cur].r=st[i].r;
        st[cur].sm=st[st[cur].l].sm+st[st[cur].r].sm;
    }
    return cur;
}

int qu(int i,int s,int e,int ss,int se){
    if(ss>se) return 0;
    if(s>=ss&&e<=se) return st[i].sm;
    else if((s+e)/2<ss) return qu(st[i].r,(s+e)/2+1,e,ss,se);
    else if((s+e)/2>=se) return qu(st[i].l,s,(s+e)/2,ss,se);
    else return qu(st[i].l,s,(s+e)/2,ss,se)+qu(st[i].r,(s+e)/2+1,e,ss,se);
}

void init(int n,int *A,int *B){
    N = n;
    for(i=0;i<n;i++)
        arr[i+1]={B[i], A[i]};
    sort(arr+1,arr+N+1,[](pii i,pii j){return i.F>j.F;});
    rt[N+1] = build(1,N);
    for(i=N,j=1;i>=1;i--){
        rt[i] = rt[i+1];
        while(j<=N&&arr[j].F>=i)
            rt[i] = upd(rt[i],1,N,arr[j++].S);
    }
}

inline int func(int x,int y){
    return qu(rt[x],1,N,1,x)-qu(rt[y],1,N,1,x);
}

struct idk{ll dp; int x;}stk[MN];
int tp; vector<idk> vec;

bool opt(int i,idk &j,idk &k){return j.dp-func(i,j.x)>k.dp-func(i,k.x);}

bool chk(int i,idk &a,idk &b,idk &c){
    int lo=0, hi=i+1;
    while(lo<hi){
        int m=(lo+hi)>>1;
        if(opt(vec[m].x,a,b)) hi=m;
        else lo=m+1;
    }
    if(lo) return !opt(vec[lo-1].x,b,c);
    else return 1;
}

int can(int m,int *K){
    map<int,ll> cnt; tp=-1;
    for(i=0;i<m;i++)
        cnt[K[i]]+=K[i];
    vec.clear();
    for(auto v : cnt)
        vec.pb({v.S,v.F});
    vec.pb({0,N+1});
    ll ans = 0;
    for(i=(int)vec.size()-2;i>=0;i--){
        while(tp>=1){
            if(chk(i,vec[i+1],stk[tp],stk[tp-1])) tp--;
            else break;
        }
        stk[++tp]=vec[i+1];
        while(tp>=1){
            if(opt(vec[i].x,stk[tp-1],stk[tp])) tp--;
            else break;
        }
        vec[i].dp+=-func(vec[i].x,stk[tp].x)+stk[tp].dp;
        ans = max(ans, vec[i].dp);
    }
    return ans <= 0;
}

int main(){
    int N;
    scanf("%d",&N);
    int *A = (int*)malloc(sizeof(int)*(unsigned int)N);
    int *B = (int*)malloc(sizeof(int)*(unsigned int)N);
    for (int i = 0; i < N; ++i) {
        scanf("%d",&A[i]);
        scanf("%d",&B[i]);
    }
    init(N, A, B);
    int Q;
    scanf("%d",&Q);
    for (int i = 0; i < Q; ++i) {
        int M;
        scanf("%d",&M);
        int *K = (int*)malloc(sizeof(int)*(unsigned int)M);
        for (int j = 0; j < M; ++j) {
            scanf("%d",&K[j]);
        }
        printf("%d\n", can(M, K));
    }
    return 0;
}