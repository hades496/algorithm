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
#define tr(x,y) 1000*(x)+(y)
typedef long long LL;
using namespace std;
const LL N = 1000005;
const LL MOD = 1e9+7;
int n,ans;
string words[N];

void init()
{
    int i;
    for(i=0;i<n;i++)
    {
        cin >> words[i];
    }
}
struct Node
{
    int flag,tot;
    int next[26];
} Trie[N];

string sta;
void go(int t)
{
    for(int i=0;i<26;i++)
        if(Trie[t].next[i])
        {
            go(Trie[t].next[i]);
            Trie[t].tot+=Trie[Trie[t].next[i]].tot;
        }
    Trie[t].tot+=Trie[t].flag;
}

int found(int i)
{
    int t=0,j;
    for(j=0;j<words[i].length();j++)
    {
        int c=words[i][j]-'a';
        if(Trie[t].next[c]==0) return 0;
        t=Trie[t].next[c];
    }
    return Trie[t].tot;
}

void work()
{
    string pat,fil;
    ans=0;
    mem(Trie);
    int i,j,k,now=0;
    for(i=0;i<n;++i)
    {
        int t=0;
        for(j=0;j<words[i].length();++j)
        {
            char c=words[i][j]-'a';
            if(Trie[t].next[c]==0)
            {
                Trie[t].next[c]=++now;
            }
            t=Trie[t].next[c];
        }
        Trie[t].flag++;
    }
    go(0);
    cin >> n;
    init();
    for(i=0;i<n;i++)
    {
        cout<<found(i)<<endl;
    }

}


void prep()
{
}

int main()
{
   //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
//    int t;
//    scanf("%d\n",&t);
//    while(t--)
    while(cin >> n)
    {
        //cin >> A >> B;
        init();
        work();
    }
    return 0;
}



