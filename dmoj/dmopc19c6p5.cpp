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

const int MN = 1e5+5;
struct nd{ll t[4][4][3];}st[3*MN];
ll N, Q, i, j, k, w[MN], h[MN], hi[MN], lo[MN], mid[MN], ed[MN], ps[MN], l, r, a[4][3], b[4][3];
vector<pll> go[3];

int n0, n1, inc, stt, edd;
inline void stmin(ll &x,ll y){x=x<=y?x:y;}
void build(ll i,ll s,ll e){
    if(s!=e){
        build(2*i,s,(s+e)/2);
        build(2*i+1,(s+e)/2+1,e);
        for(n0=0;n0<3;n0++){
            for(n1=0;n1<3-n0;n1++){
                for(inc=0;inc<3-n0-n1;inc++){
                    for(auto v : go[inc]){
                        for(stt=0;stt<4;stt++){
                            for(edd=0;edd<4;edd++){
                                stmin(st[i].t[stt][edd][n0+n1+inc],st[2*i].t[stt][v.first][n0]+st[2*i+1].t[v.second][edd][n1]);
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        st[i].t[0][3][0]=0;
        st[i].t[1][2][0]=hi[s-1];
        st[i].t[2][1][0]=lo[s-1];
        st[i].t[0][0][0]=mid[s];
        st[i].t[3][0][0]=hi[s-1]+lo[s-1];
        st[i].t[1][1][0]=hi[s-1]+mid[s];
        st[i].t[2][2][0]=lo[s-1]+mid[s];
        st[i].t[3][3][0]=lo[s-1]+hi[s-1]+mid[s];
    }
}

void qu(ll i,ll s,ll e,ll ss,ll se){
    if(s>=ss&&e<=se){
        for(edd=0;edd<4;edd++){
            for(n1=0;n1<3;n1++)
                b[edd][n1]=1LL<<50;
        }
        for(n0=0;n0<3;n0++){
            for(n1=0;n1<3-n0;n1++){
                for(inc=0;inc<3-n0-n1;inc++){
                    for(auto v : go[inc]){
                        for(edd=0;edd<4;edd++){
                            stmin(b[edd][n0+n1+inc],a[v.first][n0]+st[i].t[v.second][edd][n1]);
                        }
                    }
                }
            }
        }
        swap(a,b);
    }
    else if((s+e)/2<ss) qu(2*i+1,(s+e)/2+1,e,ss,se);
    else if((s+e)/2>=se) qu(2*i,s,(s+e)/2,ss,se);
    else qu(2*i,s,(s+e)/2,ss,se),qu(2*i+1,(s+e)/2+1,e,ss,se);
}

void solve(){
    for(i=1;i<3*MN;i++){
        for(j=0;j<4;j++){
            for(k=0;k<4;k++){
                for(inc=0;inc<3;inc++)
                    st[i].t[j][k][inc]=1LL<<50;
            }
        }
    }
    memset(hi,0,sizeof(hi));
    memset(lo,0,sizeof(lo));
    memset(mid,0,sizeof(mid));
    memset(ed,0,sizeof(ed));
    for(i=0;i<3;i++) go[i].clear();
    scanf("%lld%lld",&N,&Q);
    for(i=1;i<=N;i++){
        scanf("%lld",&h[i]);
    }
    for(i=1;i<=N;i++){
        scanf("%lld",&w[i]);
    }
    h[0]=1LL<<50;
    for(i=1;i<=N;i++){
        ed[i]=2*w[i]+h[i];
        ps[i]=ps[i-1]+ed[i];
        ps[i]+=max(0LL,h[i]-h[i-1]);
        if(i!=N){
            mid[i]=min(h[i],h[i+1]);
            if(i+1!=N){
                lo[i]=w[i+1];
                hi[i]=w[i+1]+2*h[i+1]-min(h[i],h[i+1])-min(h[i+1],h[i+2]);
            }
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            int a1 = (i&1), a2 = (i&2);
            int b1 = (j&1), b2 = (j&2);
            int c = 0;
            if(a1^b1) c++;
            if(a2^b2) c++;
            go[c].pb({i,j});
        }
    }
    if(N>1) build(1,1,N-1);
    for(;Q;Q--){
        scanf("%lld%lld",&l,&r);
        if(l==r){
            printf("%lld\n",2*(w[l]+h[l]));
            continue;
        }
        else if(l+1==r){
            printf("%lld\n",ps[r]-ps[l-1]+min(h[l-1],h[l]));
            continue;
        }
        for(i=0;i<4;i++){
            for(j=0;j<3;j++)
                a[i][j]=1LL<<50;
        }
        a[0][0]=0;
        qu(1,1,N-1,l,r-1);
        ll ans = 1LL<<50;
        for(i=0;i<4;i++){
            int c=0;
            if(i&1) c++;
            if(i&2) c++;
            for(j=0;j<3-c;j++)
                stmin(ans,a[i][j]);
        }
        printf("%lld\n",ans+ps[r]-ps[l-1]+min(h[l-1],h[l]));
    }
}

int main(){
    /*int NUM_CASES[]={0, 10, 10, 10, 20, 20, 60};
    int sub = 1;
    for(int tc=1;tc<=NUM_CASES[sub];tc++){
        string in = "dmopc19c6p5\\"+to_string(sub)+"."+to_string(tc)+".in";
        string out = "dmopc19c6p5\\"+to_string(sub)+"."+to_string(tc)+".out";
        freopen(in.c_str(),"r",stdin);
        freopen(out.c_str(),"w",stdout);

        solve();
    }*/
    solve();
}