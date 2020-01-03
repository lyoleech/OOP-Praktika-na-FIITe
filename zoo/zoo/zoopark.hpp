//
//  Created by Olga Chernova on 11/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#ifndef ZOO_H
#define ZOO_H

#include <iostream> //понаподключали тут всякого
#include <vector>
#include <ctime>
#include <list>
#include <memory>
#include <string>
#include <random>

class Animal  //создали класс Животное
{
private:
              //виртуальные методы для того, чтобы мы могли для каждого животного переопределить их:
public:       //лев у нас плавать не может, например (чисто формально, конечно - он ведь кошик), а черепаха
              //не рычит
    virtual void Eat() = 0;
    virtual void Run() = 0;
    virtual void Roar() = 0;
    virtual void Swim();
    
    virtual ~Animal(); //деструктор тоже виртуальный
};

class Lion: public Animal //отнаследовали класс льва
{
public:
    
    void Eat() override;
    void Run() override;
    void Roar() override;
    
    ~Lion() override;
    
};

class Turtle: public Animal
{
public:
    
    void Eat() override;
    void Run() override;
    void Roar() override;
    void Swim() override;
    
    ~Turtle() override;
    
};

class Elephant: public Animal
{
public:
    
    void Eat() override;
    void Run() override;
    void Roar() override;
    
    ~Elephant() override;
    
};

class Zoopark
{
private:
    size_t size_animal = 0;
    std::vector< std::unique_ptr < Animal > > animals_ptr;
    Animal** nude_ptr;
    
public:
    Zoopark();
    ~Zoopark();
    
    void Action();
};

#endif //ZOO_H
