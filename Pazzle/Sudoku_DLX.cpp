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
const int N = 200005;
const int M = 1000005;

const LL INF=0x3f3f3f3f;
int board[10][10];

class DancingLinkX
{
private:
    DancingLinkX *Up,*Down,*Left,*Right,*Col,*_Head;
    int Row,ColNum;
    void RemoveCol(DancingLinkX *C)
    {
        C->Left->Right=C->Right;
        C->Right->Left=C->Left;
        for (DancingLinkX *i=C->Down;i!=C;i=i->Down)
            for (DancingLinkX *j=i->Right;j!=i;j=j->Right)
            {
                j->Down->Up=j->Up;
                j->Up->Down=j->Down;
                j->Col->ColNum--;
            }
        C->ColNum--;
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
                j->Col->ColNum++;
            }
        C->ColNum++;
    }

public:
    DancingLinkX (int Cols)
    {
        _Head = Up = Down = Left = Right = Col = this;
        ColNum = 0;
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
        DancingLinkX *HeadNode=_Head;

        for(int i=0;i<Value.size();i++)
        {
            HeadNode=HeadNode->Right;
            if(Value[i]==1)
            {
                HeadNode->ColNum++;
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
            }
        }
    }

    vector<int> Dance()
    {
        DancingLinkX *leastC=_Head->Right;
        DancingLinkX *C1=_Head->Right;
        for(;C1!=_Head;C1=C1->Right)
        {
            if (leastC->ColNum>C1->ColNum)
                leastC=C1;
        }
        C1=leastC;
        vector <int> ans;
        if (C1==_Head)
        {
            ans.push_back(-1);
            return ans;
        }
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
    int i,j;
    for(i=1;i<=9;i++)
    {
        for(j=1;j<=9;j++)
            scanf("%d",&board[i][j]);
    }

}


void setrow(int i, int j, int k)
{
    int id = (i - 1) * 9 + j; // 表示第i行第j列格子的编号
	int pid = (id - 1) * 9 + k - 1; // 表示该格子填写k所对应的方案编号
	// 约束条件1 - 对应第1~81列
	// 第(i-1)*9+k列表示第i行存在数字k
	G[ pid ][(i - 1) * 9 + k-1] = 1;

	// 约束条件2 - 对应第82~162列
	// 第81+(j-1)*9+k列表示第j列存在数字k
	G[ pid ][81 + (j - 1) * 9 + k-1] = 1;

	// 约束条件3 - 对应第163~243列
	// 第162+(t-1)*9+k列表示第t个九宫存在数字k
	int t = ((i - 1) / 3 * 3 + (j - 1) / 3) + 1;
	G[ pid ][162 + (t - 1) * 9 + k-1] = 1;

	// 约束条件4 - 对应第244~324列
	// 第243+id列表示第i行第j列填写有数字
	G[ pid ][243 + id-1] = 1;

}

void create()
{
    G.clear(); // 设置01矩阵为729*324的矩阵，初始化为全0
	int i,j,k;
	vector <int> temp(324,0);
	for(i=0;i<729;i++)
        G.push_back(temp);
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			if (board[i][j] == 0)
				for (k=1;k<=9;k++)	// 枚举可能填写的9个数字
					setrow(i, j, k);
			else
				setrow(i, j, board[i][j]);
}

void work()
{
    create();
    DancingLinkX dancer(324);
    for(int i=0;i<G.size();i++)
    {
        dancer.AppedLine(G[i],i);
    }
    vector<int> ans = dancer.Dance();
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
    {
        //printf("ans=%d:%d %d -> %d\n",ans[i],ans[i]/9/9+1,ans[i]/9%9+1,ans[i]%9+1);
        G[ans[i]/9/9+1][ans[i]/9%9+1]=ans[i]%9+1;
    }
    int i,j;
    for(i=1;i<=9;i++)
        for(j=1;j<=9;j++)
            printf("%d%s",G[i][j],j==9?"\n":" ");
}

int main()
{
    //makedata();
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    scanf("%d\n",&t);
    while(t--)
    //while (scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
