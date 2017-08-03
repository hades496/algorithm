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
const int N = 1000005;
const int M = 1000005;
int n,m;
int f[N], s[N], q[N], a[N], b[N], c[N];
int aa;char ch;inline int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}

void init()
{
    int i;
    for(i=1;i<=m;i++)
    {
        a[i]=F();b[i]=F();c[i]=F();s[i]=i;
    }
}

int cmp(int a,int b)
{
    return c[a]<c[b];
}

int found(int x)
{
    if(f[x]>0) return f[x]=found(f[x]);
    else return x;
}

int kruskal()
{
    int res=0;
    int i,j,ran=1,x,y;
    sort(s+1,s+1+m,cmp);
    memset(f,-1,sizeof(f));
    for(j=1,i=s[j];i<=m;i=s[++j])
    {
        x=found(a[i]);
        y=found(b[i]);
        if(x!=y)
        {
            f[x]=y;
            res+=c[i];
            ran++;
        }
        if(ran==n) break;
    }
    return res;
}


void work()
{
    printf("%d\n",kruskal());
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
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
