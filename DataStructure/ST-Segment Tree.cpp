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
const int N = 1000005;
const int MAXINT = 0x7fffffff;
int n,a[N],d[3*N],ma=0;
int updata(int i,int l,int r,int x,int y)
{
    //printf("i=%d l=%d r=%d\n",i,l,r);
    if(l==r) printf("i=%d l=%d r=%d\n",i,l,r);
    if(l==r)
        return d[i]=y;
    int m=(l+r)/2;
    if(x<=m) return d[i]=min(d[i<<1|1],updata(i<<1,l,m,x,y));
    else return d[i]=min(d[i<<1],updata(i<<1|1,m+1,r,x,y));
}
int query(int i,int l,int r,int x, int y)
{
    if(l==x&&r==y)return d[i];
    int m=(l+r)/2;
    if(y<=m) return query(i<<1,l,m,x,y);
    if(x>m) return query(i<<1|1,m+1,r,x,y);
    return min(query(i<<1,l,m,x,m),query(i<<1|1,m+1,r,m+1,y));
}
int init()
{
    for(register int i = 1; i <= 2*n; ++i) d[i]=MAXINT;
    for(register int i = 1; i <= n; ++i) scanf("%d",&a[i]);
    for(register int i = 1; i <= n; ++i) updata(1,1,n,i,a[i]);
}

int work()
{
    int q,o,x,y;
    for(cin>>q;q--;)
    {
        scanf("%d%d%d",&o,&x,&y);
        if(o) updata(1,1,n,x,y);
        else printf("%d\n",query(1,1,n,x,y));
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
