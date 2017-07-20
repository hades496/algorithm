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
int n,p;
int pa[2*N],pb[2*N],pc[2*N];
int edge[N],point[2*N],next[2*N],back[2*N],ans[N];
bool has_p[N],has_e[2*N];
map<LL,LL> rec;

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

LL inv(LL a, LL m)
{
    LL x, y;
    extend_gcd(a, m, x, y);
    return (m + x % m) % m;
}

class graph_adlist
{
private:
    vector<int> edge,point,next,back;
    vector<bool> has_p,has_e;
    int n,m,e;
public:
    graph_adlist(int n1,int m1)
    {
        n=n1;m=m1;
        mem(edge);
        mem(next);
        mem(has_p);
        mem(has_e);
        mem(back);
    }
    void Link2(int a,int b,int x,int y,int z)
    {
        point[++e]=b; pa[e]=x; pb[e]=y; pc[e]=z; next[e]=edge[a]; edge[a]=e;
        point[++e]=a; pa[e]=x; pb[e]=y; pc[e]=z; next[e]=edge[b]; edge[b]=e;
        back[e]=e-1; back[e-1]=e;
    }
    void read()
    {
        int u,v,a,b,c,i;
        for(i=1;i<=n;i++)
        {
            scanf("%d%d%d%d%d",&u,&v,&a,&b,&c);
            Link2(u,v,a,b,c);
        }
    }

    int Traversal(int i)
    {
        int j,k;
        has_p[i]=1;
        for(j=edge[i];j;j=next[j])
        {
            if(has_e[j]) continue;
            has_e[j]=has_e[back[j]]=1;
            k=point[j];
            //option begin
            if(has_p[k])
                return k;
            else
            {
                int tmp=Traversal(k);
                if(tmp>0) return tmp;
            }
        }
        return -1;
    }
    bool GetOneAns(int i,LL a,LL b,LL c)
    {
        int j,k;
        has_p[i]=1;
        for(j=edge[i];j;j=next[j])
        {
            if(has_e[j]) continue;
            has_e[j]=has_e[back[j]]=1;
            k=point[j];
            //option begin
            if (k==cir)
            {
                ans[cir]=(pc[j]-pa[j]*inv(b,p)%p*c1%p+p)%p * inv((pb[j]-pa[j]*inv(b,p)%p+p)%p,p)
                return 1;
            }
            //option end
            if(a==0&&n==0&&c==0)
                if (GetOneAns(k,pa[j],pb[j],pc[j]))
                    return 1;
            else
                if (GetOneAns(k, pa[j]*inv(b,p)%p , pb[j], (pc[j]-pa[j]*inv(b,p)%p*c1%p+p)%p ))
                    return 1;
        }
        return 0;
    }
    bool GetAllAns(int i,LL x)
    {
        int j,k;
        has_p[i]=1;
        for(j=edge[i];j;j=next[j])
        {
            if(has_e[j]) continue;
            has_e[j]=has_e[back[j]]=1;
            k=point[j];
            //option begin
            ans[k]=(pc[j])
            //option end
        }
        return 0;
    }

    void Solution()
    {
        int i,u,v,c;
        read();
        cir = Traversal(1);

        mem(has_e);
        mem(has_p);
        GetOneAns(cir,0,0,0);

    }
};

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
    //scanf("%d\n",&t);
    //while(t--)
    while(cin >> n >> p)
    {
        //cin >> A >> B;
        init();
        work();
    }
    return 0;
}
