#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#define mem(f) memset(f,0,sizeof(f))
typedef long long LL;
using namespace std;
const int N = 105;
string s,s1;
void init()
{
    cin >> s >> s1;
}

int kmp(string str,string pat)//return the position of the first char
{
    int *fail,i,j,k;
    fail = (int*)malloc((pat.length()+1)*sizeof(int));
    memset(fail,-1,(pat.length()+1)*sizeof(int));
    for(i=1;i<pat.length();i++){
        for(k=fail[i-1];k>=0&&pat[i]!=pat[k+1];k=fail[k]);
        if (pat[k+1]==pat[i]) fail[i]=k+1;
    }
    i=j=0;
    while(i<str.length()&&j<pat.length()){
        if (pat[j]==str[i]) ++i,++j;
        else if (j==0) ++i;
        else j = fail[j-1]+1;
    }
    free(fail);
    return j<pat.length()?-1:i-j;
}

int kmpN(string str,string pat) //return the caught Times
{
    int *fail,i,j,k,tot=0;
    fail = (int*)malloc((pat.length()+1)*sizeof(int));
    memset(fail,-1,(pat.length()+1)*sizeof(int));
    for(i=1;i<pat.length();i++){
        for(k=fail[i-1];k>=0&&pat[i]!=pat[k+1];k=fail[k]);
        if (pat[k+1]==pat[i]) fail[i]=k+1;
    }
    i=j=0;
    while(i<str.length()&&j<pat.length()){
        if (pat[j]==str[i]) ++i,++j;
        else if (j==0) ++i;
        else j = fail[j-1]+1;
        if(j==pat.length()) {
            tot++; j=fail[j-1]+1;
        }
    }
    free(fail);
    return tot;
}

void work()
{
    cout << kmpN(s1,s) << endl;
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
    scanf("%d\n",&t);
    while(t--)
    //while (scanf("%d%d",&n,&m)!=EOF)
    {

        init();
        work();
    }
    return 0;
}
