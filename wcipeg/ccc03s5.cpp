#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct set
{
	int lead;
}tmp;

struct edge
{
	int s,e,weight;
}temp;

vector<set> a;
vector<edge> graph;
vector<int> dest;

bool comp(edge i, edge j){return(i.weight>j.weight);}

int leader(int n)
{
	if(n!=a[n].lead)
		a[n].lead = leader(a[n].lead);
	return a[n].lead;
}

bool Match(int c)
{
	for(int i=0;i<dest.size();i++)
	{
		if(leader(dest[i])!=c)
			return 0;
	}
	return 1;
}

int main()
{
	int n,m,c,i,d,s,e,w,MIN=10000000;
	scanf("%d%d%d",&n,&m,&d);
	for(i=0;i<n;i++)
	{
		tmp.lead = i;
		a.push_back(tmp);
	}
	for(i=0;i<m;i++)
	{
		scanf("%d%d%d",&s,&e,&w);
	    temp.s = s-1;
		temp.e = e-1;
		temp.weight = w;
		graph.push_back(temp);
	}
	for(i=0;i<d;i++)
	{
		scanf("%d",&s);
		dest.push_back(s-1);
	}
	sort(graph.begin(),graph.end(),comp);
	for(i=0;i<graph.size();i++)
	{
		if(leader(graph[i].e)!=leader(graph[i].s))
		{
			a[leader(graph[i].s)].lead = a[graph[i].e].lead;
			if(graph[i].weight<MIN)
				MIN = graph[i].weight;
		}
		if(Match(leader(0)))
			break;
	}
	printf("%d\n",MIN);
	return 0;
}
