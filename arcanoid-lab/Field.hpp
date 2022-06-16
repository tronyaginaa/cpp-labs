
#ifndef Field_hpp
#define Field_hpp

#include "Block.hpp"
#include "Bonus.hpp"

class Field {
    static const unsigned int COLUMNS = 7;
    static const unsigned int ROWS = 7;
    const float BLOCK_SET_X = 30;
    const float BLOCK_SET_Y = 100;
    const float INTERVAL = 2;
    const float MOVING_BLOCK_SPEED = 0.25;
    void fill();
    void free();
    float fieldBottom();
    int setType[COLUMNS][ROWS];
    void fillTypeMatrix();
public:
    std::vector<std::vector<Block*>> set{ COLUMNS, std::vector<Block*> { ROWS, nullptr } };
    BlockWithHealth* movingBlock;
    bool isMovingBlockActivated = false;
    Field();
    ~Field();
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getField() const;
    sf::Vector2f blockNum() const;
    void activateMovingBlock();
    void movingBlockUpdate(float time);
};

class Bottom : public Object {
    const float WDTH = 1130;
    const float HGHT = 20;
    const float BOTTOM_X = 1;
    const float BOTTOM_Y = 730;
public:
    bool isActivated = false;
    Bottom();
};

#endif /* Field_hpp */
