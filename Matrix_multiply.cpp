#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;
const int N = 55;
vector < vector<int> > start;
vector < vector<int> > remult;
int n,m;

vector < vector<int> > matrix_multiply(vector< vector<int> > arrA, vector< vector<int> > arrB)
{
    int rowA = arrA.size();
    int colA = arrA[0].size();
    int rowB = arrB.size();
    int colB = arrB[0].size();
    vector< vector<int> >  res;
    if (colA != rowB) return res;
    else
    {
        res.resize(rowA);
        for (int i = 0; i < rowA; ++i) res[i].resize(colB);
        for (int i = 0; i < rowA; ++i)
            for (int j = 0; j < colB; ++j)
                for (int k = 0; k < colA; ++k)
                    res[i][j] = (res[i][j] + arrA[i][k] * arrB[k][j])%100;
    }
    return res;
}

void init()
{
    int i,j,t;
    vector<int> temp;
    vector< vector<int> > temps;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&t);
        temp.push_back(t);
    }
    start.push_back(temp);
    temp.clear();
    temp.push_back(1);
    for(i=2;i<n;i++)
    {
        temp.push_back(0);
    }
    temp.push_back(1);
    for(i=1;i<=n;i++)
    {
        remult.push_back(temp);
        t = temp.back();
        temp.insert(temp.begin(),t);
        temp.erase(temp.begin()+n);
    }
}

vector< vector<int> > fastmult(vector< vector<int> > a, int times)
{
    if (times==1) return a;
    vector< vector<int> > temp = fastmult(a,times/2);
    temp = matrix_multiply(temp, temp);
    if (times%2==1)
        temp = matrix_multiply(temp,a);
    return temp;
}

void work()
{
    int i;
    vector< vector<int> > ans = matrix_multiply(start,fastmult(remult,m));
    for (i=0;i<n-1;i++)
        printf("%d ",ans[0][i]);
    printf("%d\n",ans[0][i]);

}

void outp()
{
}

void prep()
{
}

int main()
{
    freopen("input.txt","r",stdin);
    prep();
    int t;
    //scanf("%d",&t);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        work();
        outp();
    }
    return 0;
}
