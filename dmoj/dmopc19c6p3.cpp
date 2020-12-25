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

const int MN = 5e5+5, mod = 1e9+7;
int N, Q, i, x, y, pw[MN], ds[MN], ans, ok[MN];
int fnd(int x){return ds[x]=ds[x]==x?x:fnd(ds[x]);}
string s;

inline void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
inline void mrk(int x){
    add(ans,pw[x]); ok[x]=1;
    if(ok[x+1]) ds[fnd(x)]=fnd(x+1);
    if(ok[x-1]) ds[fnd(x-1)]=fnd(x);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> Q >> s;
    pw[N] = 1;
    for(i=N-1;i>=1;i--) pw[i]=2LL*pw[i+1]%mod;
    for(i=1;i<=N;i++) ds[i]=i;
    for(i=N;i>=1;i--) if(s[i-1]=='1') mrk(i);
    for(;Q;Q--){
        cin >> x >> y;
        if(!ok[x]) mrk(x);
        while(fnd(x)+1<=y) mrk(fnd(x)+1);
        printf("%d\n",ans);
    }
}