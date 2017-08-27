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
const int N = 10005 * 50;
const int M = 1000005;
const LL INF=0x3f3f3f3f;

int tot,n;
int father[N],flag[N],now[N],fail[N],nextc[N][26];
char str[M];

inline LL read()
{
    LL x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

void insert(char *s)
{
    int i,j,k,t;
    for(t=0;*s;++s)
    {
        int c = *s - 'a';
        if (nextc[t][c]==0)
        {
            nextc[t][c] = ++tot;
            now[tot] = c;
            father[tot] = t;
        }
        t = nextc[t][c];
    }
    flag[t]++;
}

void getfail(int t)
{
    for(t=1;t<=tot;++t)
        if (father[t])
        {
            int f = fail[father[t]];
            while (nextc[f][now[t]]==0&&f) f = fail[f];
            fail[t] = nextc[f][now[t]];
        }
}

void init()
{
    int i;
    n = read();
    tot=0; mem(nextc);mem(flag);mem(fail);
    for(i=1;i<=n;++i)
    {
        scanf("%s",str);
        insert(str);
    }
    scanf("%s",str);
    getfail(0);
}

void work(char *qstr)
{
    int i,t,ans=0;
    for(t=0;*qstr;++qstr)
    {
        int index = *qstr - 'a';
        while(t&&nextc[t][index]==0) t = fail[t];
        t = nextc[t][index];
        int temp = t;
        while(temp&&flag[temp])
        {
            ans+= flag[temp];
            flag[temp]=0;
            temp = fail[temp];
        }
    }
    cout << ans << endl;
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
    while(t--)
    //while (cin >> n)
    {
        init();
        work(str);
    }
    return 0;
}
