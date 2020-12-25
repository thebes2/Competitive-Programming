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

const int MN = 5e5+5;
int N, Q, i, x, y, w, arr[MN];
map<int,int> bit[MN];

inline void do_inc(int id,int v){bit[id][v]++;}
inline void do_dec(int id,int v){bit[id][v]--;if(!bit[id][v]) bit[id].erase(v);}
inline void add(int p,int v){for(;p<=N;p+=p&-p)do_inc(p,v);}
inline void sub(int p,int v){for(;p<=N;p+=p&-p)do_dec(p,v);}
inline int qu(int p,int v){int r=0;for(;p;p-=p&-p)r+=bit[p].count(v)?bit[p][v]:0;return r;}

int main(){
    scanf("%d%d",&N,&Q);
    for(i=1;i<=N;i++) add(i,0);
    for(;Q;Q--){
        scanf("%d%d",&i,&x);
        if(i==1){sub(x,arr[x]),add(x,++arr[x]);}
        else if(i==2){sub(x,arr[x]),add(x,--arr[x]);}
        else{
            scanf("%d%d",&y,&w);
            printf("%d\n",qu(y,w)-qu(x-1,w));
        }
    }
    return 0;
}