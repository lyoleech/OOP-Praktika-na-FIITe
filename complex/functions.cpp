#include <iostream>
#include <array>


//int main(int argc, char** argv);

//headers and #IFDEF with #pragma once


//vla
void Show()
{
    int n;
    std::cin>>n;
    //int array[n]; //VLA array
    int* arrayPtr = new int[n];
    delete [] arrayPtr;
    //if you do
    // delete arrayPtr; //it's undefined behaviour
}


//Объявление функции и ее определение.
//=============================================================================================
//объявление
int Sum(int a = 0, int b = 0);

//объявление вместе с определением
int Abs(int a)
{
    return a >= 0 ? a : -a;
}


//объявление, затем определение
int Square(int x);
int Square(int x)
{
    return x*x;
}


//пример перегрузки функций
//Статический полиморфизм.
//Полиморфизм (множество форм) - способность некоторой сущности оперировать с разными типами данных.
//Статический - времени компиляции.
//Динамический - во время исполнения программы.
//Перегрузка функции - ее переопределение для работы с разными типами данных.
//=============================================================================================
double Volume(double x, double y, double z)
{

}

double Volume(double x, double square)
{

}

double Volume(double radius)
{
    return 4./3. * 3.14159*radius*radius*radius;
}
//=============================================================================================

//Шаблоны
template <typename Type, typename PredefinedType = int>
Type absTyped(Type x)
{
    PredefinedType y = x;
    return x >= 0 ? x : -x;
};


template <typename TType, int n>
void DefineArray()
{
    std::array<TType, n> arr;
};

void UsingOfTemplates ()
{
    double y = 12;
    absTyped<double>(y);
    absTyped(y);
    absTyped<double, double>(y);
};

