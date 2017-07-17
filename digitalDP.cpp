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
typedef long long LL;
using namespace std;
const int N = 105;
int a[20],x,l,r,n;
int dp[20][200];
vector <int> sta;
int dfs(int pos,int sum,bool limit)
{
    if(pos==-1)
    {
        if(sum==x)
        {
            for(int i=0;i<sta.size();i++)
                cout << sta[i];
            cout << endl;
            return 1;
        }
        return sum==x;
    }
    //if(!limit && dp[pos][sum+100]!=-1) return dp[pos][sum+100];
    int up=limit ? a[pos] : 9;
    int tmp=0;
    for(int i=0;i<=up;i++)
    {
        sta.push_back(i);
        tmp+=dfs(pos-1,i-sum,limit && i==a[pos])*i*pow(10,pos);
        sta.pop_back();
    }
    if(!limit) dp[pos][100+sum]=tmp;
    return tmp;
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
    for(int i=0;i<n/2;i++) swap(a[i],a[n-i-1]);
    return dfs(pos-1,0,true);
}

void init()
{

}

void work()
{

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
        memset(dp,-1,sizeof dp);
        printf("%d\n",solve(r)-solve(l-1));
        cout << solve(r) << endl;
        memset(dp,-1,sizeof dp);
        cout << ' ' <<solve(l-1)<< endl;
    }
    return 0;
}
