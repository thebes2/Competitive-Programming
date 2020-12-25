#include "railroad.h"
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

const int MN = 2e5+5;
int N, i, j, x, y, ds[2*MN], rev[2*MN], cur, nxt;
pii evt[2*MN]; ll ans; map<int,int> mp;
int fnd(int x){return ds[x]=x==ds[x]?x:fnd(ds[x]);}
struct edge{int x,y,w;};vector<edge> vec;

ll plan_roller_coaster(int _N,int *_s,int *_t){
    vi s, t;
    for(i=0;i<_N;i++)
        s.pb(_s[i]), t.pb(_t[i]);
    s.pb(1e9+7); t.pb(0);
    N = (int)s.size();
    for(i=0;i<N;i++){
        evt[2*i+1]={s[i],0};
        evt[2*i+2]={t[i],1};
        mp[s[i]]=mp[t[i]]=0;
    }
    for(auto it=mp.begin();it!=mp.end();it++)
        it->second = ++nxt, rev[nxt] = it->first;
    for(i=1;i<=nxt;i++) ds[i]=i;
    sort(evt+1,evt+2*N+1,[](pii i,pii j){return i.F<j.F;});
    for(i=1;i<=2*N;i++){
        if(!evt[i].S) cur--;
        else cur++;
        if(i+1<=2*N){
            if(cur<0){
                ans += -1LL*cur*(evt[i+1].F-evt[i].F);
                if(fnd(mp[evt[i].F])!=fnd(mp[evt[i+1].F]))
                    ds[fnd(mp[evt[i].F])]=fnd(mp[evt[i+1].F]);
            }
            else if(cur>0&&fnd(mp[evt[i].F])!=fnd(mp[evt[i+1].F]))
                ds[fnd(mp[evt[i].F])]=fnd(mp[evt[i+1].F]);
        }
    }
    for(i=0;i<N;i++){
        x=fnd(mp[s[i]]), y=fnd(mp[t[i]]);
        if(x!=y) ds[x]=y;
    }
    for(i=1;i<nxt;i++){
        if(fnd(i)!=fnd(i+1))
            vec.pb({i,i+1,rev[i+1]-rev[i]});
    }
    sort(vec.begin(),vec.end(),[](edge i,edge j){return i.w<j.w;});
    for(auto v : vec){
        x=v.x, y=v.y;
        if(fnd(x)!=fnd(y)){
            ds[fnd(x)]=fnd(y);
            ans += v.w;
        }
    }
    return ans;
}