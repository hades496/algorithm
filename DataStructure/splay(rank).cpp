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
    int key,size;
    inline node(int x,node *fa = NULL):key(x),father(fa){ch[0] = ch[1] = NULL; size = 1;}
};

struct Splay
{
    node *root;
    Splay(){root = NULL;insert(-INF);insert(INF);}
    inline bool lr(node* s){return s->father->ch[1]==s;} //true means s is right-child
    inline int updata(node* rt){
        int res = 1;
        if(rt->ch[0]) res+=rt->ch[0]->size;
        if(rt->ch[1]) res+=rt->ch[1]->size;
        return rt->size = res;
    }
    inline void lrr(node *b)
    {
        int ore = lr(b); //ore==1 means left rotation ,0 means right rotation
        node *a = b->father,*f = a->father,*d = b->ch[ore^1];
        b->father = f; if(f) f->ch[lr(a)] = b; else root = b;
        a->ch[ore] = d; if(d) d->father = a;
        b->ch[ore^1] = a; a->father = b;
        updata(a); updata(b);
    }
    void splay(node*x, node*y)
    {
        while(x->father != y)
        {
            lrr(x);
//            node*p = x->father;
//            if (p->father == y) lrr(x);
//            else
//            {
//                lrr(lr(x)^lr(p)?x:p);
//                lrr(x);
//            }
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
            if(rt->key == x) return rt;
            else return BST_insert(rt->ch[x > rt->key], x, rt,x > rt->key);
    }
    node* insert(int x)
    {
        node *rt=BST_insert(root,x,NULL,0);
        splay(rt,NULL);
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
        node*ra=insert(a); ra = near(ra,0);
        node*rb=insert(b); rb = near(rb,1);
        splay(ra,NULL); splay(rb,ra);
        rb->ch[0]=NULL;
        updata(rb); updata(ra);
    }
    int rank(int x)//x-th min
    {
        node *rt = root;
        x++;
        while(rt)
        {
            int rak=rt->ch[0]?rt->ch[0]->size+1:1;
            if (rak==x) return rt->key;
            if (rak<x)
            {
                x -= rak;
                rt = rt->ch[1];
            }
            else
            {
                rt = rt->ch[0];
            }
        }
        return 0;
    }
    int query(int x)
    {
        node *rt=root;
        int ans = -INF;
        while(rt!=NULL)
        {
            if(rt->key > ans &&rt->key <= x) ans = rt->key;
            if(rt->key <=x) rt=rt->ch[1];
            else rt=rt->ch[0];
        }
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
        else if(c=='Q')printf("%d\n",splay->query(x));
        else
        {
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
