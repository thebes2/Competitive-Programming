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

const int MN = 3e5+5, LG = 20;
int N, K, i, j, ok[MN], sz[MN], mx[MN], lnk[MN], par[MN], vis[MN][2], ct, c[MN], nxt, x, y, dep[MN], dis[MN], rad[MN], cnt[MN], ans;
vi adj[MN]; pii a[MN], b[MN], arr[MN];

void dfs(int n,int p,int d){
    dep[n]=d; par[n]=p; sz[n]=1;
    vis[n][0] = ++nxt;
    pii big(-1,-1);
    a[n]=b[n]={1<<30,0};
    for(auto v : adj[n]){
        if(v==p) continue;
        dfs(v, n, d+1);
        sz[n] += sz[v];
        if(sz[v] > big.first)
            big={sz[v], v};
        pii ch={a[v].F+1, v};
        if(ch.F<a[n].F) b[n]=a[n],a[n]=ch;
        else if(ch.F<b[n].F) b[n]=ch;
    }
    if(ok[n]) b[n]=a[n], a[n]={0,n};
    vis[n][1] = nxt;
    if(big.second!=-1) lnk[big.second]=n;
}

void dfs2(int n,int up){
    if(!lnk[n]) lnk[n]=n;
    else lnk[n]=lnk[lnk[n]];
    rad[n]=min(up,a[n].F);
    for(auto v : adj[n]){
        if(v==par[n]) continue;
        if(v==a[n].S) dfs2(v,min(up,b[n].F)+1);
        else dfs2(v,min(up,a[n].F)+1);
    }
}

inline bool con(int x,int y){return vis[x][0]<=vis[y][0]&&vis[x][1]>=vis[y][1];}

inline int lca(int x,int y){
    while(!con(lnk[x],y)) x=par[lnk[x]];
    while(!con(lnk[y],x)) y=par[lnk[y]];
    return con(x,y)?x:y;
}

int dfs3(int n,int p){
    sz[n]=1; mx[n]=0;
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        sz[n]+=dfs3(v,n);
        mx[n]=max(mx[n],sz[v]);
    }
    return sz[n];
}

void dfs4(int n,int p,int tot){
    if(2*mx[n]<=tot&&2*(tot-sz[n])<=tot) ct=n;
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        dfs4(v, n, tot);
    }
}

void acc(int n,int p,int d,vector<vi> &dep){
    if(rad[n]>=d) dep.back().pb(rad[n]-d);
    for(auto v : adj[n]){
        if(c[v]||v==p) continue;
        acc(v, n, d+1, dep);
    }
}

inline void upd(vi &bit,int p,int v){for(p++;p<bit.size();p+=p&-p)bit[p]+=v;}
inline int qu(vi &bit,int p){int r=0;for(p++;p;p-=p&-p)r+=bit[p];return r;}

void prop(int n,int p,int d,vi &bit,int tot){
    cnt[n] += tot-qu(bit,d-1);
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        prop(v, n, d+1, bit, tot);
    }
}

void go(int n){
    dfs4(n, 0, dfs3(n, 0));
    c[ct] = 1;
    vector<vector<int>> dep;
    vi bit; bit.resize(sz[ct]+5);
    dep.pb(vi()); 
    if(rad[ct]>=0){
        dep.back().pb(rad[ct]);
        cnt[ct]++;
    }
    for(auto v : adj[ct]){
        if(c[v]) continue;
        dep.pb(vi());
        acc(v, ct, 1, dep);
        cnt[ct] += dep.back().size();
    }
    int tot=0;
    for(auto u : dep){
        for(auto v : u) upd(bit,v,1),tot++;
    }
    int cur=1;
    for(auto v : adj[ct]){
        if(c[v]) continue;
        for(auto u : dep[cur])
            upd(bit,u,-1),tot--;
        prop(v, ct, 1, bit, tot);
        for(auto u : dep[cur])
            upd(bit,u,1),tot++;
        cur++;
    }
    for(auto v : adj[ct]){
        if(!c[v]) go(v);
    }
}

void solve(){
    scanf("%d%d",&N,&K);
    for(i=1;i<=N;i++)
        adj[i].clear();
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(i=1;i<N;i++){
        scanf("%d%d",&x,&y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for(i=1;i<=K;i++){
        scanf("%d",&x);
        ok[x]=1;
    }
    dfs(1, 0, 0);
    dfs2(1,1<<30);
    for(i=1;i<=N;i++){
        scanf("%d%d",&x,&y);
        int dis=dep[x]+dep[i]-2*dep[lca(x,i)]-y-1;
        rad[i]=min(rad[i],dis);
    }
    go(1);
    for(i=1;i<=N;i++)
        printf("%d ",cnt[i]);
    pr();
    return;
}

int main(){
    solve();
}