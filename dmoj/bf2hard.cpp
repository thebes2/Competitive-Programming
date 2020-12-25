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
#define eb emplace_back
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second

const int MN = 1e6+6;
int N; string s;

struct SuffixAutomaton{
    struct nd{
        map<char,int> nxt;
        int len, link, cnt; char ch;
    }a[2*MN];
    int lst, nxt, st;
    inline void init(){lst=nxt=st=0;a[0].nxt.clear();a[0].link=-1;}
    inline void extend(char ch){
        int cur = ++nxt;
        a[cur].len = a[lst].len+1;
        a[cur].cnt = ++st;
        a[cur].ch = ch;
        while(~lst&&!a[lst].nxt.count(ch)){
            a[lst].nxt[ch] = cur;
            lst = a[lst].link;
        }
        if(~lst){
            int ot = a[lst].nxt[ch];
            if(a[ot].len!=a[lst].len+1){
                int split = ++nxt;
                a[split].len = a[lst].len+1;
                a[split].link = a[ot].link;
                a[split].nxt = a[ot].nxt;
                a[split].ch = a[ot].ch;
                a[ot].link = split;
                while(~lst&&a[lst].nxt.count(ch)&&a[lst].nxt[ch]==ot){
                    a[lst].nxt[ch] = split;
                    lst = a[lst].link;
                }
                ot = split;
            }
            a[cur].link = ot;
        }
        else a[cur].link = 0;
        lst = cur;
    }
    vector<pic> adj[2*MN];
    void dfs(int n,vi &sfa){
        if(a[n].cnt) sfa.pb(a[n].cnt);
        pr(">",n,a[n].cnt,adj[n]);
        sort(adj[n].begin(),adj[n].end(),[](pic i,pic j){return i.S<j.S;});
        for(auto v : adj[n])
            dfs(v.F, sfa);
    }
    inline vi sfa(string s){
        reverse(s.begin(),s.end());
        init();
        for(char c : s)
            extend(c);
        for(int i=1;i<=nxt;i++){
            pr(">",i,a[i].link);
            adj[a[i].link].eb(i,a[i].ch);
        }
        vi sfa;
        dfs(0, sfa);
        for(auto &v : sfa)
            v = s.size()+1-v;
        return sfa;
    }
}sa;

int main(){
    cin >> s >> N;
    sa.init();
    vi sfa = sa.sfa(s);
    pr(">",sfa);
    for(auto v : sfa){
        if(v+N-1<=s.size()){
            printf("%s\n",s.substr(v-1,N).c_str());
            return 0;
        }
    }
}