#include <cstdio>

int main()
{
    std::puts("please enter a and b for `ax + b = 0:`");

    int a = 0, b = 0;
    std::scanf("%d %d", &a, &b);

    int x = -b / a;
    std::printf("solution: %5d\n", x);
}