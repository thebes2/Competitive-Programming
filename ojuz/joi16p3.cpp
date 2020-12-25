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

const int MN = 105, MM = 1001, mod = 1e9+7;
int N, L, arr[MN], dp[MN][MN][MM][3], i, j, k, l;
inline void add(int &x,int y){x+=y; while(x>=mod)x-=mod;}

int main(){
    scanf("%d%d",&N,&L);
    for(i=1;i<=N;i++)
        scanf("%d",&arr[i]);
    if(N==1){
        printf("1\n");
        return 0;
    }
    else if(N==2){
        printf("%d\n",abs(arr[1]-arr[2])<=L?2:0);
        return 0;
    }
    sort(arr+1,arr+N+1);
    arr[N+1]=100000;
    dp[1][0][0][0] = 1;
    for(i=1;i<=N;i++){
        int dif = arr[i+1]-arr[i];
        for(j=0;j<=i;j++){
            for(k=0;k<=L;k++){
                for(l=0;l<=2;l++){
                    if(!dp[i][j][k][l]&&j>=l) continue;
                    // add new cc
                    if(k+dif*(2*j-l+2)<=L) add(dp[i+1][j+1][k+dif*(2*j-l+2)][l],dp[i][j][k][l]);
                    // merge onto old cc
                    if(k+dif*(2*j-l)<=L&&2*j>=l) add(dp[i+1][j][k+dif*(2*j-l)][l],1LL*dp[i][j][k][l]*(2*j-l)%mod);
                    // merge two cc's 
                    // "bring the cc's out of the ether"
                    if(j>=2){
                        if(l==0&&k+dif*(2*j-l-2)<=L) add(dp[i+1][j-1][k+dif*(2*j-l-2)][l],1LL*dp[i][j][k][l]*j%mod*(j-1)%mod);
                        if(l==1&&k+dif*(2*j-l-2)<=L) add(dp[i+1][j-1][k+dif*(2*j-l-2)][l],1LL*dp[i][j][k][l]*(j-1)%mod*(j-1)%mod);
                        if(l==2&&k+dif*(2*j-l-2)<=L&&i!=N) add(dp[i+1][j-1][k+dif*(2*j-l-2)][l],1LL*dp[i][j][k][l]*(j-1)%mod*(j-2)%mod);
                        if(l==2&&k+dif*(2*j-l-2)<=L&&i==N) add(dp[i+1][j-1][k+dif*(2*j-l-2)][l],dp[i][j][k][l]);
                    }
                    // sketchy endpoint cancer 
                    if(l<2){
                        // either endpoint
                        int coef = 2-l;
                        // just add it
                        if(k+dif*(2*j-l+1)<=L) add(dp[i+1][j+1][k+dif*(2*j-l+1)][l+1],1LL*dp[i][j][k][l]*coef%mod);
                        // connects with some cc
                        if(j-l>0&&k+dif*(2*j-l-1)<=L) add(dp[i+1][j][k+dif*(2*j-l-1)][l+1],1LL*dp[i][j][k][l]*coef%mod*(j-l)%mod);
                        if(k+dif*(2*j-l-1)<=L&&i==N) add(dp[i+1][j][k+dif*(2*j-l-1)][l+1],dp[i][j][k][l]);
                    }
                }
            }
        }
    }
    int ans = 0;
    for(i=0;i<=L;i++){
        ans += dp[N+1][1][i][2]%mod;
        if(ans>=mod) ans-=mod;
    }
    printf("%d\n",ans);
    return 0;
}
