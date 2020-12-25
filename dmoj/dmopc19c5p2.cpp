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

const int MN = 1005;
int N, i, x, y; pii a[MN], b[MN];

int main(){
    for(scanf("%d",&N),i=1;i<=N;i++){
        char ch;
        scanf(" %c%d",&ch,&a[i].second);
        a[i].first=(ch=='A');
    }
    for(i=1;i<=N;i++){
        char ch;
        scanf(" %c%d",&ch,&b[i].second);
        b[i].first=(ch=='A');
    }
    x=y=100;
    b[0].first=1;
    for(i=1;i<=N;i++){
        if(a[i].first){
            if(b[i-1].first) y-=a[i].second;
        }
        else if(!b[i].first) x-=a[i].second;
        if(y<=0){pr("VICTORY\n");return 0;}
        if(x<=0){pr("DEFEAT\n");return 0;}
        if(b[i].first){
            if(a[i].first) x-=b[i].second;
        }
        else if(!a[i+1].first) y-=b[i].second;
        if(y<=0){pr("VICTORY\n");return 0;}
        if(x<=0){pr("DEFEAT\n");return 0;}
    }
    pr("TIE\n");
    return 0;
}