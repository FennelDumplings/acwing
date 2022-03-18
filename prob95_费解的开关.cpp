#include <iostream>
#include <vector>

using namespace std;

const int N = 5;

int operate(vector<int>& board, const int i, const int s)
{
    // 按照 s 操作 board 的第 i 行
    for(int j = 0; j < N; ++j)
    {
        if(s >> j & 1)
        {
            // 按下 board[i] >> j
            board[i] ^= (1 << j);
            if(j > 0)
                board[i] ^= (1 << (j - 1));
            if(j < N - 1)
                board[i] ^= (1 << (j + 1));
            if(i > 0)
                board[i - 1] ^= (1 << j);
            if(i < N - 1)
                board[i + 1] ^= (1 << j);
        }
    }
}

int get1(int x)
{
    // x 的二进制中 1 的个数
    int n = 0;
    while(x > 0)
    {
        if(x & 1)
            ++n;
        x >>= 1;
    }
    return n;
}

int solve(vector<int> board, const int s)
{
    // 棋盘初始状态为 board, 第一行行动为 s，返回变为全 1 所需次数，不可行返回 -1
    int ans = get1(s);
    operate(board, 0, s);
    for(int i = 1; i < 5; ++i)
    {
        // 操作 board 的第 i 行，使得第 i - 1 行为 0
        int t = 0;
        for(int j = 0; j < N; ++j)
        {
            if((board[i - 1] >> j & 1) == 0)
                t |= (1 << j);
        }
        ans += get1(t);
        operate(board, i, t);
    }
    if(board[N - 1] != (1 << N) - 1)
        return -1;
    if(ans <= 6)
        return ans;
    else
        return -1;
}

int main()
{
    int n;
    cin >> n;
    vector<int> board(N);
    for(int k = 0; k < n; ++k)
    {
        board.assign(N, 0);
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
            {
                char ch;
                cin >> ch;
                board[i] |= ((ch - '0') << j);
            }
        int ans = -1;
        for(int s = 0; s < (1 << N); ++s)
        {
            // 第一行操作为 s
            int x = solve(board, s);
            if(x != -1 && x <= 6)
            {
                ans = x;
                break;
            }
        }
        cout << ans << endl;
    }
}
