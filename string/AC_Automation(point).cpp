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
const int N = 10005 * 50;
const int M = 1000005;
const LL INF=0x3f3f3f3f;
inline LL read()
{
    LL x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int tot,n;
char str[M];

class Node
{
public:
    Node *fail,*next[26];
    int cnt;
    Node()
    {
        mem(next);
        fail = NULL;
        cnt = 0;
    }
};

class AC_Automation:public Node
{
private:
    Node *root, *q[N];
    int head,tail;
public:
    AC_Automation()
    {
        root = new Node;
        head = tail = 0;
        root->fail = root;
    }
    void insert(char *str)
    {
        Node *t;
        for(t=root; *str; t=t->next[*str-'a'],++str)
            if(t->next[*str-'a']==NULL)
                t->next[*str-'a'] = new Node;
        t->cnt++;
    }
    void getfail()
    {
        for(q[0] = root; head <= tail; head++)
        {
            Node *t = q[head];
            for(int i=0; i<26; i++)
                if(t->next[i]!=NULL)
                {
                    Node *f = t->fail;//从t的fail节点开始
                    while(f!=root&&f->next[i]==NULL) f=f->fail;
                    if(f->next[i]!=NULL&&t!=root) t->next[i]->fail = f->next[i];//非根节点或根节点的儿子
                    else t->next[i]->fail = root;
                    q[++tail] = t->next[i];
                }
        }
    }
    int query(char *str)
    {
        int ans=0;
        for(Node *temp, *t=root; *str; ++str)
        {
            int i = *str - 'a';
            while(t!=root&&t->next[i]==NULL) t = t->fail;
            if(t->next[i]!=NULL) t = t->next[i];
            for(temp = t;temp!=root&&temp->cnt!=-1;temp = temp -> fail)
            {
                ans+= temp->cnt;
                temp->cnt=-1;
            }
        }
        return ans;
    }
};
AC_Automation *AC;

void init()
{
    int i;
    n = read();
    AC = new AC_Automation;
    for(i=1; i<=n; ++i)
    {
        scanf("%s",str);
        AC->insert(str);
    }
    scanf("%s",str);
    AC->getfail();
}

void work()
{
    printf("%d\n",AC->query(str));
}




int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
    while(t--)
        //while (cin >> n)
    {
        init();
        work();
    }
    return 0;

}
