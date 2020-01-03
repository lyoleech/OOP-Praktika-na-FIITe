//  string
//
//  Created by Olga Chernova on 05/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction{
private:
    int numerator;
    int denominator;

public:
//ctors and detors//
    explicit Fraction(int num = 0, int den = 1);
    Fraction(const Fraction &other);
    Fraction(Fraction &other);
    ~Fraction();


//Setters and Getters//
    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(const int& value);
    void SetDenominator(const int& value);
    
//приведение к типу double//
    operator double();

//перегрузка функций членов-класса//
    Fraction& operator = (const Fraction &other);
    Fraction& operator = (const int &value);
    Fraction& operator *= (const int &value);
    Fraction& operator *= (const Fraction &other);
    Fraction& operator /= (const int &value);
    Fraction& operator /= (const Fraction &other);
    Fraction& operator += (const int& value);
    Fraction& operator += (const Fraction &other);
    Fraction& operator -= (const Fraction &other);
    Fraction& operator -= (const int& other);
    

    Fraction& reduction ();
    
};

//перегрузка функций не членов-класса//
Fraction operator - (const Fraction& operand);
Fraction operator + (const Fraction& operand);

Fraction operator + (const Fraction& leftOperand, const Fraction& rightOperand);
Fraction operator + (const Fraction& leftOperand, const int& rightOperand);
Fraction operator + (const int& leftOperand, const Fraction& rightOperand);

Fraction operator ++ (const Fraction& operand);
Fraction operator -- (const Fraction& operand);

Fraction operator - (const Fraction& leftOperand, const int& rightOperand);
Fraction operator - (const int& leftOperand, const Fraction& rightOperand);
Fraction operator - (const Fraction& leftOperand, const Fraction& rightOperand);

Fraction operator * (const Fraction& leftOperand, const int& rightOperand);
Fraction operator * (const int& leftOperand, const Fraction& rightOperand);
Fraction operator * (const Fraction& leftOperand, const Fraction& rightOperand);

Fraction operator / (const Fraction& leftOperand, const int& rightOperand);
Fraction operator / (const int& leftOperand, const Fraction& rightOperand);
Fraction operator / (const Fraction& leftOperand, const Fraction& rightOperand);


std::ostream& operator << (std::ostream& stream, const Fraction& toOutput);
std::istream& operator >> (std::istream& stream, Fraction& toInput);

#endif /* FRACTION_H */
