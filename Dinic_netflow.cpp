#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<queue>
#define LL long long
#define mem(f) memset(f,0,sizeof(f))
using namespace std;

const int N=1005;
const int M=100005;
const LL INF=0x3f3f3f3f;
void makedata()
{
    int n,t,i,j;
    LL k;
    srand(time(0));
    freopen("input.txt","w",stdout);
    t=20;
    printf("%d\n",t);
    while(t--)
    {
        n=rand()%100+1;
        printf("%d\n",n);
        j=0;
        for (i=1;i<=n;i++)
        {
            k=rand()%1001;
            j+=k;
            printf("%lld ",k);
        }
        printf("\n");
        for (i=1;i<=n-1;i++)
        {
            if (j!=0) k=rand()%min(1001,j);
            else k=0;
            j-=k;
            printf("%lld ",k);
        }
        printf("%d\n",j);
        for (i=1;i<=n;i++)
        {
            for (j=1;j<=n;j++)
            {
                k=rand()*rand()%1000000000;
                printf("%lld ",k);
            }
            printf("\n");
        }
    }
}

using namespace std;

class Dinic_flow
{
private:

    int n,e,p,ss,tt,flow;
    int d[N],q[N],edge[N],prevc[N],shift[N];
    int cont[M],point[M],nextc[M],back[M];

    int improve()
    {
        int i,j,delta=INF;
        for (i=prevc[tt];i;i=prevc[i])
        {
            if (cont[shift[i]]<=delta)
            {
                delta=cont[shift[i]];
                p=i;
            }
        }
        for (i=prevc[tt];i;i=prevc[i])
        {
            j=shift[i]; cont[j]-=delta;
            j=back[j]; cont[j]+=delta;
        }
        return delta;
    }

    int dfs()
    {
        int exist,i,j,k,flow=0;
        for (i=1;i<=n;i++) shift[i]=edge[i];
        i=ss; prevc[ss]=0;
        while(i)
        {
            for(j=shift[i],exist=0;j;j=nextc[j])
            {
                k=point[j];
                if (cont[j]>0&&d[i]+1==d[k])
                {
                    shift[i]=j;prevc[k]=i; i=k; exist=1;
                    if (i==tt)
                    {
                        flow+=improve();
                        i=p;
                    }
                    break;
                }
            }
            if (!exist)
            {
                d[i]=-1;
                i=prevc[i];
            }
        }
        return flow;
    }

    bool bfs()
    {
        int h,t,i,j,k;
        memset(d,-1,sizeof(d));
        h=0;t=1;q[1]=ss; d[ss]=0;
        while(h<t)
        {
            i=q[++h];
            for (j=edge[i];j;j=nextc[j])
            {
                k=point[j];
                if (cont[j]>0&&d[k]==-1)
                {
                    q[++t]=k; d[k]=d[i]+1;
                    if (k==tt)
                        return 1;
                }
            }
        }
        return 0;
    }

public:


    void link(int a,int b,int c)
    {
        //printf("%d--->%d : %d\n",a,b,c);
        point[++e]=b; cont[e]=c; nextc[e]=edge[a]; edge[a]=e;
        point[++e]=a; cont[e]=0; nextc[e]=edge[b]; edge[b]=e;
        back[e]=e-1; back[e-1]=e; n=max(n,a); n=max(n,b);
    }

    void Init(int s,int t)
    {
        ss=s; tt=t; e=0; n=0;
        mem(edge);
        mem(nextc);
    }


    int Dinic()
    {
        int flow=0;
        while(bfs()) flow+=dfs();
        return flow;
    }

}nc;

LL g[N][N];
int n,m,tot,st[N],go[N];

void init()
{
    int i,j,k,A,B,C,s,t;
    scanf("%d",&n);
    tot=0;
    for (i=1;i<=n;i++)
    {
        scanf("%d",&st[i]);
        tot+=st[i];
    }
    for (i=1;i<=n;i++)scanf("%d",&go[i]);

    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            scanf("%d",&g[i][j]);

    for (k=1;k<=n;k++)
        for (i=1;i<=n;i++)
            for (j=1;j<=n;j++)
                if (g[i][j]>g[i][k]+g[k][j])
                    g[i][j]=g[i][k]+g[k][j];
}

bool OK(LL mid)
{
    int i,j,k,ss,tt;
    ss=2*n+1;
    tt=2*n+2;
    nc.Init(ss,tt);
    for (i=1;i<=n;i++)
    {
        nc.link(ss,i,st[i]);
        nc.link(i+n,tt,go[i]);
        for (j=1;j<=n;j++)
            if (g[i][j]<=mid)
                nc.link(i,j+n,INF);
    }
    return nc.Dinic()==tot;
}

void work()
{
    LL l=0,r=INF*INF,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if (OK(mid))
            r=mid;
        else
            l=mid+1;
    }
    if (r==INF*INF) r=-1;
    printf("%lld\n",r);
}

int main()
{
    //makedata();
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
    while (t--)
    {
        init();
        work();
    }
    return 0;
}
