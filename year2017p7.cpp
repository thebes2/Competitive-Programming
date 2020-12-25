#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

const int MN = 1e5+5, LG = 18;
int N, Q, i, j, x, y, vis[MN][2], nxt, ans[MN], lz[3*MN], rev[MN], bs[MN], sp[LG][MN]; ll t[MN], dep[MN];
vector<pii> adj[MN]; pii st[3*MN];

void build(int i,int s,int e){
    if(s!=e){
        build(2*i,s,(s+e)/2);
        build(2*i+1,(s+e)/2+1,e);
        st[i].F=min(st[2*i].F,st[2*i+1].F);
        st[i].S=max(st[2*i].F==st[i].F?st[2*i].S:0,st[2*i+1].F==st[i].F?st[2*i+1].S:0);
    }
    else st[i]={0,ans[rev[s]]};
}

inline void upd_lz(int i,int s,int e){
    if(lz[i]){
        st[i].F+=lz[i];
        if(s!=e) lz[2*i]+=lz[i],lz[2*i+1]+=lz[i];
        lz[i]=0;
    }
}

void upd(int i,int s,int e,int ss,int se,int val){
    upd_lz(i,s,e);
    if(s>=ss&&e<=se) lz[i]=val,upd_lz(i,s,e);
    else{
        if((s+e)/2<ss) upd(2*i+1,(s+e)/2+1,e,ss,se,val),upd_lz(2*i,s,(s+e)/2);
        else if((s+e)/2>=se) upd(2*i,s,(s+e)/2,ss,se,val),upd_lz(2*i+1,(s+e)/2+1,e);
        else upd(2*i,s,(s+e)/2,ss,se,val),upd(2*i+1,(s+e)/2+1,e,ss,se,val);
        st[i].F=min(st[2*i].F,st[2*i+1].F);
        st[i].S=max(st[2*i].F==st[i].F?st[2*i].S:0,st[2*i+1].F==st[i].F?st[2*i+1].S:0);
    }
}

void dfs(int n,int p,int d){
    vis[n][0]=++nxt;
    rev[nxt]=n;
    ans[n]=d; sp[0][n]=p;
    for(auto v : adj[n]){
        if(v.first==p) continue;
        dep[v.first]=dep[n]+v.second;
        dfs(v.first,n,d+1);
    }
    vis[n][1]=nxt;
}

inline int block(int x){
    int cur=x;
    for(j=LG-1;j>=0;j--){
        if(dep[sp[j][cur]]>=t[x])
            cur=sp[j][cur];
    }
    return cur;
}

int main(){
    for(scanf("%d",&N),i=1;i<=N;i++)
        scanf("%lld",&t[i]);
    for(i=1;i<=N;i++){
        scanf("%d%d",&x,&y);
        adj[x].pb({i,y});
    }
    dfs(0,0,0);
    build(1,1,nxt);
    for(j=1;j<LG;j++){
        for(i=1;i<=N;i++)
            sp[j][i]=sp[j-1][sp[j-1][i]];
    }
    for(i=1;i<=N;i++){
        if(t[i]<=dep[i]){
            int nd=block(i); bs[i]=nd;
            upd(1,1,nxt,vis[nd][0],vis[nd][1],1);
        }
    }
    for(scanf("%d",&Q);Q;Q--){
        scanf("%d%d",&x,&y);
        if(bs[x]) upd(1,1,nxt,vis[bs[x]][0],vis[bs[x]][1],-1);
        t[x]=y;
        if(t[x]<=dep[x]) bs[x]=block(x),upd(1,1,nxt,vis[bs[x]][0],vis[bs[x]][1],1);
        else bs[x]=0;
        if(st[1].first==0) printf("%d\n",st[1].second);
        else printf("0\n");
    }
    return 0;
}