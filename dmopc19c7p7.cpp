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

const int MN = 1e5+5, MS = 450;
const ld eps = 1e-9;
int N, Q, i, j, v, c, x; ll W; ld slop, inte;
vector<vector<pll>> bkt, hull;
inline ll cp(pll a,pll b){return 1LL*a.F*b.S-1LL*a.S*b.F;}
inline bool cp(pll a,pll b,pll o){return 1LL*(a.F-o.F)*(b.S-o.S)-1LL*(a.S-o.S)*(b.F-o.F)>0;}

inline void upd_hull(int id,pll p){
    if(hull[id].empty()) hull[id].pb(p);
    else{
        int pos=lower_bound(hull[id].begin(),hull[id].end(),p)-hull[id].begin();
        if(pos!=hull[id].size()&&pos!=0&&!cp(p,hull[id][pos],hull[id][pos-1])) return;
        if(hull[id][pos].F==p.F){
            pr(">>> SUS");
            if(p.S<hull[id][pos].S) hull[id].erase(hull[id].begin()+pos),pos--;
            else return;
        }
        while(pos+1<hull[id].size()&&!cp(hull[id][pos],hull[id][pos+1],p))
            hull[id].erase(hull[id].begin()+pos);
        while(pos-1>0&&!cp(hull[id][pos-1],p,hull[id][pos-2]))
            hull[id].erase(hull[id].begin()+pos-1),pos--;
        hull[id].insert(hull[id].begin()+pos,p);
    }
}

inline void reblock(int id){
    bkt.insert(bkt.begin()+id,vector<pll>());
    hull.insert(hull.begin()+id,vector<pll>());
    for(int i=0;i<MS;i++){
        bkt[id].pb(bkt[id+1][i]);
        upd_hull(id,bkt[id+1][i]);
    }
    hull[id+1].clear();
    bkt[id+1].erase(bkt[id+1].begin(),bkt[id+1].begin()+MS);
    for(auto v : bkt[id+1])
        upd_hull(id+1,v);
}

inline ld sl(pll i,pll j){return (ld)(j.S-i.S)/(ld)(j.F-i.F);}

inline void ins(pll p){
    if(bkt.empty()){
        bkt.pb(vector<pll>()); hull.pb(vector<pll>());
        bkt[0].pb(p); hull[0].pb(p);
    }
    else{
        int lo, hi, mid;
        slop=(ld)p.S/(ld)p.F;
        inte=(ld)W/(ld)sqrt(1LL*p.F*p.F+1LL*p.S*p.S)/(ld)sqrt(1+slop*slop);
        for(int i=(int)bkt.size()-1;i>=0;i--){
            lo=0, hi=(int)hull[i].size()-1;
            while(lo<hi){
                mid=(lo+hi)>>1;
                if(sl(hull[i][mid],hull[i][mid+1])-slop<0) lo=mid+1;
                else hi=mid;
            }
            int f=0;
            if(hull[i][lo].S-slop*hull[i][lo].F+eps<inte) f=1;
            if(lo+1<hull[i].size()&&hull[i][lo+1].S-slop*hull[i][lo+1].F+eps<inte) f=1;
            if(lo-1>=0&&hull[i][lo-1].S-slop*hull[i][lo-1].F+eps<inte) f=1;
            if(f){
                for(int j=(int)bkt[i].size()-1;j>=0;j--){
                    if(cp(p,bkt[i][j])<W){
                        bkt[i].insert(bkt[i].begin()+j+1,p);
                        upd_hull(i,p);
                        break;
                    }
                }
                if(bkt[i].size()>=2*MS) reblock(i);
                return;
            }
        }
        bkt[0].insert(bkt[0].begin(),p);
        upd_hull(0,p);
        if(bkt[0].size()>=2*MS) reblock(0);
    }
}

inline pll qu(int k){
    for(int i=0;i<(int)bkt.size();i++){
        if(k<=bkt[i].size()) return bkt[i][k-1];
        else k-=bkt[i].size();
    }
    assert(0);
}

int main(){
    scanf("%d%d%lld",&N,&Q,&W);
    for(i=1;i<=N;i++){
        scanf("%d%d",&v,&c);
        ins(make_pair(v,c));
    }
    string s;
    for(i=1;i<=Q;i++){
        cin >> s;
        if(s=="K-TH"){
            scanf("%d",&x);
            pll res=qu(x);
            printf("%lld %lld\n",res.F,res.S);
        }
        else if(s=="INSERT"){
            scanf("%d%d",&v,&c);
            ins(make_pair(v,c));
        }
    }
    return 0;
}
