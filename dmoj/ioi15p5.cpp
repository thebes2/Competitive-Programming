#include <bits/stdc++.h>
using namespace std;

const int MN = 200005;
int arr[MN], pos[MN], sw[MN], p[MN], n;

bool check(int v, int*x, int*y, int*a1, int *a2, bool ans){
	int i, l=0, nxt=0;
	for(i=v-1;i>=0;i--){
		swap(sw[p[x[i]]], sw[p[y[i]]]);
		swap(p[x[i]], p[y[i]]);
	}
	for(i=0;i<v;i++,l++){
		swap(pos[arr[x[i]]],pos[arr[y[i]]]);
		swap(sw[p[x[i]]], sw[p[y[i]]]);
		swap(p[x[i]],p[y[i]]);
		swap(arr[x[i]],arr[y[i]]);
		while(pos[l]==sw[l]&&l<n) l++;
		if(l >= n) return 1;
		if(ans){a1[nxt]=pos[l]; a2[nxt]=sw[l]; nxt++;}
		swap(arr[pos[l]],arr[sw[l]]);
		swap(pos[l],pos[arr[pos[l]]]);
	}
	while(pos[l]==sw[l]&&l<n) l++;
	return (l>=n);
}

int findSwapPairs(int N, int* S, int M, int* X, int* Y, int* P, int* Q){
	bool s = true; n=N;
	for(int i=0;i<N;i++)
		s = min(s, (S[i]==i));
	if(s) return 0;
	int lo = 1, hi = M;
	while(lo != hi){
		for(int i=0;i<N;i++){
			arr[i] = S[i];
			pos[S[i]] = sw[i] = p[i] = i;
		}
		int mid = (lo+hi)/2;
		if(check(mid,X,Y,P,Q,0)) hi = mid;
		else lo = mid+1;
	}
	for(int i=0;i<N;i++){
		arr[i] = S[i];
		pos[S[i]] = sw[i] = p[i] = i;
	}
	for(int i=0;i<M;i++)
		P[i] = Q[i] = 0;
	check(lo,X,Y,P,Q,1);
	return lo;
}
