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
string str;
int rank[N];
struct rec
{
    int l,x,y;
    inline rec(){}
    inline rec(int l,int x,int y):l(l),x(x),y(y){}
};
rec sa[N];

bool cmp0(rec a,rec b)
{
    return str[a.l]<str[b.l];
}

bool cmp(rec a,rec b)
{
    return a.x<b.x||a.x==b.x&&a.y<b.y;
}

void sort_box(int n)
{
    vector<rec> box[N+1];
    int i,j,k;
    mem(box);
    for(i=0;i<n;i++)
        box[sa[i].y].push_back(sa[i]);
    j=0;
    for(i=0;i<=n;i++)
    {
        if(!box[i].empty())
        {
            for(k=0;k<box[i].size();k++)
                sa[j++]=box[i][k];
        }
    }
    mem(box);
    for(i=0;i<n;i++)
        box[sa[i].x].push_back(sa[i]);
    j=0;
    for(i=0;i<=n;i++)
    {
        if(!box[i].empty())
        {
            for(k=0;k<box[i].size();k++)
                sa[j++]=box[i][k];
        }
    }
}

void suffix_array(string str)
{
    int i,j,k,n=str.length();
    for(i=0;i<n;i++) sa[i].l=i;
    sort(sa,sa+n,cmp0);
    rank[sa[0].l]=1;
    for(k=1,i=1;i<n;i++)
    {
        if (str[sa[i].l]!=str[sa[i-1].l]) k++;
        rank[sa[i].l]=k;
    }
    for(j=1;(1<<j)<n&&k<=n;j++)
    {
        printf("rank[] is :\n");
        for(int i=0;i<str.length();i++)
            printf("%d ",rank[i]);
        printf("\n");
        for(i=0;i<n;i++)
        {
            sa[i].x=rank[sa[i].l];
            sa[i].y=rank[sa[i].l+(1<<(j-1))];
        }
        sort_box(n);
        rank[sa[0].l]=1;
        for(k=1,i=1;i<n;i++)
        {
            if (sa[i].x!=sa[i-1].x||sa[i].y!=sa[i-1].y) k++;
            rank[sa[i].l]=k;
        }
    }
}

void init()
{

}

void work()
{
    suffix_array(str);
    for(int i=0;i<str.length();i++)
        printf("%d ",rank[i]);
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
