#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#include<string>
#include<stack>
#include<set>
#define mem(f) memset(f,0,sizeof(f))
#define P2 pair<LL,LL>
#define pb(x) push_back(x)
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 100005;
const int M = 500005;
int n,m,s,t,e;
int point[M],edge[N],nextc[M],cost[M],dis[N],ind[N];
bool inset[N];

int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}

inline void link(int a,int b)
{
    point[++e]=b; nextc[e]=edge[a]; edge[a]=e;
}

void init()
{
    int i,a,b;
    mem(edge); mem(nextc); mem(ind); mem(inset); e=0;
    n=F(); m=F();
    for(i=1;i<=m;i++)
    {
        a=F();b=F();
        link(a,b);
        ind[b]++;
    }
}

int Topological_sort()
{
    int i,j,k,tot=0;
    queue <int > q;
    for(i=1;i<=n;i++)
        if(ind[i]==0)
        {
            q.push(i);
            inset[i]==1;
            tot++;
        }
    while(!q.empty())
    {
        i=q.front();
        q.pop();
        for(j=edge[i];j;j=nextc[j])
        {
            k=point[j];
            ind[k]--;
            if(ind[k]==0&&inset[k]==0)
            {
                tot++;
                q.push(k);
                inset[k]=1;
            }
        }
    }
    return tot==n;
}

void work()
{
    printf("%s\n",Topological_sort()?"Correct":"Wrong");
}

void prep()
{
}

int main()
{
    //freopen("input.txt","r",stdin);
    //prep();
    int t;
    scanf("%d",&t);
    while(t--)
//    while(cin >> n >> m)
    {
        init();
        work();
    }
    return 0;
}
