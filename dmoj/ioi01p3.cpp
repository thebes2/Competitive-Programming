#include <bits/stdc++.h>
#define FOR(i,a,b) for(i=a; i<=b; i++)
#define FOR2(i,n) FOR(i,0,n-1)
#define MAXN 25
using namespace std;
int __[6] , _[6] , ___[6];
int DP[600][6][6][6][6][6];
char A[MAXN];
bool used[MAXN];
int dp(int k,int a,int b,int c,int d,int e,int t)
{
	int &ret = DP[k][a][b][c][d][e];
	if(ret) return ret;
	if(used[t]) return ret = dp(k,a,b,c,d,e,t+1);
	ret = 0;
	if(a < 5 && t > __[0] && t > ___[a]) ret += dp(k,a+1,b,c,d,e,t+1);
	if(b < a && t > __[1] && t > ___[b]) ret += dp(k,a,b+1,c,d,e,t+1);
	if(c < b && t > __[2] && t > ___[c]) ret += dp(k,a,b,c+1,d,e,t+1);
	if(d < c && t > __[3] && t > ___[d]) ret += dp(k,a,b,c,d+1,e,t+1);
	if(e < d && t > __[4] && t > ___[e]) ret += dp(k,a,b,c,d,e+1,t+1);

	return ret;

}
void solve1()
{
	int i,j,res(0),s(0),t,x,y;
	scanf("%s",A);
	FOR2(i,25)
	{
		x = i/5; y = i%5;
		_[x]++;
		t = A[i] - 'A';
		FOR2(j,t)
			if(!used[j] && j > __[x] && j > ___[y])
			{
				__[x] = ___[y] = j;
				used[j] = true;
				DP[++s][5][5][5][5][5] = 1;
				res += dp(s,_[0],_[1],_[2],_[3],_[4],0);
				used[j] = false;
			}
		used[ t ] = true;
		__[x] = ___[y] = t;
	}
	printf("%d\n" , res + 1 );
}
void solve2()
{

	int T,i,j,s(0),t,x,y;
	scanf("%d",&T);
	FOR2(i,25)
	{
		x = i/5; y = i%5;
		_[x]++;
		FOR2(j,25)
			if(!used[j] && j > __[x] && j > ___[y])
			{
				used[j] = true;
				__[x] = ___[y] = j;

				DP[++s][5][5][5][5][5] = 1;
				t = dp(s,_[0],_[1],_[2],_[3],_[4],0);

				if(T <= t)
				{
					printf("%c",j + 'A');
					break;
				}
				T -= t;

				used[j] = false;
			}
	}
	printf("\n");
}
int main()
{
	memset( __ , -1 , sizeof __ );
	memset( ___ , -1 , sizeof ___ );
	char c;
	scanf("%c" , &c);
	if(c == 'W') solve1();
	else solve2();
	getchar(); getchar();
	return 0;
}
