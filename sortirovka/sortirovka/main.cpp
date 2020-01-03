//
//  main.cpp
//  sortirovka
//
//  Created by Olga Chernova on 08/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cmath>
#include <utility>
#include <iomanip>

void ArrayOutput(const int*arr, int maxSize)
{
    for (int i = 0; i < maxSize; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}


void SortAscending(int *arr, int maxSize)
{
    for (int i = 0; i < maxSize - 1; ++i)
    {
        for (int j = 0; j < maxSize - i; ++j)
        {
            if (arr[j] > arr[j + 1]){
                arr[j] = arr[j] + arr[j+1];
                arr[j+1] = arr[j] - arr[j+1];
                arr[j] = arr[j]  - arr[j+1];
            }
        }
    }
}


void SortDescending(int *arr, int maxSize){
    for (int i = maxSize-1; i >=0; --i){
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}


double AverageValue(const int*arr, int maxSize){
    int sum = 0;
    for (int i = 0; i < maxSize; ++i){
        sum += arr[i];
    }
    return static_cast<double>(sum)/maxSize;
}


double GeometricMean(const int*arr, int maxSize){
    double p = 1;
    for (int i = 0; i < maxSize; ++i){
        p *=arr[i];
    }
    return pow(p, static_cast<double>(1) / maxSize);
}


int Maximum( int*arr, int maxSize){
    return arr[0];
}


int Minimum(int*arr, int maxSize){
    return  arr[maxSize-1];
}


int Getchar(int*arr, int maxSize, int num){
    for (int i = 0; i < maxSize; ++i){
        if (arr[i] == num){
            return i;
        }
    }
    return -1;
}


int main(){
    srand(time_t(NULL));
    int  maxSize;
    
    for (int i = 0; i < 3; ++i){
        std::cout << "rignt size of array"<<std::endl;
        std::cin >> maxSize;
        
        if (maxSize == 0)
            exit(1);
        
        int*arr = new int[maxSize];
        
        for (int i = 0; i < maxSize; ++i){
            arr[i] = rand() % 100;
            std::cout << arr[i] << ' ';
        }
        
        std::cout << "\nWrite number to find\n";
        
        int num;
        
        std::cin >> num;
        
        std::cout << Getchar(arr, maxSize, num)<< std::endl;
        
        SortAscending(arr, maxSize);
        ArrayOutput(arr, maxSize);
        
        SortDescending(arr, maxSize);
        
        std::cout << Maximum(arr, maxSize) << std::endl;
        
        std::cout << Minimum(arr, maxSize) << std::endl;
        
        std::cout << AverageValue(arr, maxSize) << std::endl;
        
        std::cout << GeometricMean(arr, maxSize) << std::endl;
        delete[] arr;
    }
    system("pause");
    
}

