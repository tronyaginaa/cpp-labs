#include "Ball.hpp"

Ball::Ball(float windowWidth, float paddleY, float shift) : placeOnRocket(shift) {
    isOnRocket = true;
    setSize({ SIZE, SIZE });
    setPosition((static_cast<float>(windowWidth) - SIZE) / 2 + placeOnRocket, paddleY - SIZE);
    speed = DEFAULT_SPEED;
    setFillColor(sf::Color::White);
}

void Ball::rocketFollow(const Rocket* paddle) {
    setPosition({ (paddle->getPosition().x + (paddle->getSize().x - getSize().x) / 2) + placeOnRocket, paddle->getPosition().y - getSize().y });
}

void Ball::update(const Rocket* paddle, float time) {
    if (isOnRocket)
        rocketFollow(paddle);
    else
        move(speed.x * time, speed.y * time);
}

void Ball::setDefaultSpeed() {
    SPEED = DEFAULT_SPEED;
}

void Ball::setSpeed() {
    speed = SPEED;
}

void Ball::changeSpeed() {
    if (rand() % 2 < 1) {
        speed *= SPEED_UP;
        SPEED *= SPEED_UP;
    }
    else {
        speed *= SLOW_DOWN_COEF;
        SPEED *= SLOW_DOWN_COEF;
    }
}

void Ball::setOnRocket(float shift) {
    placeOnRocket = shift;
}

//bool Ball:: blockTopColission(Block* block){
//    float getPosition().x = getPosition().x;
//    float getPosition().y = getPosition().y;
//    float getSize().x = getSize().x;
//    float blockX = block->getPosition().x;
//    float blockY = block->getPosition().y;
//    float blockWidth = block->getSize().x;
//    float blockHeight = block->getSize().y;
//    bool right = sf::FloatRect(getPosition().x, getPosition().y, getSize().x, 1).intersects(sf::FloatRect(blockX + blockWidth, blockY, 1, blockHeight));
//    bool left = sf::FloatRect(getPosition().x, getPosition().y, getSize().x, 1).intersects(sf::FloatRect(blockX, blockY, 1, blockHeight));
//    return right||tLeft;
//}
//
//bool Ball::blockBottomColission(Block* block){
//    float getPosition().x = getPosition().x;
//    float getPosition().y = getPosition().y;
//    float getSize().x = getSize().x;
//    float blockX = block->getPosition().x;
//    float blockY = block->getPosition().y;
//    float blockWidth = block->getSize().x;
//    float blockHeight = block->getSize().y;
//    bool right = sf::FloatRect(getPosition().x, getPosition().y + getSize().x, getSize().x, 1).intersects(sf::FloatRect(blockX + blockWidth, blockY, 1, blockHeight));
//    bool left = sf::FloatRect(getPosition().x, getPosition().y + getSize().x, getSize().x, 1).intersects(sf::FloatRect(blockX, blockY, 1, blockHeight));
//    return left||right;
//}
//
//bool Ball::blockLeftColission(Block* block){
//    float getPosition().x = getPosition().x;
//    float getPosition().y = getPosition().y;
//    float getSize().x = getSize().x;
//    float blockX = block->getPosition().x;
//    float blockY = block->getPosition().y;
//    float blockWidth = block->getSize().x;
//    float blockHeight = block->getSize().y;
//    bool top = sf::FloatRect(getPosition().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY, blockWidth, 1));
//    bool bottom = sf::FloatRect(getPosition().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY + blockHeight, blockWidth, 1));
//    return top|| bottom;
//}
//
//bool Ball::blockRightColission(Block* block){
//    float getPosition().x = getPosition().x;
//    float getPosition().y = getPosition().y;
//    float getSize().x = getSize().x;
//    float blockX = block->getPosition().x;
//    float blockY = block->getPosition().y;
//    float blockWidth = block->getSize().x;
//    float blockHeight = block->getSize().y;
//    bool top = sf::FloatRect(getPosition().x + getSize().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY, blockWidth, 1));
//    bool bottom = sf::FloatRect(getPosition().x + getSize().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY + blockHeight, blockWidth, 1));
//    return top || bottom;
//}

