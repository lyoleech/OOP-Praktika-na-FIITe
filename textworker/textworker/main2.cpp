//
// Created by perepelicin on 30.06.19.
//

#include <cstdio>
#include <cstring>
#include <vector>
#include "TextWorker.h"


//functions
//============================================================================================
void Void();
void Void(){return;}
int Sum(int a, int b) { return  a+b;}
//int Sum(const int a, int b) { return  a+ b;} //error
int Max(int a, int b) { return a > b ? a : b;}
int MaxWithIf(int a, int b) {if(a > b) {return a;} else {return b;}}
int MaxWithIfF(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

inline int SumInline(int a, int b)
{
    return a + b;
}

constexpr int Square(int value)
{
    return value*value;
}


template <typename Type>
inline Type Sum(Type a, Type b) { return a + b;}

template <typename LeftOperandType, class RightOperandType, typename ResultOperandType>
ResultOperandType Sum(LeftOperandType a, RightOperandType b, double epsilon = 0.000000001)
{
    return a + b + epsilon;
};
//============================================================================================


//arrays and pointers
//============================================================================================
void UsingOfArraysAndPointers()
{
    int *value = new int (2);
    constexpr size_t size = 5;
    int intArray[size];
    for(size_t index = 0; index < size; index++)
    {
        intArray[index] = static_cast<int>(index);
        //is it narrowing conversion
    }
    for(const auto& element : intArray)
    {
        std::cout << element;
    }
    int *array  = new int[5];

    const int* p1 = intArray; // указатель на кон// станту
    //*p1 = 2; //error
    int* const p2 = array;//константный указатель
    //p2 = p1; //error
    p1 = p2;

    delete[] array;



    int a = 2;
    int b = 3;
    //value = a;
    int& refA = a;
    refA = b;
    const int& constRefA = a;
    constRefA = b;
}
//============================================================================================

//casts
//============================================================================================
template <typename Target, typename Source>
Target narrowCast(Source value)
{
    auto castedValue = static_cast<Target>(value);
    if(static_cast<Source>(castedValue) != value)
    {
        //error
    }
    return castedValue;
};


void Casts()
{
    //static_cast<>
    //const_cast<>
    //dynamic_cast<>
    //reinterpret_cast<>
    int number = static_cast<int>(9.3);
    int num = int(9.3);//C-style cast
    double doubleNum = narrowCast<double>(number);
    number = narrowCast<int>(9.3); // error
    //IODevice* handle = reinterpret_cast<IODevice*>(0Xff00);
    class A { public:void a(){}};
    const auto* aValue = new A();
    //aValue->a(); //error
    (const_cast<auto *>(aValue))->a();
}
//============================================================================================


//using of enum
//============================================================================================
enum {ASM, AUTO, BREAK};
enum Keyword {ASM, AUTO, BREAK};
enum StartFromNine {NINE = 9, TEN, ELEVEN};
enum FakeKeyword {ASM, AUTO, BREAK};

void EnumUsing()
{
    Keyword keyword = Keyword::ASM;
    keyword = static_cast<Keyword>(1);
    //keyword = FakeKeyword::ASM; //error
    //keyword = 1; //error
    int numberOfAsm = ASM;

    int modeOfusing = 1;//get from somewhere
    switch(modeOfusing)
    {
        case Keyword::ASM :
        {

        }
        break;

        case Keyword::AUTO:
        {

        }
        break;


        default:
        {

        }
        break;
    }
}
//============================================================================================


//aliases
//============================================================================================
typedef unsigned int unsi;
using unsii = unsigned  int;
void AliasesUsing()
{
    unsii num = 2;
    unsi secondNum = 12;

    using vecInt = std::vector<int>;
    using matrixInt = std::vector<std::vector<int>>;
    using intPointer = int*;
}
//============================================================================================


int main()
{
//    using namespace std;
//    TextWorker textWorker;
//    textWorker.Output();
    std::cout<<sizeof(bool);


//    auto aa = new char*[1];
//    aa[0] = new char[5];
//    strcpy(aa[0], "aaaaa");
//    std::cout << aa[0];
//    fu(aa);
//    std::cout << aa[0];
}



