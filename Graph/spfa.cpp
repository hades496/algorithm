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
const int M = 1000005;
int n,m,s,t,e;
int point[M],edge[N],nextc[M],cost[M],dis[N];
bool inset[N];

int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}

int spfa(int s = 1,int t = n)
{
    int i,j,k,a,b;
    queue<int> q; mem(inset);
    for(i=1;i<=n;i++) dis[i]=0x7fffffff;
    inset[s]=1; dis[s]=0; q.push(s);
    while(!q.empty())
    {
        i=q.front();
        q.pop();
        for(j=edge[i];j;j=nextc[j])
        {
            k=point[j];
            if(dis[i]+cost[j]<dis[k])
            {
                dis[k]=dis[i]+cost[j];
                if(!inset[k])
                {
                    inset[k]=1;
                    q.push(k);
                }
            }
        }
        inset[i]=0;
    }
    return dis[t];
}

inline void link(int a,int b,int c)
{
    point[++e]=b; nextc[e]=edge[a]; edge[a]=e; cost[e]=c;
}

void init()
{
    int i,a,b,c;
    mem(edge); mem(nextc);e=0;
    for(i=1;i<=m;i++)
    {
        a=F();b=F();c=F();
        link(a,b,c);
        link(b,a,c);
    }
}

void work()
{
    printf("%d\n",spfa(s,t));
}

void prep()
{
}

int main()
{
    freopen("input.txt","r",stdin);
    //prep();
//    int t;
//    scanf("%d",&t);
//    while(t--)
    while(cin >> n >> m >> s >> t)
    {
        init();
        work();
    }
    return 0;
}
