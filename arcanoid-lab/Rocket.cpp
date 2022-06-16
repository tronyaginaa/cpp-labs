#include "Rocket.hpp"

Rocket::Rocket(int windowWidth) {
    setPosition((static_cast<float>(windowWidth) - WDTH) / 2, PLACE);
    setSize({ WDTH, HGHT });
    speed = { 0.f, 0.f };
    direction = RocketDirection::STOPPED;
    setFillColor(sf::Color::White);
}

void Rocket::update(float windowWidth, float borderWidth, float time) {
    if (direction == RocketDirection::LEFT && leftBorder() >= borderWidth)
        speed.x = -SPEED;
    else if (direction == RocketDirection::RIGHT && rightBorder() <= windowWidth - borderWidth)
        speed.x = SPEED;
    else
        speed.x = 0.f;
    move(speed * time);
    direction = RocketDirection::STOPPED;
}

void Rocket::resizeRocket(float windowWidth, float borderWidth) {
    if (rand() % 2 < 1) {
        if (getSize().x < WDTH) {
            return;
        }
        setSize({ WDTH / RESIZE_COEF, HGHT });
    }
    else {
        if (getSize().x > WDTH) {
            return;
        }
        setSize({ WDTH * RESIZE_COEF, HGHT });
        float shift = rightBorder() - (windowWidth - borderWidth);
        if (shift > 0)
            move(-shift, 0.f);
    }
}



