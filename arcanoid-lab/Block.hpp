#ifndef Block_hpp
#define Block_hpp

#include "Object.hpp"

class Block : public Object {
public:
    bool isNotValid = false;
    bool isBonusBlock = false;
    Block(float x, float y);
    virtual bool collision(int& score) = 0;
    static const int BLOCK_WDTH = 150;
    static const int BLOCK_HGHT = 25;
};

class OrdinaryBlock : public Block {
public:
    OrdinaryBlock(float x, float y);
    virtual bool collision(int& score) override;
};

class IndestructibleBlock : public Block {
public:
    IndestructibleBlock(float x, float y);
    virtual bool collision(int& score) override;
};

class BlockWithHealth : public Block {
    unsigned int healthMaxNum;
public:
    unsigned int healthCount;
    BlockWithHealth(float x, float y, unsigned int healthNum);
    virtual bool collision(int& score) override;
};

class SpeedChangingBlock : public Block {
public:
    SpeedChangingBlock(float x, float y);
    virtual bool collision(int& score) override;
};

#endif /* Block_hpp */
