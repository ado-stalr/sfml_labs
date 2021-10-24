#include <cstdio>

int main()
{
    std::puts("please enter a and b for `ax + b = 0:`");

    float a = 0, b = 0;
    std::scanf("%f %f", &a, &b);

    float x = -b / a;
    std::printf("solution: %5.2f\n", x);
}