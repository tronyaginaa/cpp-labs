//
//  main.cpp
//  QuadraticEq
//
//  Created by Alexandra Tronyagina on 27.02.2022.
//

#include <iostream>
#include <cmath>

double discriminant(double a, double b, double c){
    return b * b - 4 * a * c;
}

int solution(double a, double b, double c, double &x1, double &x2){
    double d = discriminant(a, b, c);
    if (d < 0)
        return 0;
    if (d == 0) {
        x1 = x2 = -b / (2 * a);
        return 1;
    }
    x1 = (-b + sqrt(d))/(2 * a);
    x1 = (-b - sqrt(d))/(2 * a);
    return 2;
}

int main() {
    double a, b ,c;
    std::cout << "Enter the values ​​of the coefficients a,b and c\n";
    std::cin >> a >> b >> c;
    double x1, x2;
    int numOfSolutions;
    numOfSolutions = solution(a, b, c, x1, x2);
    if (!numOfSolutions)
        std::cout << "No any solutions\n";
    else if (numOfSolutions == 1)
        std::cout << "One solution: x = " << x1 << "\n";
    else
        std::cout << "x1 = " << x1 << " x2 = " << x2 << "\n";
    return 0;
}

