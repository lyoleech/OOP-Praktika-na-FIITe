//
//  string_main.cpp
//  string
//
//  Created by Olga Chernova on 05/07/2019.
//  Copyright © 2019 Olga Chernova. All rights reserved.
//

#include <iostream>

#include "String.h"

int main() {
    String str = String('c', 5);
    String bStr = String('B', 1);
    
    //str.push_back('A');
    std::cout << str << std::endl << str.sizeofmystr() << std::endl;
    
    return 0;
    
}
