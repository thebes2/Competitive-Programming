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

const int MN = 2e5+6, mod = 1e9+7;
int H, W, N, i, j, x, y, dp[MN], fac[MN]={1}, inv[MN]={1};
pii pnt[MN];

int qpow(int b,int exp){
    if(exp<=0) return 1;
    else if(exp&1) return 1LL*b*qpow(b,exp-1)%mod;
    else{int r=qpow(b,exp>>1); return 1LL*r*r%mod;}
}

int main(){
    for(i=1;i<MN;i++){
        fac[i]=1LL*i*fac[i-1]%mod;
        inv[i]=1LL*qpow(i,mod-2)*inv[i-1]%mod;
    }
    scanf("%d%d%d",&H,&W,&N);
    for(i=1;i<=N;i++){
        scanf("%d%d",&pnt[i].first,&pnt[i].second);
    }
    sort(pnt+1,pnt+N+1,[](pii i,pii j){return i.first+i.second<j.first+j.second;});
    pnt[++N]={H,W};
    for(i=1;i<=N;i++){
        int ok = 1LL*fac[pnt[i].F+pnt[i].S-2]*inv[pnt[i].F-1]%mod*inv[pnt[i].S-1]%mod;
        for(int j=1;j<i;j++){
            if(pnt[i].F>=pnt[j].F&&pnt[i].S>=pnt[j].S){
                int bad = 1LL*dp[j]*fac[pnt[i].F+pnt[i].S-pnt[j].F-pnt[j].S]%mod*inv[pnt[i].F-pnt[j].F]%mod*inv[pnt[i].S-pnt[j].S]%mod;
                ok = (ok+mod-bad)%mod;
            }
        }
        dp[i]=ok;
    }
    printf("%d\n",dp[N]);
    return 0;
}