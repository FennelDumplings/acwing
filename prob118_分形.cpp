#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve(const int N, const int x, const int y, vector<string>& board)
{
    if(N == 1)
    {
        board[x][y] = 'X';
        return;
    }
    solve(N - 1, x, y, board);
    solve(N - 1, x, y + 2 * pow(3, N - 2), board);
    solve(N - 1, x + pow(3, N - 2), y + pow(3, N - 2), board);
    solve(N - 1, x + 2 * pow(3, N - 2), y, board);
    solve(N - 1, x + 2 * pow(3, N - 2), y + 2 * pow(3, N - 2), board);
}

int main()
{
    int N;
    vector<string> board;
    while((cin >> N) && N != -1)
    {
        int len = (int)pow(3, N - 1);
        board.assign(len, string(len, ' '));
        solve(N, 0, 0, board);
        for(int i = 0; i < len; ++i)
            cout << board[i] << endl;
        cout << "-" << endl;
    }
}
