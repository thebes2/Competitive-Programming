#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
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
typedef pair<int,vi> piv;

#define pb push_back
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)

const int MN = 3003;
string s, t;
int n, m, i, j, pre[MN], suf[MN], st[MN], lim1, lim2, ans, sw, fl, k, f[MN];
pii sna;

void solve(){
    k = lim2;
    for(int i=2,j=1;i<=k;i++){
        while(j&&t[m-i]!=t[m-j]) j=f[j-1];
        f[i]=j++;
    }
    f[0]=-1;
    int ln = 0;
    for(int i=n;i>=1;i--){
        while(ln>=0&&(ln>k||t[m-ln-1]!=s[i-1])) ln=f[ln];
        suf[i]=++ln;
        ln=min(ln,k);
        st[i]=max(0,k-suf[i]);
    }
    k = lim1;
    for(int i=2,j=1;i<=k;i++){
        while(j&&t[i-1]!=t[j-1]) j=f[j-1];
        f[i]=j++;
    }
    ln = 0;
    for(int i=1;i<=n;i++){
        while(ln>=0&&(ln>k||t[ln]!=s[i-1])) ln=f[ln];
        pre[i]=++ln;
        ln=min(ln,k);
        if(pre[i]+suf[i+1]>ans){
            ans = pre[i]+suf[i+1];
            if(sw) sna = {n-(i+suf[i+1]), st[i+1]};
            else sna = {i-pre[i], st[i+1]};
        }
    }
}

int main(){
    cin >> s >> t;
    n = s.size(), m = t.size();
    lim1 = 0; lim2 = m;
    solve();
    for(int i=1;i<=m;i++){
        lim1++; lim2--;
        char ch = t.back(); t.erase(t.end()-1);
        t.insert(t.begin(),ch);
        solve();
    }
    reverse(s.begin(),s.end());
    lim1 = 0; lim2 = m; sw = 1;
    solve();
    for(int i=1;i<=m;i++){
        lim1++; lim2--;
        char ch = t.back(); t.erase(t.end()-1);
        t.insert(t.begin(),ch);
        solve();
    }
    printf("%d\n%d %d\n",ans,sna.first,sna.second);
    return 0;
}
