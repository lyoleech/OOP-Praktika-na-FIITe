//
// Created by perepelicin on 03.07.19.
//

#include <iostream>
#include "Complex.h"

int main(int argc, char** argv)
{
    //Complex cmplx = 1.1; // не можем так написать, так как конструктор объявлен как explicit

    Complex complex1 = Complex();//вызов конструктора по умолчанию, который в нашем случае является перегруженным параметризованным конструктором
    Complex complex2; //также вызов конструктора по умолчанию
    Complex funComplex(); //объявление функции, а не конструирование экземпляра класса


    Complex complex3(-2, 1);
    Complex complex4{1, -1}; //конструирование экземпляра класса списком инициализации приводи к вызову допустимого конструктора. C++11 style.

    //Доступ к члену экземпляра класса (методу или переменной) производится с помощью операции точки.
    complex2.SetReal(22);
    //Указатель на объект типа Complex
    Complex* complexPtr1 = new Complex(4,3);
    //Доступ к объекту, на который указывает указатель
    complexPtr1->SetReal(2);
    (*complexPtr1).SetReal(3);
    //Тоже указатель, созданные в стиле С++ 11
    Complex* complexPtr2 = new Complex{4,3};

    Complex complex5(complex1);


    //!!!Случаи использования конструктора копирования
    //Конструктор копирования вызывается всякий раз, когда создается новый объект,
    //и для его инициализации берется значение существующего объекта того же типа. Это
    //происходит в нескольких ситуациях.
    //1.Новый объект инициализируется существующим объектом этого класса.
    Complex toUseCopyCtor1(complex1); // вызывает Complex(const Complex &)
    Complex toUseCopyCtor2 = complex1; // вызывает Complex(const Complex &)
    Complex  toUseCopyCtor3 = Complex(complex1); // вызывает Complex(const Complex&)
    Complex* ptrToUseCopyCtor = new Complex(complex1);// вызывает StringBad(const StringBad &)
    //2.Каждый раз когда вы передаете объект в функцию или возвращаете его из нее по значению.
    auto lambda1 = [complex1]() -> void {std::cout<<complex1;};
    lambda1();
    auto lambda2 = [complex1]() -> Complex {return complex1 + 1.1; };
    lambda2();

    //Умолчательный конструктор копирования выполняет ПОВЕРХНОСТНОЕ копирование.

    Complex cmplx1(2,3);
    Complex cmplx2(4,99);
    //Работаем как с стандартным типом
    std::cout<<static_cast<double>(cmplx1) << std::endl;
    std::cout<<(cmplx1 + 1 - cmplx2 + cmplx1*cmplx2 + cmplx2/cmplx2);

    //Не надо вызывать деструктор явно (во время run-time, при смерти объекта он все равно вызовется еще раз),
    //хотя сделать это можно.
    //complex1.~Complex();

    delete complexPtr1;
    delete complexPtr2;
    delete ptrToUseCopyCtor;



    //why do we need move
//    template<class T>
//    void swap(T& a, T& b)
//    {
//        const T tmp = a;
//        a = b;
//        b = tmp;
//    };

    //template<class T>
//    void swap(T& a, T& b)
//    {
//        T tmp = std::move(a);
//        a = std::move(b);
//        b = std::move(tmp);
//    }
    //Всегда форсим мувом.
    Complex cmplxx(std::move(cmplx2));


    //lvalue and rvalue
//    std::string var {"Cambridge"};
//    std::string f();
//    std::string& r1 {var}; // lvalue reference, bind r1 to var (an lvalue)
//    std::string& r2 {f()}; // lvalue reference, error : f() is an rvalue
//    std::string& r3 {"Princeton"}; // lvalue reference, error : cannot bind to temporar y194
//
//    std::string&& rr1 {f()}; // rvalue reference, fine: bind rr1 to rvalue (a temporary)
//    std::string&& rr2 {var}; // rvalue reference, error : var is an lvalue
//    std::string&& rr3 {"Oxford"}; // rr3 refers to a temporar y holding "Oxford"


}


//Немного по namespace
//=============================================================================================
//способ организации вводимых создателем библиотеки типов
namespace MyLib
{
    class GoodBye{};
    class Bye{};
    //sth else
};

namespace YourLib
{
    class Hi{};
    class Bye{};
    //sth else
};

void ExampleOfUsingNamespaces()
{
    using namespace MyLib;
    using namespace YourLib;
    //Bye a; //here is the error
}
//=============================================================================================