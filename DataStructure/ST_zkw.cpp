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
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 1<<20;
const int MAXINT = 0x7fffffff;
int n,a[N],d[2*N],ma=0,M;

void build()
{
    int t;
    for(M=1;M<=n;M<<=1);
    for(int i=1;i<=n;++i) scanf("%d",&t),d[i+M]=t;
    for(int i=n+1;i<M;++i) d[i+M]=MAXINT;
    for(int i=M-1;i>=1;i--) d[i]=min(d[i<<1],d[i<<1|1]);
}

void update(int x,int y)
{
    d[x=x+M]=y;
    while(x) d[x>>=1]=min(d[x<<1],d[x<<1|1]);
}
int query(int s,int t)
{
    int Ans=MAXINT;
    for (s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1){
        if(~s&1) Ans=min(Ans,d[s^1]);
        if( t&1) Ans=min(Ans,d[t^1]);
    }return Ans;
}

int init()
{
    build();
}

int work()
{
    int q,o,x,y;
    for(cin>>q;q--;)
    {
        scanf("%d%d%d",&o,&x,&y);
        if(o) update(x,y);
        else printf("%d\n",query(x,y));
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    while(cin >> n)
    {
        init();
        work();
    }
    return 0;
}
