#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using std::vector;

enum class Color_c {
    EMPTY,
    BLUE,
    RED,
    YELLOW,
    GREEN
};

class Cell : public sf::RectangleShape {
public:
    static const int SIZE = 100;
    bool isInMatch = false;
    Cell(int x, int y);
    void updateColor();
    void clicked();
    void fillColor();
    void setColor(Color_c newColor);
    void deleted();
    Color_c getColor();
    int GetGemSize() { return SIZE; }
    Color_c cellColor;
};
