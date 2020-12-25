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

const int MN = 5e5+5;
map<int,int> st[3*MN];
int N, Q, i, x, y, arr[MN];

void build(int i,int s,int e){
    if(s!=e){
        build(2*i,s,(s+e)/2);
        build(2*i+1,(s+e)/2+1,e);
        st[i][0]=e-s+1;
    }
    else st[i][0]=1;
}

inline void dec(int i,int v){
    st[i][v] --;
    if(!st[i][v]) st[i].erase(v);
}

void upd(int i,int s,int e,int ind,int a,int b){
    if(s!=e){
        if((s+e)/2<ind) upd(2*i+1,(s+e)/2+1,e,ind,a,b);
        else upd(2*i,s,(s+e)/2,ind,a,b);
        dec(i,a); st[i][b]++;
    }
    else dec(i,a), st[i][b]++;
}

int qu(int i,int s,int e,int ss,int se,int c){
    if(s>=ss&&e<=se) return st[i].count(c)?st[i][c]:0;
    else if((s+e)/2<ss) return qu(2*i+1,(s+e)/2+1,e,ss,se,c);
    else if((s+e)/2>=se) return qu(2*i,s,(s+e)/2,ss,se,c);
    else return qu(2*i,s,(s+e)/2,ss,se,c)+qu(2*i+1,(s+e)/2+1,e,ss,se,c);
}

int main(){
    scanf("%d%d",&N,&Q);
    build(1,1,N);
    for(;Q;Q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d",&x);
            upd(1,1,N,x,arr[x],arr[x]+1),arr[x]++;
        }
        else if(i==2){
            scanf("%d",&x);
            upd(1,1,N,x,arr[x],arr[x]-1),arr[x]--;
        }
        else{
            scanf("%d%d%d",&x,&y,&i);
            printf("%d\n",qu(1,1,N,x,y,i));
        }
    }
    return 0;
}
