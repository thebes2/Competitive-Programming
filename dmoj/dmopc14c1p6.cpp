#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,ssse3,sse3,sse4,popcnt,avx,mmx,abm,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int MN = 200;
typedef long long ll;
int N, i, start, idx[5000000]; ll K; vector<vector<int>> v;
double mat[MN][MN], a[MN][MN], o[MN][MN];
vector<int> idfk(5);
int hsh(vector<int> vec){
	int k = 1, s = 0;
	for(int i=0;i<N;i++){
		s += vec[i]*k;
		k *= 6;
	}
	return s;
}
void rec(int d,int r){
	if(d == N && r == 0) v.push_back(idfk);
	else if(d != N){
		for(int i=0;i<r;i++)
			idfk[d]++, rec(d+1,r-i-1);
		idfk[d]=0; rec(d+1,r);
	}
}

void rec2(int n, vector<int> reee, int st, double wa){
	if(n == N){
		int wat = hsh(idfk);
		o[st][idx[wat]]+=wa;
	}
	else{
		for(int i=0;i<N;i++){
			idfk[reee[i]]++;
			rec2(n+1, reee, st, wa);
			idfk[reee[i]]--;
		}
	}
}
vector<int> msk;
void cpy(){
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size();j++)
			mat[i][j] = a[i][j];
	}
}
void mul(int b){
	memset(a, 0, sizeof(a));
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size();j++){
			for(int k=0;k<v.size();k++){
				if(mat[i][k]==1.0)  a[i][j]+=mat[k][j];
				else if(mat[k][j]==1.0) a[i][j]+=mat[i][k];
				else a[i][j] += mat[i][k]*mat[k][j];
			}
		}
	}
	cpy();
	if(!b) return;
	memset(a, 0, sizeof(a));
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v.size();j++){
			for(int k=0;k<v.size();k++){
				if(mat[i][k]==1.0) a[i][j]+=o[k][j];
				else if(o[k][j]==1.0) a[i][j]+=mat[i][k];
				else a[i][j] += mat[i][k]*o[k][j];
			}
		}
	}
	cpy();
}
vector<double> ans;
int main(){
	scanf("%d%lld",&N,&K);
	rec(0, N);
	for(int k=0;k<v.size();k++){
		idx[hsh(v[k])]=k;
	}
	for(int k=0;k<v.size();k++){
		auto e = v[k];
		int fnd = 0;
		for(int i=0;i<N;i++)
			if(e[i] != 1) fnd = 1;
		if(!fnd) start = k;
		vector<int> huh;
		for(i=0;i<e.size();i++){
			for(int j=0;j<e[i];j++)
				huh.push_back(i);
		}
		double tot = pow(N, N);
		rec2(0, huh, k, 1/tot);
	}
	if(N == 2) K = min(K, 100000000LL);
	else if(N == 3) K = min(K, 100000LL);
	else if(N == 4) K = min(K, 10000000LL);
	else if(N == 5) K = min(K, 1000LL);
	ll tmp = K;
	while(K){
		msk.insert(msk.begin(),K%2);
		K /= 2;
	}
	for(int i=0;i<v.size();i++){
		mat[i][i] = 1;
	}
	K = tmp;
	if(K){
		for(int i=0;i<msk.size();i++)
			mul(msk[i]);
	}
	for(int i=0;i<v.size();i++)
		ans.push_back(mat[start][i]);
	sort(ans.begin(),ans.end());
	for(auto v : ans)
		printf("%.10lf\n",v);
	getchar(); getchar();
}
