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
const int N = 15;
int n,m,g[1<<11][1<<11],q;
LL f[N][1<<11];
void init()
{
    if(n<m)swap(n,m);
}
/*
using:
11

*/
void dfs(int s1,int s2,int d)
{
    if(d>m) return;
    if(d==m) g[s1][s2]+=1;
    else
    {
        dfs(s1<<1,s2<<1|1,d+1);//不放
        dfs(s1<<2|3,s2<<2|3,d+2);//横放
        dfs(s1<<1|1,s2<<1,d+1);//竖放
    }
}


/*
using:
11

10
11
*/
void dfs1(int s1,int s2,bool b1,bool b2,int d)
{
    if(d>m) return;
    if(d==m)
    {
        if(!b1&&!b2)
            g[s1][s2]+=1;
        else return;
    }
    else
    {
        if(!b1&&!b2)
        {
            dfs1(s1<<1,s2<<1|1,0,0,d+1);
            dfs1(s1<<1,s2<<1|1,0,1,d+1);
            dfs1(s1<<1,s2<<1|1,1,0,d+1);
        }
        if(!b2)
        {
            dfs1(s1<<1|1-b1,s2<<1|1,0,1,d+1);
            dfs1(s1<<1|1-b1,s2<<1|1,1,1,d+1);
        }
        if(!b1)
            dfs1(s1<<1,s2<<1|b2,1,1,d+1);
        dfs1(s1<<1|1-b1,s2<<1|b2,0,0,d+1);
    }
}

void work()
{
    int i,j,k;
    mem(g);mem(f);
    dfs1(0,0,0,0,0);
    f[0][(1<<m)-1]=1;
    for(i=1;i<=n+1;i++)
        for(j=0;j<(1<<m);j++)
            for(k=0;k<(1<<m);k++)
                f[i][k]=(f[i][k]+g[j][k]*f[i-1][j]);
    cout <<f[n+1][0] <<endl;
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
    while(cin >> n >> m)
    {
        if(n==0) return 0;
        init();
        work();
    }
    return 0;
}
