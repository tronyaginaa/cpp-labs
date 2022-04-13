//
//  main.cpp
//  Rectangles
//
//  Created by Alexandra Tronyagina on 13.04.2022.
//

#include <iostream>

class square{
public:
    int x;
    square(): x(0){};
    square(int x_): x(x_){};
    virtual void draw(){
        std::cout << "W:" << x << ";H:" << x<< std::endl;
        return;
    }
private:
};

class rectangle: public square{
public:
    int y;
    rectangle(): square(), y(0){};
    rectangle(int x_, int y_):square(x_), y(y_){};
    void draw(){
        std::cout << "W:" << x << ";H:" << y<< std::endl;
    }
private:
};

int main(){
    square sq(2);
    sq.draw();
    rectangle rec(2,3);
    rec.draw();
    return 0;
}
