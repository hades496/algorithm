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
const int N = 200005;
const int M = 1000005;
int n,m,s,t,e;
int point[M],edge[N],nextc[M],cost[M],dis[N];
bool inset[N];
int q[N];
int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}

struct cmp1 {
    bool operator()(const int &i, const int &j) const {
        return cost[i] > cost[j];
    }
};

int prim()
{
    priority_queue<int, vector<int>, cmp1> q;
    int tot,i,j,s=1,t,res=0;
    inset[s]=1;
    for(tot=n-1;tot;tot--)
    {
        for(j=edge[s];j;j=nextc[j])
            q.push(j);
        while(!q.empty()&&inset[point[j=q.top()]])
            q.pop();
        if(q.empty()) break;
        s=point[q.top()];
        inset[s]=1;
        res+=cost[q.top()];
    }
    return tot?-1:res;
}

inline void link(int a,int b,int c)
{
    point[++e]=b; nextc[e]=edge[a]; edge[a]=e; cost[e]=c;
}

void init()
{
    int i,j,k,a,b,c;
    mem(edge); mem(nextc);e=0; mem(inset);
    for(i=1;i<=m;i++)
    {
        a=F();b=F();c=F();
        link(a,b,c);
        link(b,a,c);
    }
}

void work()
{
    printf("%d\n",prim());
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
    while(cin >> n >> m)
    {
        init();
        work();
    }
    return 0;
}
