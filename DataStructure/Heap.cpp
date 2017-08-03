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
const int N = 1000005;
const int M = 1000005;
int n,m;
int a[N],h[N];
int aa;char ch;inline int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}
void init()
{
    m=0;
    h[0]=0x7FFFFFFF;
}

void push(int x)
{
    int i=++m;
    h[i]=x;
    while (i>1&&h[i]>h[i>>1]) swap(h[i],h[i>>1]),i>>=1;
}
void pop()
{
    printf("%d\n",h[1]);
    swap(h[1],h[m]);
    h[m--]=0;
    int i=1;
    while(h[i]<h[i<<1]||h[i]<h[i<<1|1])
    {
        if(h[i<<1]<h[i<<1|1]) swap(h[i],h[i<<1|1]),i=i<<1|1;
        else swap(h[i],h[i<<1]),i<<=1;
    }
}

void work()
{
    for(int i=1;i<=n;i++)
    {
        char c=' ';
        int j;
        while(c!='T'&&c!='A') scanf("%c",&c);
        if(c=='A')
        {
            j=F();
            push(j);
        }
        else pop();
    }
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
    while(scanf("%d%d",&n)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
