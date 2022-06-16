#ifndef Bonus_hpp
#define Bonus_hpp

#include "Object.hpp"
#include "Rocket.hpp"

enum class BonusType {
    WITHOT_BONUS,
    RESIZE_ROCKET,
    STICKY_ROCKET,
    SECOND_BALL,
    SPEED_CHANGING,
    CHANGE_DIRECTORY,
    MOVING_BLOCK,
    BOTTOM_ACTIVATE,
};

class Bonus : public Object {
    const float WDTH = 42;
    const float HGHT = 25;
    const float SPEED = 0.2;
    BonusType type = BonusType::WITHOT_BONUS;
    void setBonusType();
public:
    bool isOnField = false;
    Bonus();
    void getBonus(const sf::Vector2f& blockPosition, const sf::Vector2f& blockSize);
    bool update(const Rocket* rocket, int windowHght, float time);
    BonusType getBonusType();
};

#endif /* Bonus_hpp */
