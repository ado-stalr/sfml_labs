#include <iostream>

int main()
{
    // в цикле от 1 до 100

    // начальное действие: объявить переменную num, равную 1
    // условие: пока num меньше или равно 100
    // после каждого шага (итерации) цикла добавляем к num единицу
    for (int num = 1; num <= 100; num += 1)
    {

        if (num % 3 == 0 && num % 5 == 0) //  - если число кратно и 3, и 5, вывести FizzBuzz
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3 == 0) //  - иначе если число кратно 3, вывести Fizz
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5 == 0) //  - иначе если число кратно 5, вывести Buzz
        {
            std::cout << "Buzz" << std::endl;
        }
        else //  - иначе вывести число
        {
            std::cout << num << std::endl;
        }
    }
}