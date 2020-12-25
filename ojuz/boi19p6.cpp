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

const int MN = 505, MM = 7;
int N, K, C, arr[MN][MM], sc[MM][MN], i, j, dn;
set<vi> part, st, vis; vi id[MM][MN], cur, acc, tmp; set<int> use;
map<int,int,greater<int>> rnk[MM];
struct pq{bool operator()(const piv&i,const piv&j){return i.first<j.first;}};
priority_queue<piv,vector<piv>,pq> go;

void fill(int rem,int c){
    if(dn) return;
    if(!rem){
        vi hm;
        for(auto v : use) hm.pb(v);
        if(!st.count(hm)){
            st.insert(hm);
            C --;
            if(!C) dn = 1;
        }
    }
    else{
        for(int i=c-1;i>=1;i--){
            if(!use.count(i)){
                use.insert(i);
                fill(rem-1,i);
                use.erase(i);
                if(dn) return;
            }
        }
    }
}

void rec(int d){
    if(d==K){
        tmp = acc;
        sort(tmp.begin(),tmp.end());
        tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
        if(part.count(tmp)) return;
        part.insert(tmp);
        use.clear();
        for(auto v : tmp) 
            use.insert(v);
        fill(K-tmp.size(),N+1);
    }
    else{
        for(auto v : id[d+1][cur[d]]){
            acc.pb(v);
            rec(d+1);
            acc.pop_back();
            if(dn) return;
        }
    }
}

int main(){
    scanf("%d%d%d",&N,&K,&C);
    for(i=1;i<=N;i++){
        for(j=1;j<=K;j++){
            scanf("%d",&arr[i][j]);
            rnk[j][arr[i][j]]=0;
        }
    }
    for(i=1;i<=K;i++){
        j=0;
        for(auto it=rnk[i].begin();it!=rnk[i].end();it++) 
            it->second = ++j, sc[i][j] = it->first;
    }
    for(i=1;i<=N;i++){
        for(j=1;j<=K;j++){
            int r = rnk[j][arr[i][j]];
            id[j][r].pb(i);
        }
    }
    vi init; int sm;
    for(j=1;j<=K;j++)
        init.pb(1),sm+=sc[j][1];
    go.push({sm,init});
    vis.insert(init);
    while(go.size()){
        int s = go.top().first;
        cur = go.top().second; go.pop();
        rec(0);
        if(dn){
            int ans = 0;
            for(i=0;i<K;i++)
                ans += sc[i+1][cur[i]];
            printf("%d\n",ans);
            return 0;
        }
        for(i=0;i<K;i++){
            if(cur[i]+1<=rnk[i+1].size()){
                cur[i] ++;
                if(!vis.count(cur)){
                    vis.insert(cur);
                    go.push({s-sc[i+1][cur[i]-1]+sc[i+1][cur[i]],cur});
                }
                cur[i] --;
            }
        }
    }
}