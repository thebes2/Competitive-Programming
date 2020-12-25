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

const int MN = 444, mod = 1e9+9;
int N, M, i, x, y, nxt, par[2*MN*MN], ok[2*MN*MN], lst, f, dn, st[2*MN*MN], mt[MN];
vi go; vector<pii> adj[2*MN*MN];
string s[MN], t, ans[MN];
unordered_map<string,int> mp;
map<int,string> rev;

void rec(int n,int d){
    if(d==M){
        if(!mp.count(t)){
            mp[t]=++nxt;
            rev[nxt]=t;
        }
        adj[n].pb({mp[t],1});
        adj[mp[t]].pb({n,0});
    }
    else{
        if(s[n][d]=='X'||s[n][d]=='?'){
            t += 'X';
            rec(n,d+1);
            t.pop_back();
        }
        if(s[n][d]=='.'||s[n][d]=='?'){
            t += '.';
            rec(n,d+1);
            t.pop_back();
        }
    }
}

void dfs(int n,int pre){
    if(n<=N) pre = n;
    st[n] = pre;
    if(n>N&&!ok[n]){
        lst = n; dn = 1;
        return;
    }
    for(auto v : adj[n]){
        if(v.second&&par[v.first]==-1){
            par[v.first]=n;
            dfs(v.first, pre);
            if(dn) return;
        }
    }
}

unordered_set<string> sna;

bool gen(int n,int d){
    if(d==M){
        if(sna.find(t)==sna.end()){
            sna.insert(t);
            return 1;
        }
        return 0;
    }
    else{
        if(s[n][d]=='X'||s[n][d]=='?'){
            t += 'X';
            if(gen(n,d+1)) return 1;
            t.pop_back();
        }
        if(s[n][d]=='.'||s[n][d]=='?'){
            t += '.';
            if(gen(n,d+1)) return 1;
            t.pop_back();
        }
        return 0;
    }
}

int main(){
    for(scanf("%d%d",&N,&M),i=1;i<=N;i++){
        cin >> s[i];
        assert(s[i].size()==M);
        int cnt = 0;
        for(char c : s[i]) if(c=='?') cnt++;
        if(cnt>=20||(1<<cnt)>N) continue;
        go.pb(i); mt[i]=1;
    }
    nxt = N;
    for(auto v : go) rec(v, 0);
    for(auto v : go){
        memset(par,-1,sizeof(par));
        dn = 0; par[v] = 0; dfs(v, v);
        if(!dn){
            printf("NO\n");
            return 0;
        }
        int cur = lst;
        while(par[cur]!=0){
            if(cur>N) ok[cur]=st[cur];
            int pre = par[cur];
            for(int i=0;i<adj[pre].size();i++){
                if(adj[pre][i].first==cur){
                    adj[pre][i].second = !adj[pre][i].second;
                    break;
                }
            }
            for(int i=0;i<adj[cur].size();i++){
                if(adj[cur][i].first==pre){
                    adj[cur][i].second = !adj[cur][i].second;
                    break;
                }
            }
            cur = pre;
        }
    }
    printf("YES\n");
    for(i=N+1;i<=nxt;i++){
        if(ok[i]){
            ans[ok[i]]=rev[i];
        }
    }
    for(i=1;i<=N;i++){
        if(mt[i]) sna.insert(ans[i]);
    }
    for(i=1;i<=N;i++){
        if(!mt[i]){
            t.clear(); gen(i,0);
            ans[i] = t;
        }
    }
    for(i=1;i<=N;i++){
        printf("%s\n",ans[i].c_str());
    }
    return 0;
}