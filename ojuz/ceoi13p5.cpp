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

const int MN = 250005, N = 2505;
int M, i, j, x, y, ps[N][N]; ll dp[2][N][N];
pii r[N], c[N], pos[MN];
inline int sum(int x,int y,int a,int b){
    return max(0,ps[a][b]-ps[x-1][b]-ps[a][y-1]+ps[x-1][y-1]);
}

int main(){
    scanf("%d",&M);
    for(i=0;i<N;i++)
        r[i].F=c[i].F=N+1;
    for(i=1;i<=M;i++){
        scanf("%d%d",&x,&y);
        pos[i] = {x,y};
        ps[x][y] ++;
        r[x].F=min(r[x].F, y);
        r[x].S=max(r[x].S, y);
        c[y].F=min(c[y].F, x);
        c[y].S=max(c[y].S, x);
    }
    for(i=1;i<N;i++){
        r[i+1].F=min(r[i+1].F,r[i].F);
        c[i+1].F=min(c[i+1].F,c[i].F);
    }
    for(i=N-1;i>=1;i--){
        c[i-1].S=max(c[i-1].S,c[i].S);
        r[i-1].S=max(r[i-1].S,r[i].S);
    }
    for(i=1;i<N;i++){
        for(j=1;j<N;j++)
            ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
    }
    for(i=1;i<N;i++){
        for(j=N-1;j>=1;j--){
            if(sum(1,j,i,N-1)){
                int nx = min(i,c[j-1].F), ny = max(j,r[i+1].S);
                int tot = sum(1,j,i,N-1);
                dp[0][i][j]=tot+dp[0][nx][ny];
            }
        }
    }
    for(i=N-1;i>=1;i--){
        for(j=1;j<N;j++){
            if(sum(i,1,N-1,j)){
                int nx = max(i,c[j+1].S), ny = min(j,r[i-1].F);
                int tot = sum(i,1,N-1,j);
                dp[1][i][j]=tot+dp[1][nx][ny];
            }
        }
    }
    for(i=1;i<=M;i++){
        x=pos[i].F, y=pos[i].S;
        ll tmp = M-1+dp[0][x][y]+dp[1][x][y]-2;
        printf("%lld\n",tmp);
    }
    return 0;
}
