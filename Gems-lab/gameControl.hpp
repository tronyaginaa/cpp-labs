#pragma once
#include "cell.hpp"
#include <cmath>

class Field {
public:
    static const int SIZE = 5;
    vector<vector<std::shared_ptr<Cell>>> fieldGrid{ SIZE, vector<std::shared_ptr<Cell>>{SIZE, nullptr} };
    void grid(const int leftIndent, const int topIndent);
    void displayGrid(sf::RenderWindow& window) const;
    bool isNeighbours(const sf::Vector2i& prevClickCoordinates, const sf::Vector2i& clickCoordinates);
    bool swapCells(const sf::Vector2i& prevClickCoordinates, const sf::Vector2i& curClickCoordinates, sf::RenderWindow& window);
    int deleteMatches();
    void drop(sf::RenderWindow& window);
    int deleteAllMatches();
    int GetCellSize()const;
    int GetFieldSize()const;
private:
    bool gridIsFilled = false;
    bool isInMatch(const sf::Vector2i& coordinates);
    bool rowMatch(const sf::Vector2i& coordinates);
    bool columnMatch(const sf::Vector2i& coordinates);
    void swapCells(const sf::Vector2i& prevClickCoordinates, const sf::Vector2i& curClickCoordinates);
    bool findForMatch(const sf::Vector2i& gemCoordinates);
    sf::Vector2i findEmpty(const sf::Vector2i& beginOfColumn)const;
    int maxNumOfEmpty(vector<sf::Vector2i>& coordinatesOfFirstVoidCell)const;
    void dropColumn(sf::Vector2i& firstVoidCoordinates);
};

enum class BonusType_c {
    BOMB,
    REPAINTING
};

class Bonus : public Cell {
public:
    sf::Vector2i bonusCell;
    Bonus(int x, int y) : Cell(x, y) {};
    virtual void bonusAction(Field* field) = 0;
private:
    virtual vector<sf::Vector2i> bonusActionCells(Field* field) = 0;
};

class Bomb : public Bonus {
public:
    void bonusAction(Field* field)override;
    Bomb(int x, int y);
private:
    vector<sf::Vector2i> bonusActionCells(Field* field)override;
};

class Repainter : public Bonus {
public:
    void bonusAction(Field* field)override;
    Repainter(int x, int y, Color_c bonusCellType);
private:
    vector<sf::Vector2i> bonusActionCells(Field* field)override;
};
