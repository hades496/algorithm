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
int n;
LL pa[2*N],pb[2*N],pc[2*N],cir,ans[N],p;
int edge[N],point[2*N],nextc[2*N],back[2*N];
bool has_p[N],has_e[2*N];
map<LL,LL> rec;

LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
LL extend_gcd(LL a,LL b,LL &x,LL &y)
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
    int n,m,e;
public:
    graph_adlist(int n1,int m1)
    {
        n=n1;m=m1; e=0;
        mem(edge);
        mem(nextc);
        mem(has_p);
        mem(has_e);
        mem(back);
    }
    void Link2(int a,int b,LL x,LL y,LL z)
    {
        point[++e]=b; pa[e]=x; pb[e]=y; pc[e]=z; nextc[e]=edge[a]; edge[a]=e;
        point[++e]=a; pa[e]=y; pb[e]=x; pc[e]=z; nextc[e]=edge[b]; edge[b]=e;
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
        for(j=edge[i];j;j=nextc[j])
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
        //printf("i=%d\n",i);
        //printf("a=%lld b=%lld c=%lld\n",a,b,c);

        int j,k;
        has_p[i]=1;
        for(j=edge[i];j;j=nextc[j])
        {
            if(has_e[j]) continue;
            has_e[j]=has_e[back[j]]=1;
            k=point[j];
            //printf("GOAk:%d\n",k);
            //option begin
            if (k==cir)
            {
                ans[cir]=(pc[j]-c*pa[j]%p*inv(b,p)%p%p+p)%p * inv((pb[j]-a*pa[j]%p*inv(b,p)%p+p)%p,p)%p;
                return 1;
            }
            //option end
            if(a+b+c==0)
            {
                if (GetOneAns(k,pa[j],pb[j],pc[j]))
                    return 1;
            }
            else
                if (GetOneAns(k, (p-a*pa[j]%p*inv(b,p)%p)%p , pb[j], (pc[j]-c*pa[j]%p*inv(b,p)%p%p+p)%p ))
                    return 1;
        }
        return 0;
    }
    bool GetAllAns(int i,LL x)
    {
        int j,k;
        has_p[i]=1;
        for(j=edge[i];j;j=nextc[j])
        {
            if(has_e[j]) continue;
            has_e[j]=has_e[back[j]]=1;
            k=point[j];
            //option begin
            //pa[j]x1+pb[j]x2=pc[j]
            if(k!=cir)
                ans[k]=((pc[j]-pa[j]*x%p+p)%p)*inv(pb[j],p)%p;
            if(!has_p[k])
                GetAllAns(k,ans[k]);
            //option end
        }
        return 0;
    }

    void Solution()
    {
        int i,u,v,c;
        read();
        cir = Traversal(1);
        //printf("cir=%d\n",cir);
        mem(has_e);
        mem(has_p);
        GetOneAns(cir,0,0,0);
        //printf("ans[cir]=%d\n",ans[cir]);
        mem(has_e);
        mem(has_p);
        GetAllAns(cir,ans[cir]);

        for(i=1;i<=n;i++)
            printf("%lld\n",ans[i]);
    }
};

void init()
{

}

void work()
{
    graph_adlist g(n,2*n);
    g.Solution();
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
