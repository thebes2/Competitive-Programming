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
typedef pair<double,double> pdd;
typedef pair<ld,ld> pld;
typedef vector<int> vi;
typedef vector<ll> vl;

#define pb push_back
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)

const int MN = 1e5+5;
int N, Q, S, E, i, x, y, w, vis[MN][2], nxt, dep[MN], ok[MN], rev[MN];
pii ed[MN], q[MN]; ll st[3*MN], lz[3*MN], dis[MN], ans[MN];
vector<pll> adj[MN], qur[MN];

void dfs(int n,int p,int d){
    vis[n][0] = ++nxt;
    dep[n] = d;
    for(auto v : adj[n]){
        if(v.first==p) continue;
        dis[v.first]=dis[n]+v.second;
        dfs(v.first, n, d+1);
    }
    vis[n][1] = nxt;
}

void build(int i,int s,int e){
    if(s!=e){
        build(2*i,s,(s+e)/2);
        build(2*i+1,(s+e)/2+1,e);
        st[i]=min(st[2*i],st[2*i+1]);
    }
    else st[i]=ok[rev[s]]?dis[rev[s]]:1LL<<60;
}

inline void upd_lz(int i,int s,int e){
    if(lz[i]){
        st[i] += lz[i];
        if(s!=e) lz[2*i]+=lz[i], lz[2*i+1]+=lz[i];
        lz[i] = 0;
    }
}

ll qu(int i,int s,int e,int ss,int se){
    if(ss>se) return 1LL<<60;
    upd_lz(i,s,e);
    if(s>=ss&&e<=se) return st[i];
    else if((s+e)/2<ss) return qu(2*i+1,(s+e)/2+1,e,ss,se);
    else if((s+e)/2>=se) return qu(2*i,s,(s+e)/2,ss,se);
    else return min(qu(2*i,s,(s+e)/2,ss,se),qu(2*i+1,(s+e)/2+1,e,ss,se)); 
}

void upd(int i,int s,int e,int ss,int se,int val){
    upd_lz(i,s,e);
    if(s>=ss&&e<=se){
        lz[i] += val;
        upd_lz(i,s,e);
    }
    else{
        if((s+e)/2<ss) upd(2*i+1,(s+e)/2+1,e,ss,se,val),upd_lz(2*i,s,(s+e)/2);
        else if((s+e)/2>=se) upd(2*i,s,(s+e)/2,ss,se,val),upd_lz(2*i+1,(s+e)/2+1,e);
        else upd(2*i,s,(s+e)/2,ss,se,val),upd(2*i+1,(s+e)/2+1,e,ss,se,val);
        st[i]=min(st[2*i],st[2*i+1]);
    }
}

inline bool cont(int x,int y){return vis[x][0]<=vis[y][0]&&vis[x][1]>=vis[y][1];}
inline bool chk(int x,int y,int c){return cont(c,x)^cont(c,y);}

void solve(int n,int p){
    ll w = 0;
    for(auto v : adj[n]){
        if(v.first == p){
            w = v.second;
        }
    }
    upd(1,1,N,1,N,w);
    upd(1,1,N,vis[n][0],vis[n][1],-2*w);
    for(auto v : qur[n]){
        ans[v.second] = 1LL<<60;
        if(cont(ed[v.first].first,n)){
            int x = ed[v.first].first;
            ans[v.second]=min(ans[v.second],qu(1,1,N,vis[x][0],vis[x][1]));
        }
        else{
            int x = ed[v.first].first;
            ans[v.second]=min(ans[v.second],qu(1,1,N,1,vis[x][0]-1));
            ans[v.second]=min(ans[v.second],qu(1,1,N,vis[x][1]+1,N));
        }
    }
    for(auto v : adj[n]) if(v.first != p) solve(v.first, n);
    upd(1,1,N,1,N,-w);
    upd(1,1,N,vis[n][0],vis[n][1],2*w);
}

int main(){
    scanf("%d%d%d%d",&N,&S,&Q,&E);
    for(i=1;i<N;i++){
        scanf("%d%d%d",&x,&y,&w);
        adj[x].pb({y,w});
        adj[y].pb({x,w});
        ed[i] = {x,y};
    }
    for(i=1;i<=S;i++){
        scanf("%d",&x);
        ok[x] = 1;
    }
    for(i=1;i<=Q;i++){
        scanf("%d%d",&x,&y);
        qur[y].pb({x,i});
        q[i] = {x,y};
    }
    dfs(E,0,1);
    for(i=1;i<N;i++){
        if(dep[ed[i].first]<dep[ed[i].second]) swap(ed[i].first,ed[i].second);
    }
    for(i=1;i<=N;i++) rev[vis[i][0]]=i;
    build(1,1,N);
    solve(E,0);
    for(i=1;i<=Q;i++){
        if(!cont(ed[q[i].first].first,q[i].second)) printf("escaped\n");
        else if(ans[i]>=(2e14)) printf("oo\n");
        else printf("%lld\n",ans[i]);
    }
    return 0;
}