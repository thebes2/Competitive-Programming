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

const int MN = 1e5+5, MM = 2e5+5;
int N, M, A, B, C, i, j, use[MM], sz[MN], mx[MN], vs[MN], ds[MN], cc[MN], ct, rem;
vi tree[MN], ans;
vector<pii> adj[MN], hm;
int fnd(int x){return ds[x]=x==ds[x]?x:fnd(ds[x]);}

void dfs(int n){
    vs[n] = 1;
    for(auto v : adj[n]){
        if(!vs[v.F]){
            use[v.S]=1;
            dfs(v.F);
            tree[n].pb(v.F);
            tree[v.F].pb(n);
        }
    }
}

void dfs2(int n,int p){
    sz[n]=1; mx[n]=0;
    for(auto v : tree[n]){
        if(v==p) continue;
        dfs2(v, n);
        sz[n] += sz[v];
        mx[n] = max(mx[n], sz[v]);
    }
}

void dfs3(int n,int p){
    if(2*mx[n]<=N&&2*(N-sz[n])<=N) ct=n;
    for(auto v : tree[n]){
        if(v==p) continue;
        dfs3(v, n);
    }
}

void go(int n,int p){
    cc[fnd(n)]++;
    for(auto v : tree[n]){
        if(v==p) continue;
        ds[v] = ds[n];
        go(v, n);
    }
}

void mrk(int n,int g,int id,bool wew=false){
    vs[n] = 1;
    if(rem){
        ans[n]=id; rem--;
        for(auto v : adj[n]){
            if(!wew&&fnd(v.F)==g&&!vs[v.F]&&rem) mrk(v.F,g,id);
            if(wew&&fnd(v.F)!=g&&!vs[v.F]&&rem) mrk(v.F,g,id,wew);
        }
    }
}

vi find_split(int n,int a,int b,int c,vi p,vi q){
    N = n; M = (int)p.size();
    int w[]={1,2,3};
    A=a, B=b, C=c;
    ans.resize(N);
    if(A>B) swap(A,B), swap(w[0],w[1]);
    if(A>C) swap(A,C), swap(w[0],w[2]);
    if(B>C) swap(B,C), swap(w[1],w[2]);
    for(i=0;i<M;i++){
        adj[p[i]].pb({q[i],i});
        adj[q[i]].pb({p[i],i});
    }
    dfs(1);
    dfs2(1,-1);
    dfs3(1,-1);
    dfs2(ct,-1);
    ds[ct]=ct;
    for(auto v : tree[ct]){
        ds[v] = v;
        go(v, ct);
    }
    memset(vs,0,sizeof(vs));
    for(i=0;i<N;i++){
        if(cc[i]>=A){
            if(cc[i]>=B){
                rem = B;
                mrk(i,i,w[1]);
                rem = A;
                mrk(ct,i,w[0],1);
            }
            else{
                rem = A;
                mrk(i,i,w[0]);
                rem = B;
                mrk(ct,i,w[1],1);
            }
            for(auto &v : ans){
                if(!v) v=w[2];
            }
            return ans;
        }
    }
    for(i=0;i<M;i++){
        if(use[i]) continue;
        int x=p[i], y=q[i];
        if(x==ct||y==ct) continue;
        if(fnd(x)!=fnd(y)){
            x=fnd(x), y=fnd(y);
            cc[x] += cc[y];
            ds[y] = x;
            if(cc[x]>=A){
                if(cc[x]>=B){
                    rem = B;
                    mrk(x,x,w[1]);
                    rem = A;
                    mrk(ct,x,w[0],1);
                }
                else{
                    rem = A;
                    mrk(x,x,w[0]);
                    rem = B;
                    mrk(ct,x,w[1],1);
                }
                for(auto &v : ans){
                    if(!v) v=w[2];
                }
                return ans;
            }
        }
    }
    return ans;
}