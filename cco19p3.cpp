#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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
#define F first
#define S second

const int MN = 2e5+5;
int N, A[MN], sz[MN], mx[MN], i, j, x, y; ll sm[MN], ans, tot;
vi adj[MN];

int init(int n){
    sz[n]=A[n]; sm[n]=0;
    for(auto v : adj[n]){
        sz[n]+=init(v);
        sm[n]+=sm[v];
        mx[n]=max(mx[n],sz[v]);
    }
    sm[n]+=1LL*(sz[n]-A[n])*A[n]+1LL*A[n]*(A[n]-1);
    return sz[n];
}

vector<pll> a, b;
void rec(ll l,ll r,pll acc,vl &arr){
    if(l>r) a.pb(acc);
    else{
        rec(l+1,r,make_pair(acc.first+arr[l],acc.second),arr);
        rec(l+1,r,make_pair(acc.first,acc.second+arr[l]),arr);
    }
}

void solve(int n,ll up){
    up+=1LL*(tot-sz[n])*A[n]+1LL*A[n]*(A[n]-1);
    if(2LL*mx[n]<=tot&&2LL*(tot-sz[n])<=tot){
        vl sub;
        ll tmp=up;
        for(auto v : adj[n]){
            tmp+=sm[v]+1LL*A[n]*sz[v];
            sub.pb(sz[v]);
        }
        if(tot-sz[n]) sub.pb(tot-sz[n]);
        a.clear(); b.clear();
        a.pb({0,0}); b.pb({0,0});
        rec(0,sub.size()/2,make_pair(0,0),sub);
        swap(a,b);
        rec(sub.size()/2+1,sub.size()-1,make_pair(0,0),sub);
        sort(a.begin(),a.end(),[](pll i,pll j){return i.first-i.second<j.first-j.second;});
        sort(b.begin(),b.end(),[](pll i,pll j){return i.first-i.second>j.first-j.second;});
        pll opt(0,0);
        for(i=j=0;i<a.size();i++){
            while(j+1<b.size()&&b[j+1].first-b[j+1].second+a[i].first-a[i].second>=0) j++;
            if((a[i].first+b[j].first)*(a[i].second+b[j].second)>opt.first*opt.second)
                opt={a[i].first+b[j].first,a[i].second+b[j].second};
            if(j+1<b.size()&&(a[i].first+b[j+1].first)*(a[i].second+b[j+1].second)>opt.first*opt.second)
                opt={a[i].first+b[j+1].first,a[i].second+b[j+1].second};
        }
        tmp+=opt.first*opt.second;
        ans=max(ans,tmp);
    }
    else{
        ll tmp=up, big=0;
        for(auto v : adj[n]){
            tmp+=sm[v];
            big=max(big,(ll)sz[v]);
        }
        big=max(big,tot-sz[n]);
        tmp+=big*(tot-A[n]-big);
        ans=max(ans,tmp);
    }
    ll acc=0;
    for(auto v : adj[n])
        acc+=sm[v]+1LL*A[n]*sz[v];
    for(auto v : adj[n])
        solve(v,up+acc-sm[v]-1LL*A[n]*sz[v]);
}

int main(){
    for(scanf("%d",&N),i=1;i<=N;i++)
        scanf("%d",&A[i]),tot+=A[i];
    for(i=2;i<=N;i++){
        scanf("%d",&x);
        adj[x].pb(i);
    }
    init(1);
    solve(1,0);
    printf("%lld\n",ans);
    return 0;
}