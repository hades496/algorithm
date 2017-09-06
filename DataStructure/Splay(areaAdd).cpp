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
    int id;
    LL val,size,sumval,lazy;
    inline node(int i,LL x,node *fa):id(i),val(x),father(fa)
    {
        ch[0] = ch[1] = NULL;
        size = 1;
        sumval = val;
        lazy = 0;
    }
};

struct Splay
{
    node *root;
    Splay()
    {
        root = NULL;
        insert(-INF,-INF);
        insert(INF,INF);
    }
    inline bool isRight(node* s)
    {
        return s->father->ch[1]==s;   //true means s is right-child
    }
    inline void update(node* x)
    {
        x->size = 1;
        x->sumval = x->val;
        for(int i=0;i<2;i++)
        {
            if(x->ch[i])
            {
                x->size += x->ch[i]->size;
                x->sumval += x->ch[i]->sumval;
            }
        }
    }
    inline void rotate(node *b)
    {
        int dir = isRight(b)^1; //dir==0 means left rotation ,1 means right rotation
        node *a = b->father,*f = a->father,*d = b->ch[dir];
        send(a); send(b);
        b->father = f;
        if(f) f->ch[isRight(a)] = b;
        else root = b;
        a->ch[dir^1] = d;
        if(d) d->father = a;
        b->ch[dir] = a;
        a->father = b;
        update(a);
        update(b);//维护节点数， 注意先儿子后父亲
    }

    void splay(node*x, node*y)
    {
        while(x->father != y)
        {
            node*p = x->father;
            if (p->father == y) rotate(x);
            else
            {
                node *t = isRight(x)^isRight(p)?x:p;
                rotate(t);
                rotate(x);

            }
        }
    }
    node* BST_insert(node*rt,int id,LL x,node* fa,bool isRight)
    {
        node* res;
        if(rt==NULL)
        {
            rt = new node(id,x,fa);
            if (root==NULL) root=rt;
            if(fa) fa->ch[isRight] = rt;
            res = rt;
        }
        else
        {
            send(rt);
            res=BST_insert(rt->ch[id > rt->id],id, x, rt,id > rt->id);
        }
        update(rt);
        return res;
    }
    inline node* insert(int id,LL x)
    {
        node *rt=BST_insert(root,id,x,NULL,0);
        splay(rt,NULL);
        return rt;
    }
    node* near(node* a,int lrf) //lrf = 0 means prev node,1 means next node
    {
        splay(a,NULL);
        a=a->ch[lrf];
        while(a->ch[lrf^1]) a=a->ch[lrf^1];
        return a;
    }
    void erase(int a,int b)
    {
        node *pa = near(lower_bound(a),0);
        node *pb = upper_bound(b);
        splay(pa,NULL);
        splay(pb,pa);
        pb->ch[0]=NULL;
        update(pb);
        update(pa);
    }
    int rank(int x)//x-th min
    {
        node *rt = root;
        x++;
        while(rt)
        {
            int rak=rt->ch[0]?rt->ch[0]->size+1:1;
            if (rak==x) return rt->val;
            if (x<rak) rt = rt->ch[0];
            else
            {
                x -= rak;
                rt = rt->ch[1];
            }
        }
    }
    node* lower_bound(LL x)//id大于等于x的最小节点
    {
        node *rt=root;
        node *ans = new node(INF,INF,NULL);
        while(rt!=NULL)
        {
            if(rt->id < ans->id &&rt->id >= x) ans = rt;
            if(rt->id >= x) rt=rt->ch[0];
            else rt=rt->ch[1];
        }
        return ans;
    }
    node* upper_bound(LL x)//id大于x的最小节点
    {
        node *rt=root;
        node *ans = new node(INF<<1,INF<<1,NULL);
        while(rt!=NULL)
        {
            if(rt->id < ans->id &&rt->id > x) ans = rt;
            if(rt->id > x) rt=rt->ch[0];
            else rt=rt->ch[1];
        }
        return ans;
    }
    inline void marking(node *t,LL delta)
    {
        t->lazy += delta;
        t->sumval += t->size * delta;
        t->val += delta;
    }
    void send(node* t)
    {
        if(t->ch[0]) marking(t->ch[0],t->lazy);
        if(t->ch[1]) marking(t->ch[1],t->lazy);
        t->lazy = 0;
        update(t);
    }
    void add(LL a,LL b,LL d)
    {
        node *pa = near(lower_bound(a),0);
        node *pb = upper_bound(b);
        splay(pa,NULL);
        splay(pb,pa);
        marking(pb->ch[0],d);
    }
    LL query(LL a,LL b)
    {
        node *pa = near(lower_bound(a),0);
        node *pb = upper_bound(b);
        splay(pa,NULL);
        splay(pb,pa);

        return pb->ch[0]->sumval;
    }


} *splay;

void init()
{
}
int n;
void work()
{
    int id,val,d;
    char c;
    splay = new Splay();
    while(n--)
    {
        scanf("\n%c %d %d",&c,&id,&val);
        if(c=='I') splay->insert(id,val);
        else if(c=='Q') printf("%lld\n",splay->query(id,val));
        else if(c=='D')
        {
            splay->erase(id,val);
        }
        else
        {
            scanf("%d",&d);
            splay->add(id,val,d);
        }
    }
}

int main()
{
    //freopen("input.txt","r",stdin);
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
