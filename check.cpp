#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

int main()
{

    double st = clock();
    system("./sol.out <data.in >data.out");
    double ed = clock();
    system("./bf.out <data.in >data.ans");
    if(system("diff data.out data.ans"))
    {
        puts("Wrong Answer");
        // 程序立即退出，data.in 是发生错误的数据
        return 0;
    }
    else
        printf("Accept, 测试点 #%d, 用时 %.01fms\n", 1, ed - st);
    /*
    for(int T = 1; T <= 1e4; ++T)
    {
        system("./random.out");
        // 当前程序已经运行的 CPU 时间，Unix 下单位是 s
        double st = clock();
        system("./sol.out");
        double ed = clock();
        system("./bf.out");
        if(system("diff data.out data.ans"))
        {
            puts("Wrong Answer");
            // 程序立即退出，data.in 是发生错误的数据
            return 0;
        }
        else
            printf("Accept, 测试点 #%d, 用时 %.01fms\n", T, ed - st);
    }
    */
}
