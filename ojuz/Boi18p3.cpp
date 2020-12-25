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

const int MN = 70005;
int N, K, i, x, y, w, ds[MN], val[MN], dep[MN], par[MN], nxt, dn[MN], deg[MN], use[MN], hmm[MN], ra[MN], rb[MN], idd[MN], lst[MN];
int fnd(int x){return ds[x]=ds[x]==x?x:fnd(ds[x]);}
vi adj[MN]; vector<pii> g[MN]; pii ed[MN];
set<pii> st; map<pii,int> id, ans;
struct qur{int x, y, w, id;}q[MN];
vector<qur> a, b; queue<int> go;

void dfs(int n,int p,int d){
    dep[n] = d; par[n] = p;
    for(auto v : adj[n]){
        if(v==p) continue;
        dfs(v, n, d+1);
    }
}

int main(){
    scanf("%d",&N);
    for(i=1;i<N;i++){
        scanf("%d%d",&x,&y);
        adj[x].pb(y);
        adj[y].pb(x);
        id[{min(x,y),max(x,y)}]=i;
        ed[i]={x,y};
    }
    scanf("%d",&K);
    for(i=1;i<=K;i++){
        char ch;
        scanf(" %c%d%d%d",&ch,&x,&y,&w);
        q[i]={x,y,w,N+i};
        if(ch=='M') a.pb({x,y,w,i});
        else b.pb({x,y,w,i});
    }
    sort(a.begin(),a.end(),[](qur i,qur j){return i.w<j.w;});
    sort(b.begin(),b.end(),[](qur i,qur j){return i.w>j.w;});
    dfs(1, 0, 1);
    for(i=1;i<=N;i++)
        ds[i] = i;
    for(auto v : a){
        x = fnd(v.x), y = fnd(v.y);
        while(x!=y){
            if(dep[x]<dep[y]) swap(x,y);
            int cur = id[{min(x,par[x]),max(x,par[x])}];
            ra[cur] = v.id;
            hmm[cur] = v.w;
            ds[x] = fnd(par[x]);
            x = fnd(x);
        }
    }
    for(i=1;i<=N;i++)
        ds[i] = i;
    for(auto v : b){
        x = fnd(v.x), y = fnd(v.y);
        while(x!=y){
            if(dep[x]<dep[y]) swap(x,y);
            int cur = id[{min(x,par[x]),max(x,par[x])}];
            rb[cur] = v.id;
            hmm[cur] = v.w;
            ds[x] = fnd(par[x]);
            x = fnd(x);
        }
    }
    for(i=1;i<N;i++){
        ans[ed[i]]=hmm[i];
    }
    for(i=1;i<N;i++){
        if(ra[i]&&rb[i]){
            g[ra[i]].pb({rb[i],i});
            g[rb[i]].pb({ra[i],i});
        }
        else if(ra[i]) dn[ra[i]] = 1, idd[ra[i]] = i, use[i] = 1;
        else if(rb[i]) dn[rb[i]] = 1, idd[rb[i]] = i, use[i] = 1;
    }
    for(i=1;i<=K;i++){
        set<int> t;
        for(auto v : g[i])
            t.insert(v.first);
        deg[i] = t.size();
        if(deg[i]==1) dn[i]=1;
    }
    for(i=1;i<=K;i++){
        if(dn[i]) go.push(i);
        else st.insert({deg[i], i});
    }
    while(go.size()||st.size()){
        if(go.empty()){
            go.push(st.begin()->second);
            st.erase(st.begin());
        }
        int cur = go.front(); go.pop();
        if(!idd[cur]){
            for(auto v : g[cur]){
                if(!use[v.second]){
                    idd[cur]=v.second;
                    use[v.second]=1;
                    break;
                }
            }
        }
        ans[ed[idd[cur]]]=q[cur].w;
        for(auto v : g[cur]){
            if(dn[v.first]==0||dn[v.first]==cur){
                if(lst[v.first]!=cur){
                    st.erase({deg[v.first],v.first});
                    deg[v.first]--;
                    if(deg[v.first]==1){
                        dn[v.first] = cur;
                        go.push(v.first);
                    }
                    else st.insert({deg[v.first],v.first});
                    lst[v.first]=cur;
                }
                if(!use[v.second]){
                    idd[v.first] = v.second;
                    use[v.second] =1;
                }
            }
        }
    }
    for(i=1;i<N;i++){
        printf("%d %d %d\n",ed[i].first,ed[i].second,ans[ed[i]]);
    }
    return 0;
}