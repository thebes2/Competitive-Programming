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

const int MN = 505, MM = 5005;
bitset<MN> ok[MN], hm[MN], tmp[MN];
int R, C, M, i, j, ans, dx[]={-1,1,0,0}, dy[]={0,0,-1,1};
string s;

int main(){
    scanf("%d%d%d",&R,&C,&M);
    for(i=1;i<=R;i++){
        for(getchar(),j=1;j<=C;j++){
            char ch = getchar();
            if(ch=='.') ok[i][j]=1, hm[i][j]=1;
        }
    }
    cin >> s;
    for(char c : s){
        for(i=1;i<=R;i++) tmp[i]=ok[i],ok[i].reset();
        if(c=='W'||c=='?'){
            for(i=1;i<=R;i++) ok[i]|=(hm[i]&(tmp[i]>>1));
        }
        if(c=='E'||c=='?'){
            for(i=1;i<=R;i++) ok[i]|=(hm[i]&(tmp[i]<<1));
        }
        if(c=='N'||c=='?'){
            for(i=1;i<=R;i++) ok[i]|=(hm[i]&tmp[i+1]);
        }
        if(c=='S'||c=='?'){
            for(i=1;i<=R;i++) ok[i]|=(hm[i]&tmp[i-1]);
        }
    }
    for(i=1;i<=R;i++) ans+=ok[i].count();
    printf("%d\n",ans);
    return 0;
}