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
int n,h[N],a[N];
inline int lowbit(int x) {return x&-x;}
void updata(int x)
{
    int lx, i;
    while (x <= n)
    {
        h[x] = a[x];
        lx = lowbit(x);
        for (i=1; i<lx; i<<=1)
            h[x] = min(h[x], h[x-i]);
        x += lowbit(x);
    }
}
int query(int x, int y)
{
    int ans = MAXINT;
    while (y >= x)
    {
        ans = min(a[y], ans);
        y --;
        for (; y-lowbit(y) >= x; y -= lowbit(y))
            ans = min(h[y], ans);
    }
    return ans;
}

int init()
{
    mem(a);
    for(register int i = 0; i <= n; ++i) h[i]=MAXINT;
    for(register int i = 1; i <= n; ++i) scanf("%d",&a[i]);
    for(register int i = 1; i <= n; ++i) updata(i);
}

int work()
{
    int q;
    for(cin >> q;q--;)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(l,r));
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
