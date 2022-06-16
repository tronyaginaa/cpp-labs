
#ifndef Object_hpp
#define Object_hpp

#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::RectangleShape {
protected:
    sf::Vector2f speed;
public:
    virtual float leftBorder() const;
    virtual float rightBorder() const;
    virtual float topBorder() const;
    virtual float bottomBorder() const;
    sf::Vector2f getSpeed() const;
    void setSpeed(float newSpeedX, float newSpeedY);
    void reverseXSpeed();
    void reverseYSpeed();
};


#endif /* Object_hpp */
