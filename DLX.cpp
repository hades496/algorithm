/*
Written by Hades on 12th, July, 2017
This program is open-source and non-commercial
Please leave this paragraph if you copy the code
And give me the least amount of respect
Thank you for your cooperation

Input Format
n m
Matrix[n][m]

Output Format
vector of chosen Row Numbers

Input Sample
6 7
1 0 1 0 1 0 1
0 1 0 1 1 1 1
0 1 0 1 0 1 1
1 0 1 0 1 1 0
0 0 0 0 0 1 0
0 1 0 1 0 0 0

Output Sample
1 5 6

*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;

class DancingLinkX
{
private:
    DancingLinkX *Up,*Down,*Left,*Right,*Col,*_Head;
    int Row;

    void RemoveCol(DancingLinkX *C)
    {
        C->Left->Right=C->Right;
        C->Right->Left=C->Left;
        for (DancingLinkX *i=C->Down;i!=C;i=i->Down)
            for (DancingLinkX *j=i->Right;j!=i;j=j->Right)
            {
                j->Down->Up=j->Up;
                j->Up->Down=j->Down;
            }
    }
    void ResumeCol(DancingLinkX *C)
    {
        C->Left->Right=C;
        C->Right->Left=C;
        for (DancingLinkX *i=C->Down;i!=C;i=i->Down)
            for (DancingLinkX *j=i->Right;j!=i;j=j->Right)
            {
                j->Down->Up=j;
                j->Up->Down=j;
            }
    }

public:
    DancingLinkX (int Cols)
    {
        _Head = Up = Down = Left = Right = Col = this;
        if(Cols>0)
        {
            DancingLinkX *pre=_Head;
            for(int i=1;i<=Cols;i++)
            {
                DancingLinkX *NewCol=new DancingLinkX(0);
                NewCol->Left=_Head->Left;
                NewCol->Right=_Head;
                NewCol->Left->Right=NewCol;
                NewCol->Right->Left=NewCol;
                _Head->Left=NewCol;
            }
        }
    }

    void AppedLine(vector<int> Value,int RowN)
    {

        if (Value.empty()) return;
        DancingLinkX *FirstNode=NULL;
        DancingLinkX *PreNode=FirstNode;
        DancingLinkX *HeadNode=_Head;

        for(int i=0;i<Value.size();i++)
        {
            HeadNode=HeadNode->Right;
            if(Value[i]==1)
            {
                DancingLinkX *Node=new DancingLinkX(0);
                if(FirstNode)
                {
                    Node->Left=FirstNode->Left;
                    Node->Right=FirstNode;
                    Node->Left->Right=Node;
                    Node->Right->Left=Node;
                }
                else
                {
                    FirstNode = Node;
                }
                Node->Down = HeadNode;
                Node->Up = HeadNode->Up;
                Node->Up->Down = Node;
                Node->Down->Up = Node;

                Node->Row=RowN;
                Node->Col=HeadNode;
                PreNode = Node;
            }
        }
    }

    vector<int> Dance()
    {
        DancingLinkX *C1=_Head->Right;
        if (C1==_Head)
        {
            vector <int > res;
            res.push_back(-1);
            return res;
        }
        vector <int> ans;
        ans.clear();
        RemoveCol(C1);
        for(DancingLinkX *i=C1->Down;i!=C1;i=i->Down)
        {
            ans.push_back(i->Row);
            for(DancingLinkX *j=i->Right;j!=i;j=j->Right)
            {
                RemoveCol(j->Col);
            }
            vector<int> temp=Dance();
            if (!temp.empty())
            {
                if (temp.back()>0) ans.insert(ans.end(),temp.begin(),temp.end());
                return ans;
            }
            for(DancingLinkX *j=i->Left;j!=i;j=j->Left)
            {
                ResumeCol(j->Col);
            }
            ans.pop_back();
        }
        ResumeCol(C1);
        return ans;
    }
};

vector<vector<int> > G;
int n,m;
void init()
{
    for(int i=0;i<n;i++)
    {
        vector<int> temp;
        for(int j=0;j<m;j++)
        {
            int t;
            scanf("%d",&t);
            temp.push_back(t);
        }
        G.push_back(temp);
    }
}

void work()
{
    DancingLinkX dancer(m);
    for(int i=0;i<n;i++)
    {
        dancer.AppedLine(G[i],i+1);
    }
    vector<int> ans = dancer.Dance();
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
            printf("%d ",ans[i]);
}

int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    //scanf("%d\n",&t);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
