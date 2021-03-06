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
#define mem1(f) memset(f,-1,sizeof(f))
#define P2 pair<LL,LL>
#define pb(x) push_back(x)
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 100005;
int n,m,inset[N],patch[N];
vector<int> nxt[N];
int aa;char ch;inline int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}
void init()
{
    int i,j,k;
    mem1(patch);
    mem(nxt);
    for(i=1;i<=m;i++)
    {
        j=F(); k=F();
        nxt[j].pb(k);
        nxt[k].pb(j);
    }
}

int findPath(int i)
{
    int j,k;
    for(j=nxt[i].size()-1;j>=0;j--)
    {
        k=nxt[i][j];
        if(inset[k]==0)
        {
            inset[k]=1;
            if(patch[k]<0||findPath(patch[k]))
            {
                patch[k]=i;
                return 1;
            }
        }
    }
    return 0;
}

void work()
{
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        mem(inset);
        ans+=findPath(i);
    }
    printf("%d\n",ans/2);
}

void prep()
{
}

int main()
{
    freopen("input.txt","r",stdin);
//    prep();
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
