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
#define pb(x) push_back(x)
typedef long long LL;
using namespace std;
const LL MOD = 1e9+7;
const int N = 1000005;
const int M = 1000005;
const LL INF=0x3f3f3f3f;

struct node
{
    node *father,*ch[2];
    int key,weight;
    inline node() {}
    inline node(int x,node *fa = NULL):key(x),father(fa)
    {
        ch[0] = ch[1] = NULL;
        weight = rand();
    }
};

struct Treap
{
    node *root;
    Treap(){root = NULL;}
    inline bool lr(node* f,node* s){return f->ch[1]==s;}
    inline void lrr(node *a,int lrl)
    {
        node *b = a->ch[lrl^1],*f = a->father,*d = b->ch[lrl];
        b->father = f; if(f) f->ch[lr(f,a)] = b; else root = b;
        a->ch[lrl^1] = d; if(d) d->father = a;
        b->ch[lrl] = a; a->father = b;
    }
    node* insert(node*rt,int x,node* fa,int lr)
    {
        if(rt==NULL)
        {
            rt = new node(x,fa);
            if (root==NULL) root=rt;
            if(fa) fa->ch[lr] = rt;
            return rt;
        }
        else
            return insert(rt->ch[x > rt->key], x, rt, x > rt->key);
    }
    inline void rotate(int x)
    {
        node *rt=insert(root,x,NULL,0);
        for(node*fa=rt->father; fa!=NULL &&rt->weight < fa->weight; fa = rt->father)
            lrr(fa,lr(fa,rt)^1);
    }
    int query(int x)
    {
        node *rt=root;
        int ans = -INF;
        while(rt!=NULL)
            if(rt->key<=x &&rt->key > ans)
            {
                ans = rt->key;
                rt = rt->ch[1];
            }
            else rt = rt->ch[0];
        return ans;
    }
} *treap;


void init()
{
}
int n;
void work()
{
    int x;
    char c;
    treap = new Treap();
    while(n--)
    {
        scanf("\n%c %d",&c,&x);
        if(c=='I') treap->rotate(x);
        else printf("%d\n",treap->query(x));

    }
}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
//    int t;
//    scanf("%d\n",&t);
//    while(t--)
    while (cin >> n)
    {
        init();
        work();
    }
    return 0;
}
