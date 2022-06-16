#ifndef Rocket_hpp
#define Rocket_hpp

#include "Object.hpp"

enum class RocketDirection {
    STOPPED,
    LEFT,
    RIGHT,
};

class Rocket : public Object {
    const float WDTH = 123;
    const float HGHT = 24;
    const float SPEED = 0.5;
    const float PLACE = 700;
    const float RESIZE_COEF = 1.3;
public:
    bool isSticky = false;
    RocketDirection direction;
    Rocket(int windowWdth);
    void update(float windowWdth, float borderWidth, float time);
    void resizeRocket(float windowWdth, float borderWidth);
};

#endif /* Rocket_hpp */
