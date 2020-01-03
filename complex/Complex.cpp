//
// Created by perepelicin on 03.07.19.
//


//std includes
//==========================================================================================
#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>
//==========================================================================================

//my includes
//==========================================================================================
#include "Complex.h"
//==========================================================================================

//инициализация статической переменной
//она хранится в отдельной области памяти, поэтому ее не получится инициализировать внутри самого класса
//или внутри его конструктора.
//==========================================================================================
double Complex:: pi = 3.14159265359;
//==========================================================================================

//realization of ctors
//==========================================================================================
//Значения параметров по умолчанию нужно указывать ТОЛЬКО в объявлении
//попытка указания их в определении приведет к ошибке

//Конструктор по умолчанию в случае, если он не определен явным образом вставляется компилятором
//в таком виде Complex(){}
Complex::Complex(double real, double imaginary) : real{real}, imaginary{imaginary}
{

}

//copy ctor
Complex::Complex(const Complex &other)
{
    //It helps us to deeply understand when copy ctor is used
    //std::cout << "I'm copy ctor!";
    *this = other;
}


//move ctor
Complex::Complex(Complex&& other)
{
    real = other.real, other.real = 0;
    imaginary = other.imaginary, other.imaginary = 0;
    //To check was move completed
    std::cout<<std::endl<<"Here is move"<<std::endl;
}
//==========================================================================================


//realization of dtors
//==========================================================================================
Complex::~Complex()
{
    //Не делает ничего, так как класс не использует динамическую память и
    //какие либо ресурсы, которое небходимо освободить (файлы, устройства.)
}
//==========================================================================================


//getters and setters
//==========================================================================================
//Не забываем и здесь явно указать, что функция не меняет состояние объекта.
double Complex::GetImaginary() const
{
    return imaginary;
}


double Complex::GetReal() const
{
    return real;
}

void Complex::SetImaginary(const double& value)
{
    imaginary = value;
}

void Complex::SetReal(const double &value)
{
    real = value;
}
//==========================================================================================

//Функции для работы с классом.
//==========================================================================================
double Complex::Magnitude() const noexcept
{
    return sqrt(real*real + imaginary*imaginary);
}

double Complex::Norm() const noexcept
{
    auto x = Magnitude();
    return x * x;
}
//==========================================================================================

//Перегруженные операторы, являющиеся членами класса.
//==========================================================================================
Complex& Complex::operator=(const Complex &other)
{
    real = other.GetReal();
    imaginary = other.GetImaginary();
    return *this;//возвращает ссылку для многократного присваивания 
}


//Принимаем не константную ссылку, так как объект other должен изменить значение
Complex& Complex::operator = (Complex&& other)
{
    std::swap(real, other.real);
    std::swap(imaginary, other.imaginary);
    return *this;
}

Complex& Complex::operator = (const double& value)
{
    real = value;
    imaginary = 0;
    return *this;
}

Complex& Complex::operator *= (const double &value)
{
    real *= value;
    imaginary *= value;
    return *this;
}

Complex& Complex::operator*=(const Complex &other)
{
    const double temporary = real * other.GetReal() - imaginary * other.GetImaginary();
    imaginary = real * other.GetImaginary() + imaginary * other.GetReal();
    real = temporary;
    return *this;
}


Complex& Complex::operator /= (const double &value)
{
    real /= value;
    imaginary /= value;
    return *this;
}


Complex& Complex::operator /= (const Complex &other)
{
    const double temporary = real * other.real + imaginary * other.imaginary;
    const double norm = other.Norm();
    imaginary = (imaginary*other.GetReal() - real*other.GetImaginary()) / norm;
    real = temporary / norm;
    return *this;
}

Complex& Complex::operator += (const double &value)
{
    real += value;
    return *this;
}

Complex& Complex::operator += (const Complex &other)
{
    real += other.real;
    imaginary += other.imaginary;
    return *this;
}


Complex& Complex::operator -= (const double &value)
{
    real -= value;
    return *this;
}

Complex& Complex::operator -= (const Complex &other)
{
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
}

Complex:: operator double () const
{
    return real;
}
//==========================================================================================

//Операторы, не являющиеся членами класса.
//==========================================================================================
std::ostream& operator << (std::ostream& stream, const Complex& toOutput)
{
    return stream << "Real part : " << toOutput.GetReal() << ' ' << "Imaginary part : " << toOutput.GetImaginary() << std::endl;
}


std::istream& operator >> (std::istream& stream, Complex& toInput)
{
    int real;
    int imaginary;
    stream >> real >> imaginary;

    toInput.SetReal(real);
    toInput.SetImaginary(imaginary);
}


Complex operator+(const Complex& leftOperand, const Complex& rightOperand)
{
    Complex temporary = leftOperand;
    temporary += rightOperand;
    return temporary;
}

Complex operator+(const Complex& leftOperand, const double& rightOperand)
{
    Complex temporary = leftOperand;
    temporary += rightOperand;
    return temporary;
}

Complex operator-(const Complex& leftOperand, const Complex& rightOperand)
{
    Complex temporary = leftOperand;
    temporary -= rightOperand;
    return temporary;
}

Complex operator / (const Complex& leftOperand, const Complex& rightOperand)
{
    Complex temporary = leftOperand;
    temporary /= rightOperand;
    return temporary;
}

Complex operator / (const double & leftOperand, const Complex& rightOperand)
{
    Complex temporary {leftOperand};
    temporary /= rightOperand;
    return temporary;
}

Complex operator / (const Complex& leftOperand, const double& rightOperand)
{
    Complex temporary {leftOperand};
    temporary /= rightOperand;
    return temporary;
}

Complex operator * (const Complex& leftOperand, const Complex& rightOperand)
{
    Complex temporary = leftOperand;
    temporary *= rightOperand;
    return temporary;
}


Complex operator*(const double& leftOperand, const Complex& rightOperand)
{
    Complex temporary = rightOperand;
    temporary *= leftOperand;
    return temporary;
}

Complex operator*(const Complex& leftOperand, const double& rightOperand)
{
    Complex temporary = leftOperand;
    temporary *= rightOperand;
    return temporary;
}
//==========================================================================================

//friend's functions implementation
//==========================================================================================
double ISeeAnythingFromThisClass(const Complex& toSee)
{
    std::cout<< toSee.real;
};
//==========================================================================================
