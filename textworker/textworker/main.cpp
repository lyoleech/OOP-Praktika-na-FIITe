//
//  main.cpp
//  textworker
//
//  Created by Olga Chernova on 06/10/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>
#include <cassert>


#define DEBUG
#undef DEBUG
#define PRODUCTION


#define SUM(a,b)(a+b)
#define N 100
#define PRINT(a)(std::cout<<a<<std::endl)


inline int sum(const int& a, const int &b);
int main()
{

    //prepocessor

#ifdef DEBUG
    std::cout << "Debug";
#elif defined(PRODUCTION)
    std::cout<<"Product" << std::endl;
#endif

    #undef DEBUG
#ifndef DEBUG
    std::cout << "No Debug" << std::endl;
#endif

    std::cout<<SUM(2,3) << std::endl;
    //std::cout<<N++;
    PRINT(2);
    std::cout<<sum(2,3) << std::endl;
    //assert(N < 99);
    static_assert(N< 999, "Collapse");
    //int* number = new int {23.5};
    int* number = new int {23};
    std::cout<<*number<<std::endl;
    char *line1 = new char[100];
    //std::cin>>line1;
    //std::cout<<line1;
    std::cin.get(line1, 100, ' ');
    std::cout<<line1;
    int num = 10;
//    if(num < 100 && num > 9 || num % 10 == 0 ^ num >> 2 == 5)
//    {
//
//    }

    char symbol = 'a';
    switch (symbol)
    {
        case 'b' :
        {

        }
        break;

        default:
        {

        }
        break;
    }


}


//1.Выделяет память на n значений, заполняет случайными числами, выводит их,
//находит среднее арифметическое, среднее геометрическое, максимальное, минимальное значение,
//сортирует по неубыванию и невозрастанию.
//2.Переворачивает вводимые слова при вводе, при этом заменяя все гласные буквы на согласные случайным образом, до ввода слова stop
//Подсчитывает количество гласных и количество согласных букв
//3.

inline int sum(const int& a, const int &b){ return  a+b;}

