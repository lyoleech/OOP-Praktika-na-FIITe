#include <iostream>

#include "Fraction.hpp"

//constructors and destructor//
Fraction::Fraction(int num, int den)
{
    if (den != 0)
    {
        numerator = num;
        denominator = den;
    }
    else
    {
        std::cout << "DENOMINATOR MUST NOT BE 0" << std::endl;
        exit(1);
    }
}

Fraction::Fraction(const Fraction& other)
{
    *this = other;
}

Fraction::Fraction(Fraction& other)
{
    numerator = other.numerator;
    other.numerator = 0;
    denominator = other.denominator;
    other.denominator = 1;
}

Fraction::~Fraction() {}

//Setters and Getters//
int Fraction::GetNumerator() const
{
    return numerator;
}

int Fraction::GetDenominator() const
{
    return denominator;
}

void Fraction::SetNumerator(const int& value)
{
    numerator = value;
}

void Fraction::SetDenominator(const int& value)
{
    denominator = value;
}

Fraction::operator double()
{
    return static_cast<double>(numerator)/static_cast<double>(denominator);
}

//перегрузка функций членов-класса//
Fraction& Fraction::operator=(const Fraction &other)
{
    numerator = other.GetNumerator();
    denominator = other.GetDenominator();
    return *this;
}

Fraction& Fraction::operator = (const int& value)
{
    numerator = value;
    denominator = 1;
    return *this;
}

Fraction& Fraction::operator *= (const int &value)
{
    numerator *= value;
    return *this;
}

Fraction& Fraction:: operator *= (const Fraction &other)
{
    numerator *= other.GetNumerator();
    denominator *= other.GetDenominator();
    return *this;
}

Fraction& Fraction::operator /= (const int& value)
{
    denominator *= value;
    return *this;
}

Fraction& Fraction:: operator /= (const Fraction &other)
{
    numerator *= other.GetDenominator();
    denominator *= other.GetNumerator();
    return *this;
}

Fraction& Fraction:: operator += (const int& value)
{
    numerator += denominator * value;
    return *this;
}

Fraction& Fraction:: operator += (const Fraction &other)
{
    numerator = numerator * other.GetDenominator() + other.GetNumerator() * denominator;
    denominator *= other.GetDenominator();
    return *this;
}

Fraction& Fraction:: operator -= (const int& value)
{
    numerator -= denominator * value;
    return *this;
}

Fraction& Fraction:: operator -= (const Fraction &other)
{
    numerator = numerator * other.GetDenominator() - other.GetNumerator() * denominator;
    denominator *= other.GetDenominator();
    return *this;
}

Fraction& Fraction:: reduction()
{
    int temporary_numerator;
    int temporary_denominator;
    
    temporary_numerator = numerator;
    temporary_denominator = denominator;
    
    while (temporary_numerator > 0 && temporary_denominator > 0)
    {
        if (temporary_numerator > temporary_denominator)
        {
            temporary_numerator %= temporary_denominator;
        }
        else
        {
            temporary_denominator %= temporary_numerator;
        }
    }
    numerator /= temporary_denominator + temporary_numerator;
    denominator /= temporary_denominator + temporary_numerator;
    return *this;
}

//перегрузка функций не членов-класса//

Fraction operator - (const Fraction& operand)//унарный минус
{
    Fraction temporary;
    temporary -= operand;
    return temporary;
}

Fraction operator + (const Fraction& operand)//унарный плюс
{
    Fraction temporary = operand;
    return temporary;
}

Fraction operator + (const Fraction& leftOperand, const int& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary += rightOperand;
    return temporary;
}

Fraction operator + (const int& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = rightOperand;
    temporary += leftOperand;
    return temporary;
}

Fraction operator + (const Fraction& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary += rightOperand;
    return temporary;
}

Fraction operator ++ (const Fraction& operand)
{
    Fraction temporary;
    temporary = operand + 1;
    return temporary;
}

Fraction operator -- (const Fraction& operand)
{
    Fraction temporary;
    temporary = operand - 1;
    return temporary;
}

Fraction operator - (const Fraction& leftOperand, const int& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary -= rightOperand;
    return temporary;
}


Fraction operator - (const int& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = rightOperand;
    temporary -= leftOperand;
    return -temporary;
}

Fraction operator - (const Fraction& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary -= rightOperand;
    return temporary;
}

Fraction operator * (const Fraction& leftOperand, const int& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary *= rightOperand;
    return temporary;
}

Fraction operator * (const int& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = rightOperand;
    temporary *= leftOperand;
    return temporary;
}

Fraction operator * (const Fraction& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary *= rightOperand;
    return temporary;
}

Fraction operator / (const Fraction& leftOperand, const int& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary /= rightOperand;
    return temporary;
}

Fraction operator / (const int& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary(leftOperand, 1);
    temporary /= rightOperand;
    return temporary;
}

Fraction operator / (const Fraction& leftOperand, const Fraction& rightOperand)
{
    Fraction temporary = leftOperand;
    temporary /= rightOperand;
    return temporary;
}

//перегрузка ввода и вывода//
std::ostream& operator << (std::ostream& stream, const Fraction& toOutput)
{
    return stream << "Numerator: " << toOutput.GetNumerator() << ' ' << "Denominator: " << toOutput.GetDenominator() << std::endl;
}

std::istream& operator >> (std::istream& stream, Fraction& toInput)
{
    int numerator;
    int denominator;
    
    stream >> numerator >> denominator;
    toInput.SetNumerator(numerator);
    toInput.SetDenominator(denominator);
    
    if (denominator != 0) return stream;
    else
    {
        std::cout << "DDENOMINATOR MUST NOT BE 0" << std::endl;
        return stream;
    }
}
