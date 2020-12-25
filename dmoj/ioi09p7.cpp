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

const int MN = 2e5+5, MB = 2000, MM = 25e3+5;
int N, R, Q, i, j, x, y, arr[MN], cnt[MN], vis[MN][2], nxt, dep[MN], rev[MN], st[3*MN], lz[3*MN], stk[MN], tp; pii ans[100][MM];
vi vec[MN], adj[MN], big;
map<int,int> mp;

inline void upd_lz(int i,int s,int e){
    if(lz[i]){
        st[i]+=lz[i];
        if(s!=e) lz[2*i]+=lz[i],lz[2*i+1]+=lz[i];
        lz[i]=0;
    }
}

void upd(int i,int s,int e,int ss,int se,int val){
    upd_lz(i,s,e);
    if(s>=ss&&e<=se) lz[i]=val, upd_lz(i,s,e);
    else{
        if((s+e)/2<ss) upd(2*i+1,(s+e)/2+1,e,ss,se,val), upd_lz(2*i,s,(s+e)/2);
        else if((s+e)/2>=se) upd(2*i,s,(s+e)/2,ss,se,val), upd_lz(2*i+1,(s+e)/2+1,e);
        else upd(2*i+1,(s+e)/2+1,e,ss,se,val),upd(2*i,s,(s+e)/2,ss,se,val);
        st[i]=st[2*i]+st[2*i+1];
    }
}

int qu(int i,int s,int e,int ss,int se){
    upd_lz(i,s,e);
    if(s>=ss&&e<=se) return st[i];
    else if((s+e)/2<ss) return qu(2*i+1,(s+e)/2+1,e,ss,se);
    else if((s+e)/2>=se) return qu(2*i,s,(s+e)/2,ss,se);
    else return qu(2*i,s,(s+e)/2,ss,se)+qu(2*i+1,(s+e)/2+1,e,ss,se);
}

void dfs(int n,int d){
    dep[n]=d; vis[n][0]=++nxt;
    rev[nxt] = n;
    for(auto v : adj[n])
        dfs(v, d+1);
    vis[n][1] = nxt;
}

int main(){
    scanf("%d%d%d%d",&N,&R,&Q,&arr[1]);
    for(i=2;i<=N;i++){
        scanf("%d%d",&x,&arr[i]);
        adj[x].pb(i);
    }
    for(i=1;i<=N;i++){
        cnt[arr[i]]++;
        vec[arr[i]].pb(i);
    }
    for(i=1;i<=R;i++){
        if(cnt[i]>MB) big.pb(i);
    }
    dfs(1, 0);
    for(i=1;i<=R;i++)
        sort(vec[i].begin(),vec[i].end(),[](int i,int j){return vis[i][0]<vis[j][0];});
    for(auto v : big){
        int idx = mp.size()+1;
        mp[v] = idx;
        for(auto u : vec[v])
            upd(1,1,N,vis[u][0],vis[u][1],1);
        for(i=1;i<=R;i++){
            if(i==v) continue;
            int res = 0;
            for(auto u : vec[i])
                res += qu(1,1,N,vis[u][0],vis[u][0]);
            ans[idx][i].F = res;
        }
        for(auto u : vec[v]){
            upd(1,1,N,vis[u][0],vis[u][1],-1);
            upd(1,1,N,vis[u][0],vis[u][0],1);
        }
        for(i=1;i<=R;i++){
            if(i==v) continue;
            int res = 0;
            for(auto u : vec[i])
                res += qu(1,1,N,vis[u][0],vis[u][1]);
            ans[idx][i].S = res;
        }
        for(auto u : vec[v])
            upd(1,1,N,vis[u][0],vis[u][0],-1);
    }
    while(Q--){
        scanf("%d%d",&x,&y);
        if(max(vec[y].size(),vec[x].size())>MB){
            if(vec[x].size()<vec[y].size()) printf("%d\n",ans[mp[y]][x].S);
            else printf("%d\n",ans[mp[x]][y].F);
        }
        else{
            tp = -1; int res=0;
            for(i=j=0;i<(int)vec[y].size();i++){
                while(j<(int)vec[x].size()&&vis[vec[x][j]][0]<vis[vec[y][i]][0]){
                    while(~tp){
                        if(vis[stk[tp]][1]<vis[vec[x][j]][0]) tp--;
                        else break;
                    }
                    stk[++tp]=vec[x][j];
                    j++;
                }
                while(~tp){
                    if(vis[stk[tp]][1]<vis[vec[y][i]][0]) tp--;
                    else break;
                }
                res += tp+1;
            }
            printf("%d\n",res);
        }
        fflush(stdout);
    }
    return 0;
}