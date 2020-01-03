//
// Created by perepelicin on 03.07.19.


#include <string>
#include <exception>
#include <array>
#include <stdexcept>
#include <iostream>

//если все очень плохо
//std::abort();


//генерация с помощью оператора throw
//перехват обработчиком catch
//блок try
void UsingOfExceptions()
{
    try {
    // ... do something ...
    }
    catch (std::exception& err) {
        // ... cleanup ...
        throw; //проброс дальше
    }

    if(2 != 2)
    {
        try
        {
            throw "World's end is here";
        }
        catch(std::string smthVeryBad)
        {

        }
    }

};



void fun()
{
    throw std::logic_error("Badly");
}

void g()
{
    int* p = new int();
    fun();
    //конечная

    //Деструктор никогда не должен бросать исключения!
    //Если во время обработки исключения возникнет еще одно исключение - конец!


    delete p;
}

void gg()
{
    try
    {
        g();
    }

        //stack unwinding закончится здесь
        //а если бы не словили - stack unwinding закончился бы вызовом terminate
        //которая вызывает abort
        //но можно std::set_terminate
    catch (const std::logic_error& error)
    {

    }

}

struct MyException: public ::std::runtime_error
    {
        using::std::runtime_error::runtime_error;
        explicit MyException(const std::string& message)
            : runtime_error(message){}
        explicit MyException(const char* message)
            : runtime_error(message){}
    };


void UsingOfSthVeryBad()
{
    throw MyException("Something bad");
}

int main()
{

//классы, наследуемые от std::exception
//    logic_error
//    invalid_argument
//    domain_error
//    length_error
//    out_of_range
//    future_error(C++11)
//    runtime_error
//    range_error
//    overflow_error
//    underflow_error
//    system_error
    try
    {
        UsingOfSthVeryBad();
    }
        //от специального к общему
    catch(const MyException& exception)
    {
        std::cerr << "Ok"<<std::endl;
        throw;
    }
    catch(const std::exception& exception)
    {
        std::cerr<<"Isn't okay"<<std::endl;
        //throw;
    }
    catch(...)
    {
        std::cerr<<"will do sth"<<std::endl;
        //throw;
    }


    //gg();

}

//void gg(){}
//void f() noexcept(g()){}


class any
{
    int a;

    any(int a) try :  a{a}
    {}
    catch(...){}
};





