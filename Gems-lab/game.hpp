#pragma once
#include "gameControl.hpp"

class Game {
    static const int W_HEIGHT = 670;
    static const int W_WIDTH = 1200;
    static const int FIELD_LEFT_INDENT = 350;
    static const int FIELD_RIGHT_INDENT = 350;
    static const int FIELD_BOTTOM_INDENT = 85;
    static const int FIELD_TOP_INDENT = 85;
    static const int SCORE_TOP_INDENT = 10;
    static const int RESET_BOTTOM_INDENT = 15;
    static const int RESET_TOP_INDENT = 70;
    static const int RESET_LEFT_INDENT = 500;
    static const int RESET_RIGHT_INDENT = 500;
    unsigned int score = 0;
    sf::Text scoreLine;
    sf::Font font;
    sf::RectangleShape resetButton;
    sf::Text buttonText;
    sf::Vector2i bonusPlace(sf::Vector2i& bonusGenerator);
    vector<sf::Vector2i> bonusArea(sf::Vector2i& attendedCell);
    Field* field = new Field();
    bool isCell(const sf::Vector2i& clickCoordinates);
    void process(const sf::Vector2i& prevClickCoordinates, const sf::Vector2i& clickedCell);
    void processMatches();
public:
    Game();
    ~Game();
    sf::RenderWindow window{ sf::VideoMode(W_WIDTH, W_HEIGHT), "Gems", sf::Style::Close };
    void run(int& countOfClicks, sf::Vector2i& prevClickCoordinates);
    void drawInWindow();
    void resetClicked();
};


