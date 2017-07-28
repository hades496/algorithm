/*
Written by Hades on 13th, July, 2017
This program is open-source and non-commercial
Please leave this paragraph if you copy the code
And give me the least amount of respect
Thank you for your cooperation
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#define mem(f) memset(f,0,sizeof(f))
typedef long long LL;
using namespace std;
map<LL,LL> rec;
LL x0;
LL pow_mod(LL a,LL i,LL n)//快速幂 a^i(mod n)
{
    if(i==0) return 1%n;
    LL temp=pow_mod(a,i>>1,n);
    temp=temp*temp%n;
    if(i&1) temp=temp*a%n;
    return temp;
}

//求原根
vector<LL>a;
bool g_test(LL g,LL p)
{
    for(LL i=0;i<a.size();i++)
        if(pow_mod(g,(p-1)/a[i],p)==1) return 0;
    return 1;
}
LL primitive_root(LL p)//求原根
{
    a.clear();
    LL tmp = p-1;
    for(LL i=2;i<=tmp/i;i++)
        if(tmp%i==0){
            a.push_back(i);
            while(tmp%i==0)
                tmp/=i;
        }
    if(tmp!=1) a.push_back(tmp);
    LL g=1;
    while(true){
        if(g_test(g,p)) return g;
        ++g;
    }
}

LL euler_phi(LL n)//求n的欧拉函数值
{
    LL m=(LL)sqrt(n+0.5);
    LL ans=n;
    for(LL i=2;i<=m;i++)if(n%i==0){
        ans=ans/i*(i-1);
        while(n%i==0)n/=i;
    }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}

//大步小步算法 或 叫Giant-Step Baby-Step

LL discrete_log(LL x,LL n,LL m)//求离散对数 x^y=n(mod m)
{
    rec.clear();
    LL s=(LL)(sqrt((double)m ) );
    for(;s*s<=m;)s++;
    LL cur=1;
    for(int i=0;i<s;++i){
        rec[cur]=i;
        cur=cur*x%m;
    }
    LL mul=cur;
    cur=1;
    for(int i=0;i<s;++i){
        LL more = n*pow_mod(cur,m-2,m)%m;
        if(rec.count(more)){
            return i*s+rec[more];
        }
        cur=cur*mul%m;
    }
    return -1;
}

LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
LL extend_gcd(LL a,LL b,LL &x,LL &y)//扩展欧几里得
{
    if(b==0){x=1;y=0;return a;}
    else {
        int r=extend_gcd(b,a%b,y,x);
        y-=x*(a/b);
        return r;
    }
}
vector<LL>ans;
void line_mod_equation(LL a,LL b,LL n)//单变元模线性方程 a*x=b(mod n),求x的解集
{
    LL x,y;
    LL d=extend_gcd(a,n,x,y);
    ans.clear();
    if(b%d==0){
        x=(x%n+n)%n;
        ans.push_back(x*(b/d)%(n/d));
        for(LL i=1;i<d;++i)
            ans.push_back((ans[0]+i*n/d)%n);
    }
}

LL mod_inverse(LL a, LL m)
{
    LL x, y;
    extend_gcd(a, m, x, y);
    return (m + x % m) % m;
}

void init()
{

}

void work()
{
    LL x,n,m,i,j,ans=100001;
    x=2;m=1e9+7;
    n=mod_inverse(1+x0,m);
    LL res = discrete_log(x,n,m);
    for(i=0;i<=100000;i++)
    {
        j=(res-i*3)/2;
        if (i+j<=100000&&j>=0&&i*3+j*2==res)
        {
            if (ans>i+j) ans=i+j;
        }
    }
    if (ans>100000) ans=-1;
    cout << ans << endl;
}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    //scanf("%d\n",&t);
    prep();
    while (cin>>x0)
    {
        init();
        work();
    }
    return 0;
}
