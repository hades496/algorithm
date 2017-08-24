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
const int N = 1005;
const int M = 100005;
int n,m,pathsize,start;
int ind[N],g[N][N];
bool inset[N];

int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}


void init()
{
    int i,a,b;
    mem(ind); mem(g);
    for(i=1;i<=m;i++)
    {
        a=F();b=F();
        g[a][b]++;
        g[b][a]++;
        ind[b]++;
        ind[a]++;
    }
}


bool eular_judge()
{
    int i,tot=0;
    start=1;
    for(i=1;i<=n;i++)
    {
        if(ind[i]&1)
        {
            tot++;
            start=i;
        }
        if(tot>2) return 0;
    }
    return 1;
}

void eular_path(int i)
{
    int j,k,l;
    for(j=1;j<=n;j++)
        if(g[i][j])
        {
            g[i][j]--;
            g[j][i]--;
            eular_path(j);
        }
    printf("%d ",i);
}

void work()
{
    eular_judge();
    eular_path(start);
    printf("\n");
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
