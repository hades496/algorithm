//数位DP模板
//f[当前位][约束]
int dfs(int pos,约束,bool limit)
{
    int tmp;//计数
    if (pos == -1) \\边界
      return 满足约束？;\\满足条件返回1，否则返回0
    if( !limit && 状态已经求出？) return f[pos][约束];
    for(int i = 0; i <= (limit ? a[pos] : 9); i++)//枚举当前位
    tmp+=dfs(pos-1, 更新约束, limit && i == a[pos]);
    if(!limit) f[pos][约束] = tmp;//保存状态
    return tmp;
}

LL solve(LL x)
{
    if(x<0) return 0;
    int pos = 0;
    while(x)//整数拆分
    {
        a[pos++] = x % 10;
        x /= 10;
    }
    int tmp=dfs(pos - 1, 约束, true);
    return tmp;
}
