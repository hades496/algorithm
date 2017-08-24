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
const LL MOD = 142857;
const int N = 100005;
const int M = 500005;
int n,m,s,t,e,p;
int ind[N];

int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}

void init()
{
    int i,a,b;
    mem(ind);
    for(i=1;i<=m;i++)
    {
        a=F();b=F();
        ind[b]++;
        ind[a]++;
    }
}

bool eular_judge()
{
    int i,tot=0;
    for(i=1;i<=n;i++)
    {
        if(ind[i]&1) tot++;
        if(tot>2) return 0;
    }
    return 1;
}

void work()
{
    printf("%s\n",eular_judge()?"Full":"Part");
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
