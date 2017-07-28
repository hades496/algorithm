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
int n,q,root;

int edge[N],point[M],nextc[M],val_e[M],deep[M],ver[M],first[M],st[M][20];
map<string,int> H;
string name[N];
bool has_trav[N];

class graph_adlist
{
private:
    int e,tot;
public:
    graph_adlist()
    {
        e = 0; tot = 0;
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
        string a,b;
        for(i=1; i<=n; i++)
        {
            cin >> a >> b;
            if (!(u=H[a])) u=H[a]=++tot,name[u]=a;
            if (!(v=H[b])) v=H[b]=++tot,name[v]=b;
            Link(u,v);
            if(i==1) root = u;
        }
    }
    void Traversal(int i,int dep)//遍历生成区间序列
    {
        int j,k;
        has_trav[i]=1; ver[++tot]=i; first[i]=tot; deep[tot]=dep;
        for(j=edge[i],k=point[j]; j; j=nextc[j],k=point[j])
        {
            if(!has_trav[k])
            {
                Traversal(k,dep+1);
                ver[++tot]=i;
                deep[tot]=dep;
            }
        }
    }
    void ST(int n)//预处理1~n
    {
        int i,j;
        for(i=1; i<=n; i++) st[i][0]=i;
        for(j=1; (1<<j)<=n; j++)
            for(i=1; i+(1<<j)-1<=n; i++)
            {
                int a=st[i][j-1], b=st[i+(1<<(j-1))][j-1];
                st[i][j] = deep[a] < deep[b] ? a : b;
            }
    }
    int RMQ(int l,int r)//区间最小值
    {
        int k = 0;
        while((1<<(k+1))<r-l+1) k++;
        int a = st[l][k], b = st[r-(1<<k)+1][k];
        return deep[a] < deep[b] ? a : b;
    }
    int LCA(int i,int j)//最近公共祖先-ST算法
    {
        int x = first[i], y = first[j];
        if(x > y) swap(x,y);
        return ver[RMQ(x,y)];
    }
    void Solution()//判断两条路径是否相交
    {
        read();
        Traversal(root,0);
        ST(tot);
        cin >> q;
        while(q--)
        {
            string a,b;
            int u,v;
            cin >> a>> b;
            cout << name[LCA(H[a],H[b])]<<endl;
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
//    prep();
//    int t;
//    scanf("%d",&t);
//    while(t--)
    while(cin >> n )
    {
        work();
    }
    return 0;
}
