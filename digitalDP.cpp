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
int a[20],x,l,r,n;
LL fact[20];
P2 dp[20][200];
P2 dfs(int pos,int sum,bool limit)
{
    if(pos==-1) return P2(sum==x,0);
    if(!limit && dp[pos][sum+100].first!=-1) return dp[pos][sum+100];
    int up=limit ? a[pos] : 9;
    LL tmp=0,tot=0;
    for(int i=0; i<=up; i++)
    {
        P2 te=dfs(pos-1,i-sum,limit && i==a[pos]);
        tmp=(tmp+te.first)%MOD;
        tot=(tot+te.first*i*fact[pos]+te.second)%MOD;
    }
    if(!limit) dp[pos][100+sum]=P2(tmp,tot);
    return P2(tmp,tot);
}
int solve(int x)
{
    int pos=0;
    while(x)
    {
        a[pos++]=x%10;
        x/=10;
    }
    n=pos;
//    for(int i=0; i<n/2; i++) swap(a[i],a[n-i-1]);
    return dfs(pos-1,0,true).second;
}

void init()
{

}

void work()
{
    fact[0]=1;
    for(int i=1;i<20;i++) fact[i]=(fact[i-1]*10)%MOD;
    memset(dp,-1,sizeof dp);
    cout << solve(r) -solve(l-1)<< endl;
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
    //memset(dp,-1,sizeof dp);可优化
    while(scanf("%d%d%d",&l,&r,&x)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
