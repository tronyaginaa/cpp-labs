#include "Field.hpp"

Field::Field() {
    fillTypeMatrix();
    fill();
}

Field::~Field() {
    free();
}

void Field::fillTypeMatrix() {
    for (int i = 0; i < COLUMNS; i++)
        for (int j = 0; j < ROWS; j++)
            setType[i][j] = rand() % 7 + 1;
}

void Field::fill() {
    srand(static_cast<unsigned int>(time(nullptr)));
    float x = BLOCK_SET_X;
    for (int i = 0; i < COLUMNS; ++i) {
        float y = BLOCK_SET_Y;
        for (int j = 0; j < ROWS; ++j) {
            Block* block;
            if (setType[i][j] == 1 || setType[i][j] == 2 || setType[i][j] == 3) {
                block = new OrdinaryBlock(x, y);
            }
            else if (setType[i][j] == 4) {
                block = new SpeedChangingBlock(x, y);
            }
            else if (setType[i][j] == 5) {
                block = new IndestructibleBlock(x, y);
            }
            else if (setType[i][j] == 6) {
                block = new BlockWithHealth(x, y, 3);
            }
            else if (setType[i][j] == 7) {
                block = new BlockWithHealth(x, y, 2);
            }
            else
                block = nullptr;
            set[i][j] = block;
            y += Block::BLOCK_HGHT + INTERVAL;
        }
        x += Block::BLOCK_WDTH + INTERVAL;
    }
    movingBlock = new BlockWithHealth(0.f, 0.f, 3);
}

void Field::free() {
    for (int i = 0; i < COLUMNS; ++i) {
        for (int j = 0; j < ROWS; ++j)
            delete set[i][j];
    }
    delete movingBlock;
}

void Field::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < COLUMNS; ++i)
        for (int j = 0; j < ROWS; ++j)
            if (!set[i][j]->isNotValid)
                window.draw(*set[i][j]);
    if (isMovingBlockActivated && !movingBlock->isNotValid)
        window.draw(*movingBlock);
}

sf::FloatRect Field::getField() const {
    float width = (Block::BLOCK_WDTH + INTERVAL) * COLUMNS - INTERVAL;
    float height = (Block::BLOCK_HGHT + INTERVAL) * ROWS - INTERVAL;
    return sf::FloatRect{ BLOCK_SET_X, BLOCK_SET_Y, width, height };
}

sf::Vector2f Field::blockNum() const {
    return { COLUMNS , ROWS };
}

float Field::fieldBottom() {
    for (int j = ROWS - 1; j >= 0; --j)
        for (int i = 0; i < COLUMNS; ++i)
            if (!set[i][j]->isNotValid)
                return BLOCK_SET_Y + (j + 1) * (Block::BLOCK_HGHT + INTERVAL);
    return BLOCK_SET_Y;
}

void Field::activateMovingBlock() {
    if (isMovingBlockActivated)
        return;
    isMovingBlockActivated = true;
    movingBlock->healthCount = 3;
    movingBlock->setPosition({ BLOCK_SET_X , fieldBottom() });
    movingBlock->setSpeed(MOVING_BLOCK_SPEED, 0.f);
}

void Field::movingBlockUpdate(float time) {
    if (!isMovingBlockActivated || movingBlock->isNotValid)
        return;
    movingBlock->move(movingBlock->getSpeed().x * time, 0.f);
    if (movingBlock->leftBorder() <= BLOCK_SET_X || movingBlock->rightBorder() >= BLOCK_SET_X + getField().width)
        movingBlock->reverseXSpeed();
}

Bottom::Bottom() {
    setPosition(BOTTOM_X, BOTTOM_Y);
    setSize({ WDTH, HGHT });
    setFillColor(sf::Color::Blue);
    speed = { 0.f, 0.f };
}

