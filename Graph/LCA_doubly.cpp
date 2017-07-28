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
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 100005;
const int M = 200005;
int n,q,m;

int edge[N],point[M],nextc[M],val_e[M],deep[M],f[M][20];
bool has_trav[N];

class graph_adlist
{
private:
    int e;
public:
    graph_adlist()
    {
        e = 0; m = 0;
        mem(edge); mem(nextc); mem(has_trav);
    }
    void Link(int a,int b,int c = 0)
    {
        point[++e]=b; val_e[e]=c; nextc[e]=edge[a]; edge[a]=e;
        point[++e]=a; val_e[e]=c; nextc[e]=edge[b]; edge[b]=e;
    }
    void read()
    {
        int u,v,i;
        scanf("%d%d",&n,&q);
        m = log(n)/ log(2);
        for(i=1; i<n; i++)
        {
            scanf("%d%d",&u,&v);
            Link(u,v);
        }
    }
    void Traversal(int i,int dep)//遍历生成区间序列
    {
        int j,k;
        has_trav[i]=1; deep[i]=dep;
        for(j=edge[i],k=point[j]; j; j=nextc[j],k=point[j])
        {
            if(!has_trav[k])
            {
                Traversal(k,dep+1);
                f[k][0]=i;
            }
        }
    }
    void doubly()
    {
        int i,j;
        for(j=1;j<m;j++)
            for(i=1;i<=n;i++)
                f[i][j]=f[f[i][j-1]][j-1];
    }

    int LCA(int i,int j)//最近公共祖先-倍增算法
    {
        if(deep[i]>deep[j]) swap(i,j);
        int dep = deep[j]-deep[i];
        for(int k=0;dep>0;k++,dep=dep>>1)
            if(dep&1) j=f[j][k];
        for(int k=m;k>=0;k--)
            if(f[i][k]!=f[j][k])
            {
                i=f[i][k];
                j=f[j][k];
            }
        return i==j?i:f[i][0];
    }
    void Solution()//判断两条路径是否相交
    {
        int x1,x2,y1,y2;
        read();
        f[1][0]=0;
        Traversal(1,0);
        doubly();
        while(q--)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            int t1 = LCA(x1, y1);
            int t2 = LCA(x2, y2);
            printf("%s\n",(LCA(t1,t2)==t1&&(LCA(t2,x1)==t2||LCA(t2,y1)==t2)||LCA(t1,t2)==t2&&(LCA(t1,x2)==t1||LCA(t1,y2)==t1))?"YES":"NO");
        }
    }
};


void work()
{
    graph_adlist g;
    g.Solution();
}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    prep();
    int t;
    scanf("%d",&t);
    while(t--)
    //while(cin >> n >> p)
    {
        work();
    }
    return 0;
}
