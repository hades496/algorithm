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
#define double char
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 100005;
int sa[N],s[N],wa[N], wb[N], wn[N], wv[N], r[N];
int rank[N], height[N];
string str;
bool cmp(int r[], int a, int b, int l)
{
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int r[], int sa[], int n, int m)
{
    int i, j, p, *x = wa, *y = wb;
    for (i = 0; i < m; ++i) wn[i] = 0;
    for (i = 0; i < n; ++i) wn[x[i]=r[i]]++;
    for (i = 1; i < m; ++i) wn[i] += wn[i-1];
    for (i = n-1; i >= 0; --i) sa[--wn[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p)
    {
        for (p = 0, i = n - j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < n; ++i) wv[i] = x[y[i]];
        for (i = 0; i < m; ++i) wn[i] = 0;
        for (i = 0; i < n; ++i) wn[wv[i]]++;
        for (i = 1; i < m; ++i) wn[i] += wn[i-1];
        for (i = n-1; i >= 0; --i) sa[--wn[wv[i]]] = y[i];
        for (std::swap(x, y), p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
    }
}

void calheight(int r[], int sa[], int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; ++i) rank[sa[i]] = i;
    for (i = 0; i < n; height[rank[i++]] = k)
        for (k?k--:0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k++);
}


void init()
{

}

void work()
{
    for(int i=0;i<str.length();i++)
        r[i]=str[i];
    r[str.length()]='$';
    da(r,sa,str.length()+1,128);
    calheight(r,sa,str.length()+1);
    for(int i=1;i<=str.length();i++)
        printf("%d ",height[i]);
    printf("\n");
}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
    //int t;
    //scanf("%d\n",&t);
    //while(t--)
    while(cin >> str)
    {
        init();
        work();
    }
    return 0;
}
