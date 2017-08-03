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
int n,m,color[N];
vector<int> nxt[N];
int aa;char ch;inline int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}
void init()
{
    int i,j,k;
    n=F(); m=F();
    mem1(color);
    mem(nxt);
    for(i=1;i<=m;i++)
    {
        j=F(); k=F();
        nxt[j].pb(k);
        nxt[k].pb(j);
    }
}

bool coloring(int now,int col)
{
    if(color[now]!=-1) return color[now]==col;
    int j,k,flag=1;
    color[now]=col;
    for(j=nxt[now].size()-1;j>=0;j--)
    {
        k=nxt[now][j];
        flag&=coloring(k,col^1);
    }
    return flag;
}

void work()
{
    int ans=1;
    for(int i=1;i<=n;i++)
        if(color[i]==-1)
            ans&=coloring(i,0);
    if(ans)
        printf("Correct\n");
    else
        printf("Wrong\n");
}

void prep()
{
}

int main()
{
    freopen("input.txt","r",stdin);
    prep();
    int t;
    scanf("%d",&t);
    while(t--)
//    while(scanf("%d%d",&n)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
