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
typedef tuple<int,int,int> t3;

#define pb push_back
#define mt make_tuple
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second

const int MN = 1e5+5;
int R, C, N, M, K, L, i, j, x, y; ll w, st[6*MN], lz[6*MN];
struct evt{int x, l, r; ll val;}arr[2*MN];
map<int,int> mp; ll ans = -1LL<<60;

inline void upd_lz(int i,int s,int e){
    if(lz[i]){
        st[i] += lz[i];
        if(s!=e){
            lz[2*i]+=lz[i];
            lz[2*i+1]+=lz[i];
        }
        lz[i]=0;
    }
}

void upd(int i,int s,int e,int ss,int se,ll val){
    upd_lz(i,s,e);
    if(s>=ss&&e<=se){
        lz[i]=val;
        upd_lz(i,s,e);
    }
    else{
        if((s+e)/2<ss) upd(2*i+1,(s+e)/2+1,e,ss,se,val), upd_lz(2*i,s,(s+e)/2);
        else if((s+e)/2>=se) upd(2*i,s,(s+e)/2,ss,se,val), upd_lz(2*i+1,(s+e)/2+1,e);
        else upd(2*i,s,(s+e)/2,ss,se,val), upd(2*i+1,(s+e)/2+1,e,ss,se,val);
        st[i]=max(st[2*i],st[2*i+1]);
    }
}

int main(){
    scanf("%d%d%d%d",&R,&C,&N,&M);
    for(scanf("%d",&K),i=1;i<=K;i++){
        scanf("%d%d%lld",&x,&y,&w);
        arr[2*i-1]={x,y,y+C-1,w};
        arr[2*i]={x+R,y,y+C-1,-w};
        mp[y]=mp[y+C]=1;
    }
    i=0;
    mp[C]=mp[M+1]=0;
    while(mp.size()&&mp.begin()->F<C) mp.erase(mp.begin()->F);
    while(mp.size()){
        auto it=mp.end(); it--;
        if(it->F>M+1) mp.erase(it);
        else break;
    }
    for(auto it=mp.begin();it!=mp.end();it++)
        it->second = ++i;
    L = mp.size()-1;
    sort(arr+1,arr+2*K+1,[](evt i,evt j){return i.x<j.x;});
    for(i=1;i<=2*K;i=j){
        for(j=i;j<=2*K&&arr[j].x==arr[i].x;j++){
            int a = max(arr[j].l, C);
            int l = mp[a];
            int b = min(arr[j].r+1, M+1);
            int r = mp.lower_bound(b)->S-1;
            upd(1,1,L,l,r,arr[j].val);
        }
        if(arr[i].x>=R&&arr[i].x<=N)
            ans = max(ans, st[1]);
    }
    printf("%lld\n",ans);
    return 0;
}
