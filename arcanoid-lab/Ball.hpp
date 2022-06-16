#ifndef Ball_hpp
#define Ball_hpp

#include "Object.hpp"
#include "Rocket.hpp"
#include "Block.hpp"
#include "Field.hpp"
#include <cmath>

class Ball : public Object {
    const float SIZE = 20;
    const float SPEED_UP = 1.1;
    const float SLOW_DOWN_COEF = 0.9;
    const sf::Vector2f DEFAULT_SPEED{ 0.25, -0.25 };
    sf::Vector2f SPEED = DEFAULT_SPEED;
    float placeOnRocket;
    bool blockTopColission(Block* block);
    bool blockBottomColission(Block* block);
    bool blockLeftColission(Block* block);
    bool blockRightColission(Block* block);
public:
    bool isOnRocket;
    Ball(float windowWidth, float paddleY, float shift);
    void rocketFollow(const Rocket* paddle);
    void update(const Rocket* paddle, float time);
    void blockCollision(Block* block, float time);
    void rocketCollision(Rocket* rocket);
    void borderCollision(int borderWdth, int windowWdth, Bottom* bottom);
    void ballCollision(Ball* secondBall);
    void setDefaultSpeed();
    void setSpeed();
    void changeSpeed();
    void setOnRocket(float shift);
};

#endif /* Ball_hpp */
