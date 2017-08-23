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
typedef long long LL;
using namespace std;
const LL MOD = 12357;
int n,m,q;
int f[105][1<<7];
void init()
{
    if(n<m)swap(n,m);
}


class matrix
{
public:
    int Row,Col;
    vector<vector<LL> > data;
    matrix(){}
    matrix(vector<vector<LL> > mat)
    {
        size_t i,j;
        Row=mat.size();
        data=mat;
        Col=0;
        for(i=0;i<Row;i++)
            if(Col<mat[i].size())
                Col=mat[i].size();
        for(i=0;i<Row;i++)
            while(data[i].size()<Col)
                data[i].push_back(0);
    }
    matrix(LL **a,size_t n,size_t m)
    {
        size_t i,j;
        Row=n;Col=m;data.clear();
        for(i=0;i<n;i++)
        {
            vector<LL> temp; temp.clear();
            for(j=0;j<m;j++)
                temp.push_back(*((LL*)a + n*i + j));
            data.push_back(temp);
        }
    }
    matrix(size_t n,size_t m)
    {
        Row=n; Col=m;
        vector<LL> temp;
        for(int i=0;i<m;i++) temp.push_back(0);
        for(int i=0;i<m;i++) data.push_back(temp);
    }

    vector<LL> &operator[](size_t i)
    {
        return data[i];
    }

    matrix operator*(matrix mat)
    {
        if (Col!=mat.Row)
            cout<< "Matrix Size is wrong!" << endl;
        matrix res(Row,mat.Col);
        for(int i=0;i<res.Row;i++)
            for(int j=0;j<res.Col;j++)
                for(int k=0;k<mat.Row;k++)
                    res.data[i][j]=(res.data[i][j]+data[i][k]*mat.data[k][j]%MOD )%MOD;
        return res;
    }
    matrix operator+(matrix mat)
    {
        if (Col!=mat.Col||Row!=mat.Row)
            cout<< "Matrix Size is wrong!" << endl;
        matrix res(data);
        for(int i=0;i<res.Row;i++)
            for(int j=0;j<res.Col;j++)
                res.data[i][j]+=mat.data[i][j];
        return res;
    }
    matrix operator-(matrix mat)
    {
        if (Col!=mat.Col||Row!=mat.Row)
            cout<< "Matrix Size is wrong!" << endl;
        matrix res(data);
        for(int i=0;i<res.Row;i++)
            for(int j=0;j<res.Col;j++)
                res.data[i][j]-=mat.data[i][j];
        return res;
    }


    friend ostream& operator<< (ostream &os,matrix mat)
    {
        int i,j;
        for(i=0;i<mat.Row;i++)
        {
            for(j=0;j<mat.Col-1;j++)
                os<<mat.data[i][j]<<' ';
            os<<mat.data[i][j]<<endl;
        }
        os<<endl;
    }
    friend istream& operator>> (istream &is,matrix &mat)
    {
        int i,j,t;
        is >> mat.Row >> mat.Col;
        for(i=0;i<mat.Row;i++)
        {
            vector<LL> temp;
            for(j=0;j<mat.Col;j++)
            {
                is>>t;
                temp.push_back(t);
            }
            mat.data.push_back(temp);
        }
        return is;
    }
    matrix pow(int n)
    {
        if(n==1) return *this;
        matrix temp = pow(n/2);
        temp = temp * temp;
        if(n%2) temp = temp * *this;
        return temp;
    }
};

matrix g;
/*
using:
11
*/
void dfs(int s1,int s2,int d)
{
    if(d>m) return;
    if(d==m) g[s1][s2]+=1;
    else
    {
        dfs(s1<<1,s2<<1|1,d+1);//不放
        dfs(s1<<2|3,s2<<2|3,d+2);//横放
        dfs(s1<<1|1,s2<<1,d+1);//竖放
    }
}

void work()
{
    int i,j,k;
    g=matrix(1<<m,1<<m);
    dfs(0,0,0);
    matrix s=matrix(1,1<<m);
    s.data[0][(1<<m)-1]=1;
    s=s*g.pow(n+1);
    cout <<s[0][0] <<endl;
}


void prep()
{

}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    prep();
    //int t;
    //scanf("%d\n",&t);
    //while(t--)
    while(cin >> n >> m)
    {
        if(n==0) return 0;
        init();
        work();
    }
    return 0;
}
