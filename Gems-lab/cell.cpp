#include "cell.hpp"

Cell::Cell(int x, int y) {
    setSize(sf::Vector2f(SIZE, SIZE));
    cellColor = Color_c(rand() % 4 + 1);
    setPosition(x, y);
    fillColor();
}

void Cell::clicked() {
    switch (cellColor) {
    case Color_c::EMPTY:
        break;
    case Color_c::BLUE:
        setFillColor(sf::Color(0, 149, 255, 100));
        break;
    case Color_c::RED:
        setFillColor(sf::Color(232, 32, 96, 100));
        break;
    case Color_c::YELLOW:
        setFillColor(sf::Color(0, 255, 128, 100));
        break;
    case Color_c::GREEN:
        setFillColor(sf::Color(255, 234, 0, 200));
        break;
    }
}

void Cell::fillColor() {
    switch (cellColor) {
    case Color_c::EMPTY:
        setFillColor(sf::Color(34, 23, 40, 0));
        break;
    case Color_c::BLUE:
        setFillColor(sf::Color(0, 149, 255, 250));
        break;
    case Color_c::RED:
        setFillColor(sf::Color(232, 32, 96, 250));
        break;
    case Color_c::YELLOW:
        setFillColor(sf::Color(0, 255, 128, 250));
        break;
    case Color_c::GREEN:
        setFillColor(sf::Color(255, 234, 0, 250));
        break;
    }
}

void Cell::setColor(Color_c newColor) {
    cellColor = newColor;
    fillColor();
}

void Cell::deleted() {
    cellColor = Color_c::EMPTY;
    fillColor();
}

Color_c Cell::getColor() {
    return cellColor;
}

void Cell::updateColor() {
    cellColor = Color_c(rand() % 4 + 1);
    fillColor();
}


