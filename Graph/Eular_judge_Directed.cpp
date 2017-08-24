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
int n,m,s,t,e,pathsize;
int point[M],edge[N],nextc[M],path[N],ind[N],oud[N];
bool inset[N],has[M];

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
    mem(edge); mem(nextc); mem(ind); mem(oud); mem(inset); e=0;
    n--;
    for(i=0;i<(1<<n);i++)
    {
        a=i; b=(i>>1);
        link(a,b); link(a,b|(1<<(n-1)));
        ind[b]++; ind[b|(1<<(n-1))]++;
        oud[a]++; oud[a]++;
    }
}

void eular_path(int i)
{
    int j,k,l;
    for(j=edge[i];j;j=nextc[j])
    {
        if(has[j]) continue;
        has[j]=1;
        k=point[j];
        eular_path(k);
    }
    path[pathsize++]=i;
}

void work()
{
    mem(path); pathsize=0; mem(has);
    int start=0;
    for(int i=0;i<(1<<n);i++)
        if(oud[i]&1) start=i;
    eular_path(start);
    for(int i=pathsize-1;i>0;i--)
        if((path[i]>>1)==path[i-1])
            printf("0");
        else
            printf("1");
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
    while(cin >> n)
    {
        init();
        work();
    }
    return 0;
}
