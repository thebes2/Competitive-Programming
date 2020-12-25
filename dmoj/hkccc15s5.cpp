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
typedef pair<ld,ld> pdd;
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

#define double long double
const int MN = 1e5+5, LG = 22;
const ld PI = (ld)acos((ld)-1), eps = 1e-11;
int N, i, j, x, y, lst[MN]; double a, b;
pdd pos[MN], qu[MN];
vector<pdd> vec[3*MN], hull[LG];

inline double cp(pdd a,pdd b){return a.F*b.S-a.S*b.F;}
inline bool cp(pdd o,pdd a,pdd b){return cp({a.F-o.F,a.S-o.S},{b.F-o.F,b.S-o.S})<eps;}

void ins(int i,int s,int e,int ss,int se,pdd p){
    if(s>=ss&&e<=se) vec[i].pb(p);
    else if((s+e)/2<ss) ins(2*i+1,(s+e)/2+1,e,ss,se,p);
    else if((s+e)/2>=se) ins(2*i,s,(s+e)/2,ss,se,p);
    else ins(2*i,s,(s+e)/2,ss,se,p), ins(2*i+1,(s+e)/2+1,e,ss,se,p);
}

inline bool chk(vector<pdd> hull,pdd vec,pdd qur){
    if(hull.empty()) return 0;
    int lo=0, hi=(int)hull.size()-1;
    while(lo<hi){
        int mid=(lo+hi)>>1;
        pdd hvec(hull[mid+1].F-hull[mid].F,hull[mid+1].S-hull[mid].S);
        if(cp(vec,hvec)>eps) hi=mid;
        else lo=mid+1;
    }
    for(int i=-2;i<2;i++){
        if(i+lo>=0&&i+lo<(int)hull.size()){
             if(hull[lo+i].F*qur.F+hull[lo+i].S*qur.S<=1+eps) return 1;
        }
    }
    return 0;
}

void solve(int i,int s,int e,int dep){
    hull[dep].clear();
    sort(vec[i].begin(),vec[i].end(),[](pdd i,pdd j){return i.F<j.F;});
    for(auto v : vec[i]){
        while(hull[dep].size()>=2){
            int sz = hull[dep].size();
            if(cp(hull[dep][sz-2],hull[dep][sz-1],v)) hull[dep].pop_back();
            else break;
        }
        hull[dep].pb(v);
    }
    if(s==e){
        if(qu[s].F>0){
            double xint=1.0/qu[s].F, yint=1.0/qu[s].S;
            bool f=0;
            for(j=0;j<=dep;j++){
                if(chk(hull[j],{xint,-yint},qu[s])){
                    f = 1;
                    break;
                }
            }
            printf("%d\n",f?0:1);
        }
    }
    else{
        solve(2*i,s,(s+e)/2,dep+1);
        solve(2*i+1,(s+e)/2+1,e,dep+1);
    }
}

int main(){
    scanf("%d",&N);
    memset(lst,-1,sizeof(lst));
    for(i=1;i<=N;i++){
        scanf("%d",&j);
        if(!j){
            cin >> a >> b >> x;
            pos[x]={a, b};
            lst[x] = i;
        }
        else if(j==1){
            scanf("%d",&x);
            ins(1,1,N+1,lst[x],i,pos[x]);
            lst[x] = -1;
        }
        else{
            cin >> a >> b;
            qu[i]={a,b};
        }
    }
    for(i=0;i<MN;i++){
        if(~lst[i]){
            ins(1,1,N+1,lst[i],N+1,pos[i]);
        }
    }
    solve(1,1,N+1,0);
    return 0;
}