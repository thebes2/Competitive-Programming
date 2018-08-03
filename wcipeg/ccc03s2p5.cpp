#include <iostream>
#include <bitset>
#include <queue>

using namespace std;

int len, sol, last, x;
bitset<65536> a; queue<unsigned short int> q, tmp;

int main(){
	for(;;len++){
		scanf("%d",&x);
		if(x==0 || sol == 65536) break;
		else x--;
		if(a[x]){
			if(len-last>sol) tmp = q;
			sol = max(sol,len-last);
			while(!q.empty()){
				last++;
				if(q.front()==x){a[q.front()].flip(); q.pop(); break;}
				else{a[q.front()].flip(); q.pop();}
			}
			q.push(x); a[x].flip();
		}
		else{
			a[x].flip(); q.push(x);
		}
	}
	if(len-last>sol) tmp=q;
	while(!tmp.empty()){
		printf("%hu\n",tmp.front()+1);
		tmp.pop();
	}
	return 0;
}
