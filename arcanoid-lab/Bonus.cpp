#include "Bonus.hpp"

Bonus::Bonus() {
    setPosition(0.f, 0.f);
    setSize({ WDTH, HGHT });
    speed = { 0.f, SPEED };
}

void Bonus::setBonusType() {
    type = (BonusType)(rand() % 7 + 1);
}

void Bonus::getBonus(const sf::Vector2f& blockPosition, const sf::Vector2f& blockSize) {
    setBonusType();
    isOnField = true;
    setPosition(blockPosition.x + (blockSize.x - WDTH) / 2, blockPosition.y + blockSize.y / 2);
}

bool Bonus::update(const Rocket* paddle, int windowHeight, float time) {
    move(speed * time);
    if (topBorder() > windowHeight)
        isOnField = false;
    if (getGlobalBounds().intersects(paddle->getGlobalBounds())) {
        isOnField = false;
        return true;
    }
    return false;
}

BonusType Bonus::getBonusType() {
    return type;
}
