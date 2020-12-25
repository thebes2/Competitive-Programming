#include <bits/stdc++.h>
using namespace std;

int dp[150][2505], x, nxt;
string s;

bool num(char c){
	return(c>='0'&&c<='9');
}

int opt(int id, int n){
	int lo=0, hi=n;
	while(lo<hi){
		int m = (lo+hi)/2;
		if((1+m)*(1+m)>=dp[id][n-m]) hi=m;
		else lo=m+1;
	}
	int ret = 0;
	for(int i=-1;i<=1;i++){
		if((!lo+i>=0)||(!lo+i<=n))
			ret=max(ret,min((1+lo+i)*(1+lo+i),dp[id][n-(lo+i)]));
	}
	return ret;
}

void rec(int l, int r){
	int id = ++nxt;
	while(s[r]==' ') r--;
	while(s[l]==' ') l++;
	if(num(s[l])&&num(s[r])){
		int n = atoi(s.substr(l,r-l+1).c_str());
		for(int i=0;i<=x;i++)
			dp[id][i] = i+n;
	}
	else{
		l++; r--;
		while(s[r]==' ') r--;
		while(s[l]==' ') l++;
		int cnt = 0, i=l;
		for(;!(s[i]==' '&&!cnt);i++){
			if(s[i]=='(') cnt++;
			else if(s[i]==')') cnt--;
		}
		int id1 = nxt+1, id2;
		rec(l,i); id2=nxt+1; rec(i,r);
		for(i=x;i>=0;i--)
			dp[id][i]=dp[id1][i];
		for(i=x;i>=0;i--){
			for(int j=0;j<=i;j++)
				dp[id][i]=max(dp[id][i],dp[id][i-j]+dp[id2][j]);
		}
	}
	if(id!=1){
		for(int i=x;i>=0;i--)
			dp[id][i]=opt(id,i);
	}
}

int main(){
	getline(cin,s); cin>>x;
	rec(0,s.size()-1);
	printf("%d\n",dp[1][x]);
	return 0;
}
