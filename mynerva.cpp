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
typedef tuple<int,int,int> t3;

#define pb push_back
#define mt make_tuple
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second

const int MN = 1e4+4;
int N, M, Q, i, x, y, w, vs[MN], dep[MN], dis[MN], mn[MN], mx[MN];
vector<pii> adj[MN]; string st;

struct pq{bool operator()(const pii&i,const pii&j){return i.S>j.S;}};
priority_queue<pii,vector<pii>,pq> q;

int main(){
    scanf("%d%d",&N,&M);
    for(i=1;i<=M;i++){
        scanf("%d%d%d",&x,&y,&w);
        adj[x].pb({y,w});
        adj[y].pb({x,w});
    }
    q.push({1,0});
    int dep = 0;
    while(q.size()){
        int sz=q.size();
        vector<pii> tmp;
        while(sz--){
            pii cur=q.top(); q.pop();
            if(vs[cur.F]) continue;
            vs[cur.F]=1;
            mn[cur.F]=cur.S;
            dis[cur.F]=dep;
            for(auto v : adj[cur.F]){
                if(vs[v.F]) continue;
                tmp.pb({v.F,v.S+cur.S});
            }
        }
        for(auto v : tmp)
            q.push(v);
        dep++;
    }
    memset(vs,0,sizeof(vs));
    q.push({1,0});
    while(q.size()){
        int sz=q.size();
        vector<pii> tmp;
        while(sz--){
            pii cur=q.top(); q.pop();
            if(vs[cur.F]) continue;
            vs[cur.F]=1;
            mx[cur.F]=-cur.S;
            for(auto v : adj[cur.F]){
                if(vs[v.F]) continue;
                tmp.pb({v.F,cur.S-v.S});
            }
        }
        for(auto v : tmp)
            q.push(v);
    }
    for(scanf("%d",&Q);Q;Q--){
        cin >> x >> st;
        printf("%d %d\n",dis[x],(st[0]=='B')?mn[x]:mx[x]);
    }
    return 0;
}