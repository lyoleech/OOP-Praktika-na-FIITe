//
// Created by perepelicin on 03.07.19.
//

#ifndef INC_2NDLECTION_COMPLEX_H
#define INC_2NDLECTION_COMPLEX_H




class Complex
//Начало области видимости класса.
{
//Всегда явно указываем модификатор доступа к членам класса, несмотря на то что
//по умолчанию доступ и так имеет тип private. Все члены будут иметь указанный тип доступа
//вплоть до его переопределения.
private:
    double real;
    double imaginary;
    static double pi;
public:
//Ctors
//================================================================================================
//Убиваем двух зайцев - такой конструктор можно вызвать как без параметров и тогда оба значения будут
//проинициализированы нулями (то есть мы определяем конструктор по умолчанию),
//так и с двумя или одни параметром.
    explicit Complex(double real = 0, double imaginary = 0);

    //Если хотим явно указать на автоматическое создание конструктора по умолчанию.
    //Complex() = default;

    //Если хотим явно указать, что, например, нам не нужен автоматические сгенерированный
    //конструктор копирования
    //Complex() = delete;



//Объявляем конструктор копирования
    Complex(const Complex& other);
//Объявляем конструктор перемещения
    Complex(Complex&& other);

//================================================================================================


//Dtor
//================================================================================================
//Всё равно создался бы компилятором, также как и в нашем определении, пустой функцией.
    ~Complex();
//================================================================================================


//getters and setters
//Во имя  инкапсуляции объявляем геттеры и сеттеры для доступа к данным
//================================================================================================
//Если функция не меняет состояние объекта  - ВСЕГДА помечаем ее модификатором const.
    double GetReal() const;
    double GetImaginary() const;
    void SetReal(const double& value);
    void SetImaginary(const double &value);
//================================================================================================


//Функции работы с нашим классом.
//==========================================================================================
    double Magnitude() const noexcept;
    double Norm() const noexcept;
//==========================================================================================


//Перегруженные операции, которые являются членами класса.
//==========================================================================================
    Complex& operator = (Complex&& other);

    Complex& operator = (const Complex& other);
    Complex& operator = (const double &value);

    Complex& operator *= (const double &value);
    Complex& operator *= (const Complex& other);

    Complex& operator /= (const double &value);
    Complex& operator /= (const Complex& other);

    Complex& operator += (const double &value);
    Complex& operator += (const Complex& other);

    Complex& operator -= (const double &value);
    Complex& operator -= (const Complex& other);

    //Запрещаем неявные приведения к double
    explicit operator double () const;
//==========================================================================================

//friend example
//bad practice
//==========================================================================================
friend double ISeeAnythingFromThisClass(const Complex& toSee);
//==========================================================================================
//Не забываем в конце объявления всех членов закрывать объявление класса точкой с запятой.
};


//Объявление функций, не являющихся функциями-членами.
//==========================================================================================

//Операторы, не являющиеся членами класса.
//==========================================================================================
Complex operator+(const Complex& leftOperand, const Complex& rightOperand);
Complex operator+(const Complex& leftOperand, const double& rightOperand);
Complex operator-(const Complex& leftOperand, const Complex& rightOperand);

Complex operator*(const Complex& leftOperand, const Complex& rightOperand);
Complex operator*(const double& leftOperand, const Complex& rightOperand);
Complex operator*(const Complex& leftOperand, const double& rightOperand);

Complex operator/(const Complex& leftOperand, const Complex& rightOperand);
Complex operator/(const double& leftOperand, const Complex& rightOperand);
Complex operator/(const Complex& leftOperand, const double& rightOperand);

std::ostream& operator << (std::ostream& stream, const Complex& toOutput);
std::istream& operator >> (std::istream& stream, Complex& toInput);
//==========================================================================================

//==========================================================================================




//Информация по автоматические генерируемым методам класса (С++11)
//1.Default constructor if no other constructor is explicitly declared.
//2.Copy constructor if no move constructor and move assignment operator are explicitly declared.
//If a destructor is declared generation of a copy constructor is deprecated (C++11, proposal N3242 [2]).
//3.Move constructor if no copy constructor, copy assignment operator, move assignment operator and destructor are explicitly declared.
//4.Copy assignment operator if no move constructor and move assignment operator are explicitly declared.
//If a destructor is declared, generation of a copy assignment operator is deprecated.
//5.Move assignment operator if no copy constructor, copy assignment operator, move constructor and destructor are explicitly declared.
//6.Destructor

#endif //INC_2NDLECTION_COMPLEX_H
