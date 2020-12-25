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
#define fox(i,x,y) for(int i=(x);i<=(y);i++)
#define foxr(i,x,y) for(int i=(y);i>=(x);i--)
#define F first
#define S second

const int MN = 808, MM = 1e5+5;
int N, M, K, i, j, k, x, y, a[MN][MN], dx[]={-1,1,0,0}, dy[]={0,0,-1,1}, ds[MN*MN], vs[MN*MN], len[1<<4], sz[MN*MN], ans, cnt;
string s; char op[]={'N','S','W','E'}; set<char> ok;
queue<pii> q; vector<pii> *elem[MN*MN], *go[MN*MN];
stack<int> stk; bitset<MN*MN> st; int dep[MN*MN];

inline int id(int x,int y){return (x-1)*M+y;}
int fnd(int x){return ds[x]=x==ds[x]?x:fnd(ds[x]);}
inline bool flood(int x,int y,int cc){
    if(a[x][y]==0) return 0;
    int msk = 0;
    for(int i=0;i<4;i++){
        int nx=x+dx[i], ny=y+dy[i];
        if(nx<1||nx>N||ny<1||ny>M) continue;
        if(fnd(id(nx,ny))==cc) msk |= (1<<i);
    }
    return len[msk]>=a[x][y];
}

void augment(int cc){
    vs[cc] = 1;
    while(go[cc]->size()){
        pii v=go[cc]->back();
        go[cc]->pop_back();
        elem[fnd(cc)]->pb(v);
        for(int i=0;i<4;i++){
            int nx=v.F+dx[i], ny=v.S+dy[i];
            if(nx<1||nx>N||ny<1||ny>M) continue;
            if(fnd(id(nx,ny))!=fnd(cc)&&flood(nx,ny,fnd(cc))){
                if(st[fnd(id(nx,ny))]){
                    int anc = fnd(id(nx,ny));
                    while(stk.size()){
                        int x=stk.top(); stk.pop();
                        ds[x]=fnd(cc); st[x]=0;
                        if(elem[x]->size()>elem[fnd(cc)]->size())
                            swap(elem[x],elem[fnd(cc)]);
                        for(auto v : *elem[x])
                            go[cc]->pb(v);
                        elem[x]->clear();
                        if(x==anc) break;
                    }
                }
                else if(!vs[fnd(id(nx,ny))]){
                    int cur = fnd(cc);
                    stk.push(cur), st[cur]=1;
                    augment(fnd(id(nx,ny)));
                    if(stk.size()&&stk.top()==cur) stk.pop();
                    st[cur]=0;
                }
            }
        }
    }
}

int main(){
    //freopen("03-04.txt","r",stdin);
    cin >> K >> N >> M >> s;
    for(i=0;i<(1<<4);i++){
        int cur = 0;
        ok.clear();
        for(j=0;j<4;j++)
            if((1<<j)&i) ok.insert(op[j]);
        for(k=0;k<=2*K;k++){
            if(ok.count(s[k%K])) cur++;
            else len[i]=max(len[i],cur), cur=0;
        }
        len[i]=max(len[i],cur);
        if(len[i]>=2*K) len[i]=111111;
        //pr(">>>",i,len[i]);
    }
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]){
                ds[id(i,j)]=id(i,j);
                go[id(i,j)]=new vector<pii>();
                elem[id(i,j)]=new vector<pii>();
                go[id(i,j)]->pb({i,j});
            }
        }
    }
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            if(!vs[fnd(id(i,j))]&&a[i][j]) augment(id(i,j));
        }
    }
    ans = 1<<30;
    memset(vs,0,sizeof(vs));
    for(i=1;i<=N;i++){
        for(j=1;j<=M;j++){
            if(!a[i][j]) continue;
            int cur_id = fnd(id(i,j));
            if(!vs[cur_id]){
                vs[cur_id] = 1;
                int aug = 0;
                for(auto v : *elem[cur_id]){
                    for(k=0;k<4;k++){
                        int nx=v.F+dx[k], ny=v.S+dy[k];
                        if(nx<1||nx>N||ny<1||ny>M) continue;
                        if(fnd(id(nx,ny))!=cur_id&&flood(nx,ny,cur_id))
                            aug = 1;
                    }
                }
                if(!aug){
                    //if(elem[cur_id]->size()==28)pr(">",cur_id,elem[cur_id]->size());
                    if(elem[cur_id]->size()<ans)
                        ans = cnt = elem[cur_id]->size();
                    else if(elem[cur_id]->size()==ans)
                        cnt += elem[cur_id]->size();
                }
            }
        }
    }
    //pr(">>>>",count+zero,N*M);
    //assert(sm+zero==N*M);
    printf("%d\n%d\n",ans,cnt);
    return 0;
}