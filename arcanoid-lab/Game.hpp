#ifndef game_hpp
#define game_hpp

#include "Object.hpp"
#include "Block.hpp"
#include "Rocket.hpp"
#include "Ball.hpp"
#include "Bonus.hpp"
#include "Field.hpp"

class Game {
    static const int WINDOW_WDTH = 1130;
    static const int WINDOW_HGHT = 900;
    static const int BORDER_WDTH = 18;
    static const int FRAM = 200;
    static const int FREQ = 800;
    static const int SCORE_SET_X = 30;
    static const int SCORE_SET_Y = 15;
    int score = 0;
    sf::Clock* clock;
    sf::Text scoreLine;
    sf::Font font;
    Rocket* rocket;
    Ball* ball;
    Field* blocks;
    Bonus* bonus;
    Bottom* bottom;
    Ball* secondBall;
    bool isSecondBall = false;
    void drawInWindow();
    void checkKeyPress();
    void checkBallisValid();
    void fieldCollision(Ball* _ball, float time);
    void allBallCollision(Ball* _ball, float time);
    void activateSecondBall();
    void generateBonus(float time);
public:
    sf::RenderWindow window{ sf::VideoMode(WINDOW_WDTH, WINDOW_HGHT), "ARKANOID", sf::Style::Close };
    Game();
    ~Game();
    void Run();
};

#endif /* game_hpp */
