#include "game.hpp"

Game::Game() {
    clock = new sf::Clock();
    rocket = new Rocket(WINDOW_WDTH);
    ball = new Ball(WINDOW_WDTH, rocket->getPosition().y, 0.f);
    ball->setDefaultSpeed();
    blocks = new Field();
    bonus = new Bonus();
    bottom = new Bottom();
    secondBall = new Ball(WINDOW_WDTH, rocket->getPosition().y, ball->getSize().x + 1);
    window.setFramerateLimit(FRAM);
    font.loadFromFile("/Users/tronyagina/Desktop/arkanoidNew/CyrillicHelvet Bold.ttf");
    scoreLine.setFont(font);
    scoreLine.setCharacterSize(45);
    scoreLine.setFillColor(sf::Color::White);
    scoreLine.setString("score: " + std::to_string(score));
    scoreLine.setPosition(sf::Vector2f(SCORE_SET_X, SCORE_SET_Y));
}

Game::~Game() {
    delete clock;
    delete rocket;
    delete ball;
    delete blocks;
    delete bonus;
    delete bottom;
    delete secondBall;
}

void Game::drawInWindow() {
    window.clear();
    scoreLine.setString("score: " + std::to_string(score));
    window.draw(scoreLine);
    window.draw(*ball);
    if (isSecondBall)
        window.draw(*secondBall);
    window.draw(*rocket);
    if (bonus->isOnField)
        window.draw(*bonus);
    blocks->draw(window);
    if (bottom->isActivated)
        window.draw(*bottom);
    window.display();
}

void Game::checkKeyPress() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        rocket->direction = RocketDirection::LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        rocket->direction = RocketDirection::RIGHT;
    else
        rocket->direction = RocketDirection::STOPPED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        if (ball->isOnRocket) {
            ball->setSpeed();
            ball->isOnRocket = false;
            if (rocket->isSticky)
                rocket->isSticky = false;
        }
        if (isSecondBall && secondBall->isOnRocket) {
            secondBall->setSpeed();
            secondBall->isOnRocket = false;
        }
    }
}

void Game::checkBallisValid() {
    if (ball->topBorder() > WINDOW_HGHT) {
        if (!isSecondBall) {
            ball->isOnRocket = true;
        }
        score--;
        std::swap(ball, secondBall);
        ball->setOnRocket(0.f);
        secondBall->setOnRocket(ball->getSize().x + 1);
    }
    if (isSecondBall && secondBall->topBorder() > WINDOW_HGHT)
        isSecondBall = false;
}

void Game::fieldCollision(Ball* _ball, float time) {
    if (blocks->isMovingBlockActivated && !blocks->movingBlock->isNotValid && _ball->getGlobalBounds().intersects(blocks->movingBlock->getGlobalBounds())) {
        _ball->blockCollision(blocks->movingBlock, time);
        blocks->movingBlock->collision(score);
        if (blocks->movingBlock->isNotValid) {
            blocks->isMovingBlockActivated = false;
        }
    }
    if (!blocks->getField().intersects(_ball->getGlobalBounds()))
        return;
    for (int i = 0; i < blocks->blockNum().x; ++i)
        for (int j = 0; j < blocks->blockNum().y; ++j) {
            if (blocks->set[i][j]->isNotValid || !_ball->getGlobalBounds().intersects(blocks->set[i][j]->getGlobalBounds()))
                continue;
            _ball->blockCollision(blocks->set[i][j], time);
            if (blocks->set[i][j]->collision(score)) {
                _ball->changeSpeed();
                if (blocks->set[i][j]->isNotValid)
                    score++;
            }
            if (blocks->set[i][j]->isBonusBlock == true && bonus->isOnField == false)
                bonus->getBonus(blocks->set[i][j]->getPosition(), blocks->set[i][j]->getSize());
        }
}


void Game::allBallCollision(Ball* _ball, float time) {
    fieldCollision(_ball, time);
    _ball->borderCollision(BORDER_WDTH, WINDOW_WDTH, bottom);
    _ball->rocketCollision(rocket);
}

void Game::activateSecondBall() {
    if (isSecondBall)
        return;
    isSecondBall = true;
    secondBall->rocketFollow(rocket);
    if (ball->isOnRocket)
        secondBall->isOnRocket = true;
    else {
        secondBall->isOnRocket = false;
        secondBall->setDefaultSpeed();
        secondBall->setSpeed();
    }
}

void Game::generateBonus(float time) {
    if (!bonus->isOnField)
        return;
    if (!bonus->update(rocket, WINDOW_HGHT, time))
        return;
    BonusType bonusType = bonus->getBonusType();
    switch (bonusType) {
    case BonusType::WITHOT_BONUS:
        break;
    case BonusType::RESIZE_ROCKET:
        rocket->resizeRocket(WINDOW_WDTH, BORDER_WDTH);
        break;
    case BonusType::STICKY_ROCKET:
        rocket->isSticky = true;
        break;
    case BonusType::SECOND_BALL:
        activateSecondBall();
        break;
    case BonusType::SPEED_CHANGING:
        ball->changeSpeed();
        if (isSecondBall)
            secondBall->changeSpeed();
        break;
    case BonusType::CHANGE_DIRECTORY:
        ball->getSpeed().x > ball->getSpeed().y ? ball->reverseXSpeed() : ball->reverseYSpeed();
        if (isSecondBall)
            secondBall->getSpeed().x > secondBall->getSpeed().y ? secondBall->reverseXSpeed() : secondBall->reverseYSpeed();
        break;
    case BonusType::MOVING_BLOCK:
        blocks->activateMovingBlock();
        break;
    case BonusType::BOTTOM_ACTIVATE:
        bottom->isActivated = true;
        break;
    }
}

void Game::Run() {
    while (window.isOpen()) {
        float time = static_cast<float>(clock->getElapsedTime().asMicroseconds());
        clock->restart();
        time = time / FREQ;
        sf::Event event;
        window.pollEvent(event);
        if (event.type == sf::Event::Closed)
            window.close();
        checkKeyPress();
        rocket->update(WINDOW_WDTH, BORDER_WDTH, time);
        ball->update(rocket, time);
        blocks->movingBlockUpdate(time);
        allBallCollision(ball, time);
        if (isSecondBall) {
            secondBall->update(rocket, time);
            allBallCollision(secondBall, time);
            ball->ballCollision(secondBall);
        }
        generateBonus(time);
        checkBallisValid();
        drawInWindow();
    }
}
