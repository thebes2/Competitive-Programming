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

const int MN = 5e5+5, MM = 21;
int N, M, V, i, x, y, w, dep[MN], ds[MN], b[MM];
vector<pii> adj[MN];
struct edge{int x, y, w;};
vector<edge> ed; vi cyc;
int fnd(int x){return ds[x]=ds[x]==x?x:fnd(ds[x]);}

void dfs(int n,int p){
    for(auto v : adj[n]){
        if(v.first==p) continue;
        dep[v.first]=dep[n]^v.second;
        dfs(v.first, n);
    }
}

int main(){
    scanf("%d%d%d",&N,&M,&V);
    if(!V){pr("yes\n"); return 0;}
    for(i=1;i<=N;i++) ds[i]=i;
    for(i=1;i<=M;i++){
        scanf("%d%d%d",&x,&y,&w);
        if(fnd(x)!=fnd(y)){
            ds[fnd(x)]=fnd(y);
            adj[x].pb({y,w});
            adj[y].pb({x,w});
        }
        else ed.pb({x,y,w});
    }
    dfs(1,0);
    for(auto v : ed){
        cyc.pb(dep[v.x]^dep[v.y]^v.w);
    }
    for(auto v : cyc){
        x = v;
        for(i=MM-1;i>=0;i--){
            if(b[i]){
                if((1<<i)&x) x ^= b[i];
            }
            else if((1<<i)&x){
                b[i] = x;
                break;
            }
        }
    }
    for(i=MM-1;i>=0;i--){
        if((1<<i)&V) V ^= b[i];
    }
    printf("%s\n",V?"no":"yes");
    return 0;
}