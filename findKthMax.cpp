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
#include<bitset>
#define mem(f) memset(f,0,sizeof(f))
#define P2 pair<LL,LL>

typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 2005;

int n,m,a[N],center[N],s[N];
void init()
{
    int i;
    for(i=1;i<=n;i++) cin >> a[i];

}



int findKthMax(int l,int r,int k)
{
    if(l==r) return a[l];
    int x = (l+r) >> 1,v = a[x],i = l,j = r;
    swap(a[x],a[l]);
    while(i<j)
    {
        while(i<j && a[j]<v) --j;
        if(i<j) a[i]=a[j],++i;
        else break;

        while(i<j && a[i]>v) ++i;
        if(i<j) a[j]=a[i],--j;
        else break;
    }
    a[i]=v;
    if(i<k) return findKthMax(i+1,r,k);
    if(i>k) return findKthMax(l,i-1,k);
    return a[i];
}


void work()
{
    cout << findKthMax(1,n,m) << endl;
}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
//    int t;
//    scanf("%d\n",&t);
//    while(t--)
    while(cin >> n >> m)
    {
        init();
        work();
    }

    return 0;
}

