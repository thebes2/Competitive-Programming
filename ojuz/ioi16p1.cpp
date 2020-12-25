#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define pb push_back

vi find_subset(int l, int r, vi w){
	vector<pii> a;
	for(int i=0;i<w.size();i++)
		a.pb({w[i], i});
	sort(a.begin(),a.end());
	ll sm = 0;
	vi ans;
	for(int i=0,j=0;i<a.size();i++){
		sm += a[i].first;
		while(sm>r) sm -= a[j++].first;
		if(sm>=l){
			for(int k=j;k<=i;k++)
				ans.pb(a[k].second);
			return ans;
		}
	}
	return ans;
}