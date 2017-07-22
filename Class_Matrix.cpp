/*
Written by Hades on 15th, July, 2017
This program is open-source and non-commercial
Please leave this paragraph if you copy the code
And give me the least amount of respect
Thank you for your cooperation

Overload operator:
>>, <<, +, -, *,[]

constructor:
matrix()
matrix(vector<vector<double> > mat)
matrix(double **a,size_t n,size_t m)

function:
rank() 矩阵的秩
*/

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
#include<set>
#define mem(f) memset(f,0,sizeof(f))
typedef long long LL;
using namespace std;
const int N = 1005;
int n,ans=50;
string str;
//vector<vector<int> > matrix;

template <class T>
class matrix
{
private:
    int Row,Col;
    const double EPS = 1e-6;
    vector<vector<T> > data;
    static int cmp(vector<T> a,vector<T> b)
    {
        int i=0;
        while(a[i]==b[i]&&i<a.size()&&i<b.size())i++;
        if(i==a.size()||i==b.size())return 0;
        return a[i]>b[i];
    }
public:
    matrix(){}
    matrix(vector<vector<T> > mat)
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
    matrix(T **a,size_t n,size_t m)
    {
        size_t i,j;
        Row=n;Col=m;data.clear();
        for(i=0;i<n;i++)
        {
            vector<T> temp; temp.clear();
            for(j=0;j<m;j++)
                temp.push_back(*((T*)a + n*i + j));
            data.push_back(temp);
        }
    }
    matrix(size_t n,size_t m)
    {
        Row=n; Col=m;
        vector<double> temp;
        for(int i=0;i<m;i++) temp.push_back(0);
        for(int i=0;i<m;i++) data.push_back(temp);
    }

    vector<T> operator[](size_t i)
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
                    res.data[i][j]+=data[i][k]*mat.data[k][j];
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
            vector<T> temp;
            for(j=0;j<mat.Col;j++)
            {
                is>>t;
                temp.push_back(t);
            }
            mat.data.push_back(temp);
        }
        return is;
    }
    int rank()
    {
        vector<vector<T> > mat(data);
        int i,j,k,l,res=0;
        for(i=0;i<Row;i++)
        {
            sort(mat.begin()+i,mat.end(),&cmp);
            cout << matrix(mat);
            j=i;
            while (j<Col&&fabs(mat[i][j])<EPS)j++;
            if(j==Col) break;
            res++;
            for(k=i+1;k<Col;k++)
                if(fabs(mat[k][j])>EPS)
                    for(l=Col-1;l>=j;l--)
                        mat[k][l]=mat[k][l]*(mat[i][j]/mat[k][j])-mat[i][l];
        }
        return res;
    }
};


void init()
{
    matrix<double> mat1;
    cin>>mat1;
    cout<< mat1.rank();
}

int main()
{
    freopen("input.txt","r",stdin);
    init();
    return 0;
}
