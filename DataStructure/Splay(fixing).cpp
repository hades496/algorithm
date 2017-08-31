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
    int key;
    inline node(int x,node *fa = NULL):key(x),father(fa)
    {
        ch[0] = ch[1] = NULL;
    }
};

struct Splay
{
    node *root;
    Splay(){root = NULL;insert(-INF);insert(INF);}
    inline bool lr(node* f,node* s){return f->ch[1]==s;} //true means s is right-child of f
    inline void lrr(node *b,int lrl) //lrl==0 means left rotation ,1 means right rotation
    {
        node *a = b->father,*f = a->father,*d = b->ch[lrl];
        b->father = f; if(f) f->ch[lr(f,a)] = b; else root = b;
        a->ch[lrl^1] = d; if(d) d->father = a;
        b->ch[lrl] = a; a->father = b;
    }
    void Path(node*rt)
    {
        if(rt==NULL) return;
        printf("x=%d l=%d r=%d\n",rt->key,rt->ch[0]?rt->ch[0]->key:-1,rt->ch[1]?rt->ch[1]->key:-1);
        Path(rt->ch[0]);
        Path(rt->ch[1]);
    }
    void splay(node*x, node*y)
    {
        while(x->father != y)
        {
            node*p = x->father;
            if (p->father == y) lrr(x,lr(p,x)^1);
            else//zig-zig or zag
            {
                node* g = p->father;
                node* t = lr(p,x)^lr(g,p)?x:p;
                lrr(t,lr(t->father,t)^1);
                lrr(x,lr(x->father,x)^1);
            }
        }
    }
    node* BST_insert(node*rt,int x,node* fa,bool lr)
    {
        if(rt==NULL)
        {
            rt = new node(x,fa);
            if (root==NULL) root=rt;
            if(fa) fa->ch[lr] = rt;
            splay(rt,NULL);
            return rt;
        }
        else
            return BST_insert(rt->ch[x > rt->key], x, rt,x > rt->key);
    }
    node* insert(int x)
    {
        node *rt=BST_insert(root,x,NULL,0);
        splay(rt,NULL);
        return rt;
    }
    node* find(int x)
    {
        node* rt=root;
        while(rt)
        {
            if(rt->key==x) return rt;
            else rt=rt->ch[x>rt->key];
        }
        return rt;
    }
    node* near(node* a,int lrf) //lrf = 0 means prev node,1 means next node
    {
        a=a->ch[lrf];
        while(a->ch[lrf^1]) a=a->ch[lrf^1];
        return a;
    }
    void erase(int a,int b)
    {
        node*ra=find(a);
        node*rb=find(b);
        if(ra==NULL) ra=insert(a);
        if(rb==NULL) rb=insert(b);
        splay(ra,NULL); ra = near(ra,0);
        splay(rb,NULL); rb = near(rb,1);
        splay(ra,NULL); splay(rb,ra);
        rb->ch[0]=NULL;
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
} *splay;


void init()
{
}
int n;
void work()
{
    int x,y;
    char c;
    splay = new Splay();
    while(n--)
    {
        scanf("\n%c %d",&c,&x);
        if(c=='I') splay->insert(x);
        else if(c=='Q') printf("%d\n",splay->query(x));
        else {
           scanf("%d",&y);
           splay->erase(x,y);
        }
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