void Ball::blockCollision(Block* block, float time) {
    float blockX = block->getPosition().x;
    float blockY = block->getPosition().y;
    float blockWidth = block->getSize().x;
    float blockHeight = block->getSize().y;
    bool topRight = sf::FloatRect(getPosition().x, getPosition().y, getSize().x, 1).intersects(sf::FloatRect(blockX + blockWidth, blockY, 1, blockHeight));
    bool topLeft = sf::FloatRect(getPosition().x, getPosition().y, getSize().x, 1).intersects(sf::FloatRect(blockX, blockY, 1, blockHeight));
    bool bottomRight = sf::FloatRect(getPosition().x, getPosition().y + getSize().x, getSize().x, 1).intersects(sf::FloatRect(blockX + blockWidth, blockY, 1, blockHeight));
    bool bottomLeft = sf::FloatRect(getPosition().x, getPosition().y + getSize().x, getSize().x, 1).intersects(sf::FloatRect(blockX, blockY, 1, blockHeight));
    bool leftTop = sf::FloatRect(getPosition().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY, blockWidth, 1));
    bool leftBottom = sf::FloatRect(getPosition().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY + blockHeight, blockWidth, 1));
    bool rightTop = sf::FloatRect(getPosition().x + getSize().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY, blockWidth, 1));
    bool rightBottom = sf::FloatRect(getPosition().x + getSize().x, getPosition().y, 1, getSize().x).intersects(sf::FloatRect(blockX, blockY + blockHeight, blockWidth, 1));
    setPosition(getPosition().x - getSpeed().x * time, getPosition().y - getSpeed().y * time);
    if (topRight || topLeft || bottomRight || bottomLeft)
        reverseXSpeed();
    if (leftTop || leftBottom || rightTop || rightBottom)
        reverseYSpeed();
}

void Ball::rocketCollision(Rocket* rocket) {
    sf::FloatRect rocketArea;
    if (!getGlobalBounds().intersects(rocket->getGlobalBounds(), rocketArea))
        return;
    if (rocket->getPosition().y < getPosition().y) {
        reverseXSpeed();
        if (getPosition().x < rocket->getPosition().x)
            setPosition(rocket->getPosition().x - 2 * getSize().x, getPosition().y);
        else
            setPosition(rocket->getPosition().x + rocket->getSize().x, getPosition().y);
        return;
    }
    reverseYSpeed();
    setPosition(getPosition().x, rocket->getPosition().y - 2 * getSize().x);
}

void Ball::borderCollision(int borderWdth, int windowWdth, Bottom* bottom) {
    if (leftBorder() <= borderWdth) {
        setPosition({ static_cast<float>(borderWdth), getPosition().y });
        reverseXSpeed();
    }
    else if (rightBorder() >= windowWdth - borderWdth) {
        setPosition({ static_cast<float>(windowWdth - borderWdth) - getSize().x,getPosition().y });
        reverseXSpeed();
    }
    else if (topBorder() < borderWdth) {
        setPosition({ getPosition().x, static_cast<float>(borderWdth) });
        reverseYSpeed();
    }

    else if (bottom->isActivated && getGlobalBounds().intersects(bottom->getGlobalBounds())) {
        setPosition({ getPosition().x, bottom->topBorder() - getSize().y });
        reverseYSpeed();
        bottom->isActivated = false;
    }
}

void Ball::ballCollision(Ball* secondBall) {
    if (!getGlobalBounds().intersects(secondBall->getGlobalBounds()) || isOnRocket || secondBall->isOnRocket)
        return;
    reverseXSpeed();
    secondBall->reverseXSpeed();
}
