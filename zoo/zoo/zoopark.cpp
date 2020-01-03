//
//  zoopark.cpp
//  zoo
//
//  Created by Olga Chernova on 10/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include <string>
#include <random>

#include "zoopark.hpp"


void Animal::Swim()
{
    
}

Animal::~Animal()
{
    
}

void Lion::Eat()
{
    std::cout << "Ya lev, i ya yem " << std::endl;
}

void Lion::Run()
{
    std::cout << "Ya lev, i ya run " << std::endl;
}

void Lion::Roar()
{
    std::cout << "Ya lev, i ya roar " << std::endl;
}

Lion::~Lion()
{
    std::cout << "i'm elephant and i'm going to sleep " << std::endl;
}


void Turtle::Eat()
{
    std::cout << "ya cherepaha, i ya yem" << std::endl;
}

void Turtle::Run()
{
    std::cout << "ya cherepaha, i ya begu " << std::endl;
}

void Turtle::Roar()
{
    std::cout << "ya cherepaha, i ya roar" << std::endl;
}

void Turtle::Swim()
{
    std::cout << " ya cherepaha i ya plyvu" << std::endl;
}

Turtle::~Turtle()
{
    std::cout << "i'm pawka and i'm going to sleep" << std::endl;
}


void Elephant::Eat()
{
    std::cout << "i'm elephant and i'm going to yest" << std::endl;
}

void Elephant::Run()
{
    std::cout << "Ya slon, i ya begu" << std::endl;
}

void Elephant::Roar()
{
    std::cout << "i'm elephant and i'm going to sleep" << std::endl;
}

Elephant::~Elephant()
{
    std::cout << "Ya slon, i ya idu spat" << std::endl;
}

Zoopark::Zoopark()
{
    std::mt19937 variableToUseInRandAlgorithm;
    size_t valueToSeed = 15;
    variableToUseInRandAlgorithm.seed(valueToSeed);
    std::uniform_int_distribution<uint32_t> uint_dist;
    std::uniform_int_distribution<uint32_t> uint_dist10(0,10); // От 0 до 10
    //нормальное распределение с параметрами - математическое ожидание и стандратное отклонение
    std::normal_distribution<double> normal_dist(1, 0);  // N(mean, standart deviation)
    for(int index = 0; index < 3; index++)
    {
        std::cout << uint_dist(variableToUseInRandAlgorithm) << ' ' <<
        uint_dist10(variableToUseInRandAlgorithm) << ' ' <<
        normal_dist(variableToUseInRandAlgorithm) << std::endl;
    }
    
    std::random_device seed;
    std::uniform_int_distribution<int> dist(0, 2);

    
    
    
    std::cout << "Quantity of animals" << std::endl;
    std::cin >> size_animal;
    nude_ptr = new Animal*[size_animal];
    for (size_t i = 0; i < size_animal; i++)
    {
        switch (dist(seed))
        {
            case 0:
                animals_ptr.push_back(std::unique_ptr<Animal>(new Elephant));
                nude_ptr[i] = new Elephant;
                break;
            case 1:
                animals_ptr.push_back(std::unique_ptr<Animal>(new Lion));
                nude_ptr[i] = new Lion;
                break;
            case 2:
                animals_ptr.push_back(std::unique_ptr<Animal>(new Turtle));
                nude_ptr[i] = new Turtle;
                break;
        }
        
    }
}

Zoopark::~Zoopark()
{
    for (size_t i = 0; i < size_animal; i++){
        
        delete nude_ptr[i];
        
    }
    delete[] nude_ptr;
    std::cout << "CLOSED" << std::endl;
}


void Zoopark::Action()
{
    for(const auto& animal : animals_ptr)
    {
        animal->Roar();
        animal->Run();
        animal->Eat();
        animal->Swim();
        
    }
    
    std::cout << std::endl;
    for(size_t i = 0; i < size_animal; i++)
    {
        
        nude_ptr[i]->Roar();
        nude_ptr[i]->Run();
        nude_ptr[i]->Eat();
        nude_ptr[i]->Swim();
    }
    
}
