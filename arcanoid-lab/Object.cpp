#include "Object.hpp"

float Object::leftBorder() const {
    return getPosition().x;
}

float Object::rightBorder() const {
    return getPosition().x + getSize().x;
}

float Object::topBorder() const {
    return getPosition().y;
}

float Object::bottomBorder() const {
    return getPosition().y + getSize().y;
}

sf::Vector2f Object::getSpeed() const {
    return speed;
}

void Object::setSpeed(float newSpeedX, float newSpeedY) {
    speed.x = newSpeedX;
    speed.y = newSpeedY;
}

void Object::reverseXSpeed() {
    speed.x *= -1;
}

void Object::reverseYSpeed() {
    speed.y *= -1;
}
