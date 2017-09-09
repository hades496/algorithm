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
string str,pat;
int n,ans;
void init()
{
    cin >> str >> pat;
}

vector<int> getNext(string str)
{
    int len = str.length(),i,k;
    vector<int> next(len,-1);
    for(i=1;i<len;i++)
    {
        for(k=next[i-1];k>=0&&str[i]!=str[k+1];k=next[k]);
        if(str[k+1]==str[i]) next[i]=k+1;
    }
    return next;
}

int kmp(string str,string pat)
{
    int len = str.length(),plen=pat.length(),i,k;
    vector<int> next=getNext(pat);
    for(i=0,k=-1;i<len;i++)
    {
        while(k>=0&&str[i]!=pat[k+1]) k=next[k];
        if(str[i]==pat[k+1]) k++;
        if(k==plen-1) return i-plen+1;
    }
    return -1;
}

vector<int> kmpN(string str,string pat)
{
    int len = str.length(),plen=pat.length(),i,k;
    vector<int> next=getNext(pat);
    vector<int> res;
    for(i=0,k=-1;i<len;i++)
    {
        while(k>=0&&str[i]!=pat[k+1]) k=next[k];
        if(str[i]==pat[k+1]) k++;
        if(k==plen-1)
        {
            res.push_back(i-plen+1);
            k=next[k];
        }
    }
    return res;
}

void work()
{
    cout << kmpN(pat,str).size() << endl;
}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
    while(t--)
    //while (cin >>str >> pat)
    {
        init();
        work();
    }
    return 0;
}




