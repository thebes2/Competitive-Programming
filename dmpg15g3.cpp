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

const int MN = 2e5+5;
int N, K[2], C[2], i, x, y, sz[MN], mx[MN], c[MN], ct, bit[MN], tp[MN]; ll ans;
vi adj[MN];

inline void upd(int p,int v){for(++p;p<=N+1;p+=p&-p)bit[p]+=v;}
inline int qu(int p){int r=0;for(++p;p>0;p-=p&-p)r+=bit[p];return r;}

int dfs(int n,int p){
    sz[n]=1; mx[n]=0;
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        sz[n]+=dfs(v,n);
        mx[n]=max(mx[n],sz[v]);
    }
    return sz[n];
}

void dfs2(int n,int p,int t){
    if(2*mx[n]<=t&&2*(t-sz[n])<=t) ct=n;
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        dfs2(v,n,t);
    }
}

void acc(int n,int p,pii dep,vector<pii> &a){
    if(tp[n]==1) dep.first++;
    else dep.second++;
    a.pb(dep);
    for(auto v : adj[n]){
        if(v==p||c[v]) continue;
        acc(v,n,dep,a);
    }
}

ll solve(vector<pii> &pnt,pii &rt){
    sort(pnt.begin(),pnt.end());
    ll res=0, l=pnt.size(), r=pnt.size()-1;
    for(auto v : pnt){
        while(l>0&&pnt[l-1].first+rt.first+v.first>=K[0])
            upd(pnt[--l].second,1);
        while(r>=l&&pnt[r].first+rt.first+v.first>K[1])
            upd(pnt[r--].second,-1);
        res+=qu(C[1]-rt.second-v.second)-qu(C[0]-1-rt.second-v.second);
    }
    for(ll i=l;i<=r;i++)
        upd(pnt[i].second,-1);
    return res;
}

void go(int n){
    dfs2(n,0,dfs(n,0));
    c[ct]=1;
    pii rt={tp[ct],!tp[ct]};
    vector<pii> tot; tot.pb({0,0});
    ll dif=0;
    for(auto v : adj[ct]){
        if(c[v]) continue;
        vector<pii> tmp;
        acc(v,ct,make_pair(0,0),tmp);
        dif-=solve(tmp,rt);
        for(auto v : tmp)
            tot.pb(v);
    }
    dif+=solve(tot,rt);
    if(rt.first>=K[0]&&rt.first<=K[1]&&rt.second>=C[0]&&rt.second<=C[1]) dif++;
    dif/=2;
    ans+=dif;
    for(auto v : adj[ct]){
        if(c[v]) continue;
        go(v);
    }
}

int main(){
    scanf("%d%d%d%d%d\n",&N,&K[0],&K[1],&C[0],&C[1]);
    for(i=1;i<=N;i++)
        tp[i]=getchar()=='K';
    for(i=1;i<N;i++){
        scanf("%d%d",&x,&y);
        adj[x].pb(y);
        adj[y].pb(x);
    }
    go(1);
    printf("%lld\n",ans);
    return 0;
}
