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

const int MN = 5e5+5;
int N, M, K, i, x, y, vs[MN], dx[]={-1,-1,-1,0,0,1,1,1}, dy[]={-1,0,1,-1,1,-1,0,1};
map<pii,int> id; queue<int> q; pii pos[MN];

int main(){
    scanf("%d%d%d",&N,&M,&K);
    for(i=1;i<=K;i++){
        scanf("%d%d",&x,&y);
        pos[i]={x,y};
        id[{x,y}]=i;
        if(x==1||y==M){
            vs[i]=1;
            q.push(i);
        }
    }
    while(q.size()){
        x=q.front(); q.pop();
        pii cur = pos[x];
        for(i=0;i<8;i++){
            int nx=cur.F+dx[i],ny=cur.S+dy[i];
            if(id.count({nx,ny})){
                int ot = id[{nx,ny}];
                if(!vs[ot]){
                    vs[ot] = 1;
                    q.push(ot);
                }
            }
        }
    }
    for(i=1;i<=K;i++){
        if(vs[i]&&(pos[i].F==N||pos[i].S==1)){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}