//
// Created by perepelicin on 04.07.19.
//
#include <string>
#include <ctime>
#include <memory>
#include <list>
#include <iostream>
#include <vector>


class Date{};

//base class
//superclass
class Employee {
    std::string first_name , family_name;
    char middle_initial;
    Date hiring_date;
    short department;
public:
    Employee(const std::string& name = "Robby") : first_name{name}
    {
        //std::cout<<"Employee was created"<<std::endl;
    };

    ~Employee()
    {
        //std::cout<<"Employee was destroyed"<<std::endl;
    }
    void print() const
    {
        std::cout<<"I'm an employee!" << std::endl;
    };
};

//subclass
//derived class
class Manager : public Employee {
    std::list<Employee*> group; //являющиеся менеджерами рабочие
    short level;
public :
    Manager(const std::string& name = "Robby", int dept = 12, int lvl = 1) : Employee{name}
    {
        //std::cout << "Manager was created" << std::endl;
    };


    ~Manager()
    {
        //std::cout << "Manager was destroyed" << std::endl;
    }

    void print() const
    {
        std::cout << "I am a manager";
    }
};

//После того как Manager становится подтипом класса Employee класс Manager может быть использован
//в любом выражении, где до этого мы могли использовать класс employee.

void g(Manager manager, Employee employee)
{
    Employee* ptrEmployee = &manager; // работаем с паматью через вспомогательный указалтель птрраб
    //Manager* ptrManager = &employee; // error
    Manager* ptrManager = static_cast<Manager*> (ptrEmployee); // расширили облатсь видмиости, приходим и говорим дай мне все
}


void UsingOfNoneVirtualFunctions()
{
    std::unique_ptr<Employee> employee1 (new Employee());
    std::unique_ptr<Employee> employee2 (new Manager());
    employee2->print(); //вызовется функция print класса employee
}





class RightEmployee {
    std::string first_name , family_name;
    char middle_initial;
    Date hiring_date;
    short department;
public:
    RightEmployee(const std::string& name = "Robby") : first_name{name}
    {
        //std::cout << "Right employee was created" << std::endl;
    };
    virtual void print() const
    {
        std::cout << "I'm an right employee!" << std::endl;
    };

    void DoSth(){}

    ~RightEmployee()
    {
        //std::cout << "Right employee was destroyed" << std::endl;
    }
};


class RightManager : public RightEmployee {
    std::list<Employee*> group; //являющиеся менеджерами рабочие
    short level;
public :
    RightManager(const std::string& name = "Robby", int dept = 12, int lvl = 1) : RightEmployee{name}
    {
        //std::cout << "Right manager was created" << std::endl;
    };
    void print()  const override final // перегрузка виртуальных функций, перегружает - распространяет а на б, чтобы из а вызвать функцию в б стаким же названием
    {
        RightEmployee::print();
        //print();//Бесконечная рекурсия
        std::cout << "I am a right manager" << std::endl;
    }

    ~RightManager()
    {

        //std::cout << "Right manager was destroyed" << std::endl;
    }
};


class A final{}; //от этого класса нельзя будет пронаследоваться, эквивалентно следующей строке
//class B : A {}; //can not do this

void UsingOfRightVirtualFunctions()
{
    std::unique_ptr<RightEmployee> employee1 (new RightEmployee()); //сборщик мусора
    std::unique_ptr<RightEmployee> employee2 (new RightManager()); //можно только мувать
    employee2->print(); //вызовется функция print класса rightManager
}

//abstract class
class Shape
{
    int centerOfGravity;
public :
    virtual void Draw() = 0; // спец синтаксис, который говорит, что в этом классе нет реализации в данном классе (pure virtual function)
    virtual void Rotate() = 0; // мы обязательно ее перегрузим
};

class Triangle : public Shape
{
public:
    void Draw() // не указан оверрайд
    {
        std::cout<<"I draw triangle"<<std::endl;
    }


    void Rotate() //не указан оверрайд
    {
        std::cout<<"I rotate triangle" << std::endl;
    }

};

class Circle : public Shape
{
public:
    void Draw()
    {
        std::cout<<"I draw circle"  << std::endl;
    }

    void Rotate()
    {
        std::cout<<"I rotate circle"<<std::endl;
    }
};


int main()
{
    UsingOfNoneVirtualFunctions();
    std::cout << std::endl << std::endl;
    UsingOfRightVirtualFunctions();


    std::cout << std::endl;

    srand(time(NULL));
    std::vector<std::unique_ptr<Shape>> shapes;
    size_t size = 20; // беззнаковый инт = сайз-т
    for(size_t index = 0; index < size; index++)
    {
        std::unique_ptr<Shape> shapePtr;//массив умных указателей на т
        if(rand()%100 > 50)
        {
            shapes.push_back(std::unique_ptr<Shape>(new Circle()));
        }
        else
        {
            shapes.push_back(std::unique_ptr<Shape>(new Triangle()));
        }
    }
    for(const auto& shape : shapes)
    {
        shape->Draw();
        shape->Rotate();
    }
}

        
//1)Objects are constructed from the bottom up (base before member and member before
//derived) and destroyed top-down (derived before member and member before base)
//2)Typically, destructors in a hierarchy need to be virtual

        //конкретные классы - ведут себя как примитивные типы, а все остальные - абстрактные == interface: есть виртуальные функции

//for each - типа как for i in list в питоне
