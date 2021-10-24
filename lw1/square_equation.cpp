#include <cstdio>
#include <cmath>

int main()
{
    std::puts("please enter a and b and c for `ax^2 + bx + c = 0:`");

    float a = 0, b = 0, c = 0, x1, x2;
    std::scanf("%f %f %f", &a, &b, &c);

    float D = b * b - 4 * a * c;
    if (D < 0)
    {
        std::printf("solution doesn't exist");
        return 0;
    }
    else
    {
        x1 = (-b + std::sqrt(D)) / 2 / a;
        x2 = (-b - std::sqrt(D)) / 2 / a;

        if (x1 == x2)
            std::printf("solution: x = %5.2f\n", x1);
        else
            std::printf("solution: x1 = %5.2f, x2 = %5.2f\n", x1, x2);
    }
}
