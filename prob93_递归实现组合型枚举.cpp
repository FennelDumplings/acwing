#include <iostream>
#include <vector>

using namespace std;

const int N = 100010;
int stack[N];
int top = 0, address = 0;

int n, m;
vector<int> vec; // 被选择的

void call(int ret_addr)
{
    // 模拟计算机汇编指令 call
    // i 是参数, ret_addr 是函数返回时的地址
    int old_top = top - 1;
    stack[++top] = ret_addr; // 返回地址标号
    stack[++top] = old_top; // 在栈顶记录以前的 top 值
}

int ret()
{
    // 模拟计算机汇编指令 ret
    int ret_addr = stack[top - 1];
    top = stack[top]; // 恢复以前的 top 值
    return ret_addr;
}

void print()
{
    for(int i = 0; i < vec.size(); ++i)
        printf("%d ", vec[i]);
    puts("");
}

int main()
{
    cin >> n >> m;

    stack[++top] = 1; // 参数 1
    call(0); // dfs(1)
    while(top)
    {
        int i = stack[top - 2]; // 获取参数
        switch(address)
        {
            case 0:
                if(vec.size() == m)
                {
                    print();
                    address = ret(); // return
                    continue;
                }
                if(vec.size() + (n - i + 1) < m)
                {
                    address = ret(); // return
                    continue;
                }
                vec.push_back(i);
                stack[++top] = i + 1; // 参数 i + 1
                call(1); // 相当于 dfs(i + 1)，返回后会从 case1 继续
                address = 0;
                continue; // 返回到 while 循环开头，相当于开始新的递归
            case 1:
                vec.pop_back();
                stack[++top] = i + 1; // 参数 i + 1
                call(2); // 相当于 dfs(i + 1)，返回后会从 case2 继续
                address = 0;
                continue; // 回到 while 循环开头，相当于开始新的递归
            case 2:
                address = ret(); // 相当于原 dfs 函数结尾，执行 return
        }
    }
}


/*
void dfs(vector<int>& vec, int i, const int n, const int m)
{
    if(vec.size() == m)
    {
        for(int x: vec)
            cout << x << " ";
        cout << endl;
        return;
    }
    if(vec.size() + n - i + 1 < m)
        return;
    vec.push_back(i);
    dfs(vec, i + 1, n, m);
    vec.pop_back();
    dfs(vec, i + 1, n, m);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> vec;
    dfs(vec, 1, n, m);
}
*/
