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
int n,q,M;
LL S[N<<1],P[N<<1];

int init()
{
    int i,t;
    mem(S);mem(P);
    for(M=1;M<n+2;M<<=1);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&t);
        S[i+M]=t;
    }
    for(i=n;i;i--)S[i+M]=S[i+M]-S[i+M-1],P[i+M]=S[i+M]*i;
    for(i=M-1;i;i--) S[i]=S[i<<1]+S[i<<1|1],P[i]=P[i<<1]+P[i<<1|1];
}

inline void updata(int s,int t,LL x)
{
    for(int u=s+M;u^1;u>>=1) S[u]+=x,P[u]+=x*s;
    for(int u=t+M+1;u^1;u>>=1) S[u]-=x,P[u]-=x*(t+1);
}

inline LL prefix(int t)
{
    LL res = 0;
    for(int u=t+M+1;u^1;u>>=1)
        if(u&1) res+=S[u^1]*(t+1)-P[u^1];
    return res;
}

int work()
{
    while(q--)
    {
        int a,b,c;
        char o = ' ';
        while(o!='Q'&&o!='C') scanf("%c",&o);
        if(o=='Q')
        {
            scanf("%d%d",&a,&b);
            printf("%lld\n",prefix(b)-prefix(a-1));
        }
        else
        {
            scanf("%d%d%d",&a,&b,&c);
            updata(a,b,c);
        }
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    while(cin >> n >> q)
    {
        init();
        work();
    }
    return 0;
}
