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
LL s[N],a[N],b[N],c[N];
int n;
void change(int i,LL x)
{
    while(i<=n)
    {
        s[i]+=x;
        i+=i&-i;
    }
}
LL query(int i)
{
    LL ans=0;
    while(i)
    {
        ans+=s[i];
        i-=i&-i;
    }
    return ans;
}
bool cmp(int x,int y)
{
    return a[x]<a[y];
}
void init()
{
    int i;
    LL j=0;
    mem(s);
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        a[i]++;
        b[i]=i;
    }
    sort(b+1,b+1+n,cmp);
    for(i=1;i<=n;i++)
    {
        if(a[b[i]]!=a[b[i-1]])
            j++;
        c[b[i]]=j;
    }
}

void work()
{
    LL ans=0;
    int i;
    for(i=1;i<=n;i++)
    {
        change(c[i],1);
        ans+=i-query(c[i]);
    }
    printf("%lld\n",ans);

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
