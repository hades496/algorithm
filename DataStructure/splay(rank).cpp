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
    inline bool isRight(node* s){return s->father->ch[1]==s;} //true means s is right-child
    inline int updata(node* rt){
        int res = 1;
        if(rt->ch[0]) res+=rt->ch[0]->size;
        if(rt->ch[1]) res+=rt->ch[1]->size;
        return rt->size = res;
    }
    inline void rotate(node *b)
    {
        int dir = isRight(b)^1; //dir==0 means left rotation ,1 means right rotation
        node *a = b->father,*f = a->father,*d = b->ch[dir];
        b->father = f; if(f) f->ch[isRight(a)] = b; else root = b;
        a->ch[dir^1] = d; if(d) d->father = a;
        b->ch[dir] = a; a->father = b;
        updata(a); updata(b);//维护节点数， 注意先儿子后父亲
    }
    void splay(node*x, node*y)
    {
        while(x->father != y)
        {
            node*p = x->father;
            if (p->father == y) rotate(x);
            else
            {
                node* g = p->father,*t = isRight(x)^isRight(p)?x:p;
                rotate(t);
                rotate(x);
            }
        }
    }
    node* BST_insert(node*rt,int x,node* fa,bool isRight)
    {
        if(rt==NULL)
        {
            rt = new node(x,fa);
            if (root==NULL) root=rt;
            if(fa) fa->ch[isRight] = rt;
            splay(rt,NULL);
            return rt;
        }
        else
            if(rt->key == x) return rt;//不重复计数
            else return BST_insert(rt->ch[x > rt->key], x, rt,x > rt->key);
    }
    inline node* insert(int x)
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
        node *rt = root;x++;
        while(rt)
        {
            int rak=rt->ch[0]?rt->ch[0]->size+1:1;
            if (rak==x) return rt->key;
            if (x<rak) rt = rt->ch[0];
            else
            {
                x -= rak;
                rt = rt->ch[1];
            }
        }
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
        else printf("%d\n",splay->rank(x));

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
