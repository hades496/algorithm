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
#define double char
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 205;
int edge[N],point[N],nextc[N],n,e,f[N][N],ans,m,d[N],Left[N],Right[N],treeSize[N];
bool has_triv[N];
void link(int a,int b)
{
    point[++e]=b; nextc[e]=edge[a]; edge[a]=e;
    point[++e]=a; nextc[e]=edge[b]; edge[b]=e;
}
int mult2bin(int i)
{
    int j,k,max1=-1,max2=-1,res=1,t;
    has_triv[i]=1;
    for(j=edge[i];j;j=nextc[j])
    {
        k=point[j];
        if(!has_triv[k])
        {
            if(Left[i]==-1)
                Left[i]=k;
            if(nextc[j]&&!has_triv[point[nextc[j]]])
                Right[k]=point[nextc[j]];
            res+=mult2bin(k);
        }
    }
    return treeSize[i]=res;
}

int dp(int i,int m)
{
    int res=0,t;
    if(m<=0||i<0) return 0;
    if(f[i][m]!=-1) return f[i][m];
    for(t=0;t<=m;t++)
    {
        res=max(res,dp(Left[i],t)+dp(Right[i],m-t));
        if(t<m) res=max(res,dp(Left[i],t)+dp(Right[i],m-t-1)+d[i]);
    }
    printf("f[%d][%d]=%d\n",i,m,res);
    return f[i][m]=res;
}

void init()
{
    int i,a,b;
    ans = e = 0;
    mem(edge);mem(f);mem(nextc);mem(has_triv);
    for(i=1;i<=n;i++)
        scanf("%d",&d[i]);
    for(i=1;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        link(a,b);
    }
    memset(Left,-1,sizeof(Left));
    memset(Right,-1,sizeof(Right));
    memset(f,-1,sizeof(f));

}


void work()
{
    int i,j,k;
    mult2bin(1);
    for(i=1;i<=n;i++)
        printf("treeSize[%d]=%d\n",i,treeSize[i]);
    printf("%d\n",dp(1,m));
}


void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
    //int t;
    //scanf("%d\n",&t);
    //while(t--)
    while(cin >> n >>m)
    {
        if(n==0) return 0;
        init();
        work();
    }
    return 0;
}
