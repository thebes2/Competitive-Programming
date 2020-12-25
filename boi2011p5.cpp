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

const int MN = 202, MM = 1e4+5;
int N, M, i, j, x[MM], y[MM], t[MM], c[MM], ds[MN], ord[MM], id, _; ll w[MM], ans;
bool cmp(int i,int j){return w[i]<w[j];}
int fnd(int x){return ds[x]=x==ds[x]?x:fnd(ds[x]);}
inline void init(){for(_=0;_<N;_++)ds[_]=_;}
pii A, B, hm, sna, cur;
inline void doit(pii ww){for(_=0;_<M;_++)w[_]=t[_]*ww.first+c[_]*ww.second;}
vector<pii> ed; queue<pair<pii,pii>> vis;

int main(){
    for(scanf("%d%d",&N,&M),i=0;i<M;i++){
        scanf("%d%d%d%d",&x[i],&y[i],&t[i],&c[i]);
        w[i]=t[i]; ord[i]=i;
    }
    ans=1LL<<60;
    sort(ord,ord+M,cmp);
    init();
    for(i=0;i<M;i++){
        id=ord[i];
        if(fnd(x[id])!=fnd(y[id])){
            ds[fnd(x[id])]=fnd(y[id]);
            A.first+=t[id];
            A.second+=c[id];
        }
    }
    if(A.first*A.second<ans) ans=A.first*A.second,sna={1,0};
    for(i=0;i<M;i++)
        w[i]=c[i];
    sort(ord,ord+M,cmp);
    init();
    for(i=0;i<M;i++){
        id=ord[i];
        if(fnd(x[id])!=fnd(y[id])){
            ds[fnd(x[id])]=fnd(y[id]);
            B.first+=t[id];
            B.second+=c[id];
        }
    }
    if(B.first*B.second<ans) ans=B.first*B.second,sna={0,1};
    vis.push({A,B});
    while(vis.size()){
        pii l=vis.front().first,r=vis.front().second;
        vis.pop();
        cur={-r.second+l.second,-l.first+r.first};
        ll zero=r.first*l.second-r.second*l.first;
        doit(cur);
        hm={0,0};
        sort(ord,ord+M,cmp);
        init();
        ll acc=0;
        for(i=0;i<M;i++){
            id=ord[i];
            if(fnd(x[id])!=fnd(y[id])){
                ds[fnd(x[id])]=fnd(y[id]);
                acc+=w[id];
                hm.first+=t[id];
                hm.second+=c[id];
            }
        }
        if(hm.first*hm.second<ans){
            ans=hm.first*hm.second;
            sna=cur;
        }
        if(acc<zero){
            vis.push({l,hm});
            vis.push({hm,r});
        }
    }
    hm={0,0};
    doit(sna);
    sort(ord,ord+M,cmp);
    init();
    for(i=0;i<M;i++){
        id=ord[i];
        if(fnd(x[id])!=fnd(y[id])){
            ds[fnd(x[id])]=fnd(y[id]);
            hm.first+=t[id];
            hm.second+=c[id];
            ed.pb({x[id],y[id]});
        }
    }
    printf("%d %d\n",hm.first,hm.second);
    for(auto v : ed)
        printf("%d %d\n",v.first,v.second);
    return 0;
}