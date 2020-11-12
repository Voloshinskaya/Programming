#pragma first
#include<iostream>

int Factorial(int s);
 main()
{
    setlocale(LC_ALL, "Russian");
    int z;
    std::cout << "Введите число, фактариал которого необходимо посчитать: " << '\n';
    std::cin >> z;
    for (int s = 0; s <= z; s++)
    {
        std::cout << s << "!" << " = " << Factorial(s) << '\n';
    }
}
int Factorial(int s)
{
    int answer = 1;
    for (int i = 1; i <= s; i++)
    {
        answer = answer * i;
    }
    return answer;
}