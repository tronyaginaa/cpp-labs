#include "Block.hpp"

Block::Block(float x, float y) {
    setPosition(x, y);
    setSize({ static_cast<float>(BLOCK_WDTH), static_cast<float>(BLOCK_HGHT) });
    speed = { 0.f, 0.f };
}

OrdinaryBlock::OrdinaryBlock(float x, float y) : Block(x, y) {
    isBonusBlock = (std::rand() % 4 != 0);
    if (isBonusBlock)
        setFillColor(sf::Color(255, 145, 0, 250));
    else
        setFillColor(sf::Color(245, 73, 168, 250));
}

IndestructibleBlock::IndestructibleBlock(float x, float y) : Block(x, y) {
    isBonusBlock = false;
    setFillColor(sf::Color(82, 9, 145, 250));
}

SpeedChangingBlock::SpeedChangingBlock(float x, float y) : Block(x, y) {
    isBonusBlock = false;
    setFillColor(sf::Color(0, 187, 255, 250));
}

BlockWithHealth::BlockWithHealth(float x, float y, unsigned int healthNum) : Block(x, y) {
    healthMaxNum = healthNum;
    healthCount = healthMaxNum;
    isBonusBlock = false;
    setFillColor(sf::Color(137, 255, 46, 250));
}


bool OrdinaryBlock::collision(int& score) {
    isNotValid = true;
    score++;
    return false;
}

bool IndestructibleBlock::collision(int& score) {
    return false;
}

bool BlockWithHealth::collision(int& score) {
    healthCount--;
    score++;
    if (healthCount == 2)
        setFillColor(sf::Color(137, 255, 46, 200));
    else if (healthCount == 1)
        setFillColor(sf::Color(137, 255, 46, 150));
    else if (healthCount == 0)
        isNotValid = true;
    return false;
}

bool SpeedChangingBlock::collision(int& score) {
    isNotValid = true;
    score++;
    return true;
}

