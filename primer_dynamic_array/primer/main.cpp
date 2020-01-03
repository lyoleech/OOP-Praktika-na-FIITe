//
//  main.cpp
//  primer
//
//  Created by Olga Chernova on 10/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>

int main() {
    
    int **dinamic_array2 = new int* [5];
    for (int i = 0; i < 5; i++) {
        dinamic_array2[i] = new int [i + 1];
    }
    
    for (int i = 0; i < 5; i++) {
        std::cout << i + 1;
        for (int j = 0; j < i + 1; ++j) {
            std::cin >> dinamic_array2[i][j];
        }
    }
    
    for (int i = 0; i < 5; i++) {
        delete [] dinamic_array2[i];
    }
    delete [] dinamic_array2;
    return 0;
};

