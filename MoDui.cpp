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
const LL N = 20005;
const LL MOD = 1e9+7;
LL a[N],len,ans,anss[N];
int n,m;
//hihocoder:1488
class BIT
{
    LL tree[N+1];
    int n;
public:
    BIT(int num){
        n=num;
        mem(tree);
    }
    void add(int x,LL t){
        while(x<=n){
            tree[x]+=t;
            x+=x&-x;
        }
    }
    LL operator [](int x){
        LL sum = 0;
        while(x){
            sum+=tree[x];
            x-=x&-x;
        }
        return sum;
    }
    void clear(){
        mem(tree);
    }
}s1(N),s2(N);

struct Quary
{
    int l,r,id,block;
    Quary(){}
    Quary(int l,int r,int i):l(l),r(r),id(i){
        block = l/len;
    }
} Q[N];

bool cmp(Quary a,Quary b){
    return a.block<b.block||a.block==b.l/len&&a.r<b.r;
}

void insert(LL x){
    ans+=s1[x]+(s2[N]-s2[x]+1)*x;
    s1.add(x,x);
    s2.add(x,1);
}
void erase(LL x){
    ans-=s1[x]+(s2[N]-s2[x])*x;
    s1.add(x,-x);
    s2.add(x,-1);
}

void init()
{
    int i,j,k;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%lld",&a[i]);
}

void work()
{
    int i,j,k;
    len = sqrt(n);
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&j,&k);
        Q[i]=Quary(j,k,i);
    }
    sort(Q+1,Q+1+m,cmp);
    int l=1,r=1;
    s1.clear(); s2.clear();mem(anss);
    s1.add(a[1],a[1]); s2.add(a[1],1);
    ans=s1[a[1]];
    for(i=1;i<=m;i++)
    {
        Quary &qi = Q[i];
        while(l>qi.l) insert(a[--l]);
        while(r<qi.r) insert(a[++r]);
        while(l<qi.l) erase(a[l++]);
        while(r>qi.r) erase(a[r--]);
        anss[qi.id]=ans;
    }
    for(i=1;i<=m;i++)
        cout << anss[i] <<endl;

}

void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
    int t;
    scanf("%d\n",&t);
    while(t--)
    //while(cin >> n)
    {
        //cin >> A >> B;
        init();
        work();
    }
    return 0;
}



