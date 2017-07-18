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
#define mem(f) memset(f,0,sizeof(f))
#define P2 pair<LL,LL>
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
LL a[20],x,n;
LL l,r;
LL fact[20];
P2 f[20][200][20];//前ｉ位，总和为ｊ，位数为ｄ的总数

P2 dfs(int pos,int sum,bool limit,LL dig)
{
    P2 tmp(0,0);
    if (pos == -1) return P2(sum == x ,0);
    if( !limit && f[pos][sum + 100][dig].first != -1) return f[pos][sum + 100][dig];
    for(int i = 0; i <= (limit ? a[pos] : 9); i++)
    {
        P2 te = dfs(pos-1, sum + i*(dig&1?-1:1), limit && i == a[pos],dig+(i!=0||dig!=0));
        tmp.first=(tmp.first + te.first) % MOD;
        tmp.second=(te.second + (tmp.second + te.first * (i * fact[pos]) % MOD) % MOD) % MOD;
    }
    if(!limit) f[pos][100 + sum][dig] = tmp;
    return tmp;
}
LL solve(LL x)
{
    if(x<0) return 0;
    int pos = 0;
    while(x)
    {
        a[pos++] = x % 10;
        x /= 10;
    }
    P2 tmp=dfs(pos - 1, 0, true,0);
    return tmp.second;
}

void init()
{

}

void work()
{
    fact[0]=1;
    for(int i = 1; i < 20; i++) fact[i]=(fact[i - 1] * 10) % MOD;
    memset(f, -1, sizeof(f));
    cout << (solve(r) - solve(l - 1) + MOD) % MOD << endl;
}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    prep();
//    scanf("%d\n",&t);
//    while(t--)
    while(cin >> l >> r >> x)
    {
        init();
        work();
    }
    return 0;
}
