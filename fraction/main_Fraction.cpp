#include "Fraction.hpp"
#include <iostream>

int main()
{
    Fraction a(3,7);
    //Fraction b(1,2);
    Fraction c;
    
    c = +a;
    c.reduction();
    std::cout << c << std::endl;
    
    Fraction r = ++a;
    std::cout << r.reduction() << std::endl;
    
    std::cout << (a.GetNumerator()) << " " << (a.GetDenominator()) << std::endl;
    a.SetNumerator(20);
    a.SetDenominator(40);
    std::cout << (static_cast<double>(a)) << std::endl;
    
    return 0;
}
