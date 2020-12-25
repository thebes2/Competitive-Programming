#include "simurgh.h"
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
#define eb emplace_back
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second
 
const int MN = 505;
int N, M, i, x, y, bk[MN], par[MN], id[MN], use[MN], vs[MN], val[MN*MN], dep[MN], ds[MN];
vector<pii> adj[MN], tr[MN]; vi wew, ans, tmp, a, b; pii meh[MN];
 
void dfs(int n,int p){
    vs[n] = 1;
    meh[n] = {1<<30, 0};
    for(auto v : adj[n]){
        if(vs[v.F]){
            if(v.F==p) continue;
            if(dep[v.F]<meh[n].F) meh[n]={dep[v.F],v.S};
        }
        else{
            dep[v.F] = dep[n]+1;
            par[v.F] = n;
            id[v.F] = v.S;
            dfs(v.F, n);
            wew.pb(v.S);
            tr[n].pb(v);
            tr[v.F].pb({n,v.S});
            if(meh[v.F].F<meh[n].F) meh[n]=meh[v.F];
        }
    }
    if(meh[n].F<dep[n]) bk[n]=meh[n].S;
}
 
inline void ini(){tmp.clear(); for(int _=0;_<N;_++)ds[_]=_;}
int fnd(int x){return ds[x]=x==ds[x]?x:fnd(ds[x]);}
bool uni(int x,int y){
    x=fnd(x), y=fnd(y);
    if(x!=y){ds[x]=y; return 1;}
    else return 0;
}
int treeify(){
    int res=0;
    for(auto v : wew){
        if(uni(a[v],b[v])){
            tmp.pb(v);
            res += val[v];
        }
    }
    return res;
}
 
vi find_roads(int n,vi u,vi v){
    N = n; M = (int)u.size();
    for(i=0;i<M;i++){
        adj[u[i]].pb({v[i],i});
        adj[v[i]].pb({u[i],i});
    }
    a=u, b=v;
    memset(bk,-1,sizeof(bk));
    dfs(0,-1);
    memset(val, -1, sizeof(val));
    int init = count_common_roads(wew);
    for(i=1;i<N;i++){
        if(bk[i]==-1) val[id[i]]=1;
        else{
            if(val[bk[i]]==-1){
                int ed = bk[i];
                x=u[ed], y=v[ed];
                if(dep[x]<dep[y]) swap(x,y);
                int dn = -1; vi acc;
                while(x!=y){
                    if(~val[id[x]]){
                        dn = id[x];
                        break;
                    }
                    acc.pb(id[x]);
                    x = par[x];
                }
                if(~dn){
                    wew.erase(find(wew.begin(),wew.end(),dn));
                    wew.pb(bk[i]);
                    int res = count_common_roads(wew);
                    wew.erase(find(wew.begin(),wew.end(),bk[i]));
                    wew.pb(dn);
                    val[bk[i]] = res-init+val[dn];
                }
                else{
                    int mx = init;
                    vi res;
                    for(auto v : acc){
                        wew.erase(find(wew.begin(),wew.end(),v));
                        wew.pb(bk[i]);
                        res.pb(count_common_roads(wew));
                        mx = max(res.back(), mx);
                        wew.pop_back();
                        wew.pb(v);
                    }
                    int fl=0;
                    for(auto v : res){
                        if(v!=mx) fl=1;
                    }
                    if(fl){
                        for(int j=0;j<(int)acc.size();j++){
                            if(res[j]!=mx) val[acc[j]]=1;
                            else val[acc[j]]=0;
                        }
                        if(init!=mx) val[bk[i]]=1;
                        else val[bk[i]]=0;
                    }
                    else{
                        for(int j=0;j<(int)acc.size();j++)
                            val[acc[j]]=0;
                        val[bk[i]]=0;
                    }
                }
            }
            if(val[id[i]]==-1){
                wew.erase(find(wew.begin(),wew.end(),id[i]));
                wew.pb(bk[i]);
                int res = count_common_roads(wew);
                wew.erase(find(wew.begin(),wew.end(),bk[i]));
                wew.pb(id[i]);
                val[id[i]] = init-res+val[bk[i]];
            }
        }
    }
    for(i=0;i<M;i++){
        if(val[i]==1) ans.pb(i);
    }
    for(i=0;i<N;i++){
        vi vec;
        for(auto v : adj[i]){
            if(val[v.S]==-1)
                vec.pb(v.S);
        }
        if(vec.size()){
            ini();
            for(auto v : vec){
                tmp.pb(v);
                uni(a[v],b[v]);
            }
            int r = treeify();
            int k = count_common_roads(tmp)-r;
            while(k--){
                int lo=0, hi=(int)vec.size()-1;
                while(lo<hi){
                    int mid=(lo+hi)>>1;
                    ini();
                    for(int j=mid+1;j<=hi;j++){
                        tmp.pb(vec[j]);
                        uni(a[vec[j]],b[vec[j]]);
                    }
                    int r = treeify();
                    if(count_common_roads(tmp)-r>0) lo=mid+1;
                    else hi=mid;
                }
                val[vec[lo]]=1;
                ans.pb(vec[lo]);
                for(int j=lo+1;j<(int)vec.size();j++)
                    val[vec[j]]=0;
                vec.erase(vec.begin()+lo,vec.end());
            }
        }
    }
    //pr(">",ans);
    return ans;
}