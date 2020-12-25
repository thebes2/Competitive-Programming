#include <bits/stdc++.h>
using namespace std;

const int MN = 3e4+4;
vector<int> id; unordered_map<string,int> t;
int bit[MN], lo, hi, N, Q, ans[MN], i, j, pos[MN], l, r;
struct qu{string s; int t, id;}q[MN];
string s[MN];

void upd(int p){for(;p<=N;p+=p&(-p))bit[p]++;}
int sum(int p){int r=0;for(;p>0;p-=p&(-p))r+=bit[p]; return r;}

int main(){
	for(scanf("%d",&N),i=1;i<=N;i++){
		cin >> s[i];
		t[s[i]] = i;
	}
	for(scanf("%d",&Q),i=1;i<=Q;i++){
		cin >> q[i].s; q[i].id = i;
		if(t.find(q[i].s)==t.end())
			q[i].t = 1<<30;
		else q[i].t = t[q[i].s];
	}
	sort(q+1, q+Q+1, [](qu i,qu j){return(i.t<j.t);});
	for(i=1;i<=N;i++) id.push_back(i);
	sort(id.begin(), id.end(), [](int i,int j){return(s[i]<s[j]);});
	for(i=0;i<id.size();i++) pos[id[i]]=i+1;
	id.insert(id.begin(),0);
	for(i=j=1;i<=Q;i++){
		if(q[i].t==1<<30) break;
		while(j<=q[i].t){
			upd(pos[j]);
			j++;
		}
		l = 1; r = N; int cnt=0;
		for(int k=0;k<q[i].s.size();k++){
			lo = l; hi = r;
			while(lo < hi){
				int m = (lo+hi)/2;
				if(s[id[m]].size()<k) lo=m+1;
				else if(s[id[m]][k]<q[i].s[k]) lo=m+1;
				else hi=m;
			}
			l = hi; hi = r;
			while(lo < hi){
				int m = (lo+hi)/2+1;
				if(s[id[m]].size()<k) hi=m-1;
				else if(s[id[m]][k]>q[i].s[k]) hi=m-1;
				else lo=m;
			}
			r = hi;
			cnt += sum(r)-sum(l-1);
		}
		ans[q[i].id] = cnt+q[i].t;
	}
	while(j<=N) upd(pos[j++]);
	for(;i<=Q;i++){
		l = 1; r = N; int cnt=0;
		for(int k=0;k<q[i].s.size();k++){
			lo = l; hi = r;
			while(lo < hi){
				int m = (lo+hi)/2;
				if(s[id[m]].size()<k) lo=m+1;
				else if(s[id[m]][k]<q[i].s[k]) lo=m+1;
				else hi=m;
			}
			l = hi; hi = r;
			while(lo < hi){
				int m = (lo+hi)/2+1;
				if(s[id[m]].size()<k) hi=m-1;
				else if(s[id[m]][k]>q[i].s[k]) hi=m-1;
				else lo=m;
			}
			r = hi;
			if(s[id[l]][k]!=q[i].s[k]||s[id[r]][k]!=q[i].s[k]) break;
			cnt += sum(r)-sum(l-1);
		}
		ans[q[i].id] = cnt+N;
	}
	for(i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
