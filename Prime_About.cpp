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
const int N = 10000;
int prime[N],tot,n;
bool isnotprime[N];
void init()
{
}

void PrimeScreening_Linear()
{
    for(int i = 2,tot = 0; i <= n / 2; i++){
        if (!isnotprime[i]) prime[tot++]=i;
        for(int j = 0; j < tot && i * prime[j] <= n; j++){
            isnotprime[i*prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

void PrimeScreening()
{
    for(int i = 2,tot = 0; i <= n / 2; i++)
        if (!isnotprime[i]){
            prime[tot++]=i;
            for(int j = i+i; j <= n; j+=i) isnotprime[j] = 1;
        }
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
    freopen("output.txt","w",stdout);
    int t;
    prep();
//    scanf("%d\n",&t);
//    while(t--)
    //memset(dp,-1,sizeof dp);©исе╩╞
    while(scanf("%d",&n)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
