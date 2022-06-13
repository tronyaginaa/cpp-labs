#include "game.hpp"

Game::Game() {
    field->grid(FIELD_LEFT_INDENT, FIELD_TOP_INDENT);
    font.loadFromFile("CyrillicHelvet Bold.ttf");
    scoreLine.setFont(font);
    scoreLine.setCharacterSize(45);
    scoreLine.setFillColor(sf::Color::White);
    scoreLine.setString("score: " + std::to_string(score));
    scoreLine.setPosition(sf::Vector2f(FIELD_LEFT_INDENT, SCORE_TOP_INDENT));
    resetButton.setFillColor(sf::Color::White);
    resetButton.setSize(sf::Vector2f(200, 55));
    resetButton.setPosition(sf::Vector2f(RESET_LEFT_INDENT, W_HEIGHT - RESET_TOP_INDENT));
    buttonText.setFont(font);
    buttonText.setCharacterSize(40);
    buttonText.setString("reset");
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(sf::Vector2f(RESET_LEFT_INDENT + 50, W_HEIGHT - RESET_TOP_INDENT));
}

Game::~Game() {
    delete field;
}

bool Game::isCell(const sf::Vector2i& coordinates) {
    return coordinates.x >= FIELD_LEFT_INDENT && coordinates.x <= (W_WIDTH - FIELD_RIGHT_INDENT) && coordinates.y >= FIELD_TOP_INDENT && coordinates.y <= (W_HEIGHT - FIELD_BOTTOM_INDENT);
}

vector<sf::Vector2i> Game::bonusArea(sf::Vector2i& attendedCell) {
    vector<sf::Vector2i> bonusCoordinates;
    for (int i = attendedCell.y - 3; i <= attendedCell.y + 3; i++)
        for (int j = attendedCell.x - 3; j <= attendedCell.x + 3; j++)
            if (i >= 0 && j >= 0 && i < Field::SIZE && j < Field::SIZE)
                if (abs(attendedCell.x - j) + abs(attendedCell.y - i) <= 3 && !(field->fieldGrid[i][j]->isInMatch)) {
                    sf::Vector2i cell(j, i);
                    bonusCoordinates.push_back(cell);
                }
    return bonusCoordinates;
}

sf::Vector2i Game::bonusPlace(sf::Vector2i& bonusGenerator) {
    vector<sf::Vector2i> availableCell;
    int fieldSize = Field::SIZE;
    vector<sf::Vector2i> bonusGenerators;
    for (int i = 0; i < fieldSize; ++i)
        for (int j = 0; j < fieldSize; ++j) {
            sf::Vector2i curCoodinates(j, i);
            bonusGenerators.push_back(curCoodinates);
            vector<sf::Vector2i> curAreaCoordinates = bonusArea(curCoodinates);
            availableCell.push_back(curAreaCoordinates[rand() % curAreaCoordinates.size()]);
        }
    int numOfBonusGenerator = rand() % availableCell.size();
    bonusGenerator = bonusGenerators[numOfBonusGenerator];
    return availableCell[numOfBonusGenerator];
}

void Game::processMatches() {
    int numOfDeleted = field->deleteMatches();
    drawInWindow();
    sf::sleep(sf::seconds(0.3f));
    score += numOfDeleted;
    field->drop(window);
    sf::sleep(sf::seconds(0.3f));
    drawInWindow();
    sf::sleep(sf::seconds(0.3f));
    while ((numOfDeleted = field->deleteAllMatches()) != 0) {
        drawInWindow();
        sf::sleep(sf::seconds(0.3f));
        score += numOfDeleted;
        field->drop(window);
        sf::sleep(sf::seconds(0.3f));
        drawInWindow();
        sf::sleep(sf::seconds(0.3f));
    }
}

void Game::process(const sf::Vector2i& initCell, const sf::Vector2i& attendedCell) {
    if (field->swapCells(initCell, attendedCell, window)) {
        processMatches();
        int chanceOfBonus = rand() % 100;
        if (chanceOfBonus >= 50) {
            int bonusType = rand() % 2;
            sf::Vector2i bonusGenerator;
            sf::Vector2i place = bonusPlace(bonusGenerator);
            if (bonusType == (int)(BonusType_c::BOMB)) {
                Bomb bomb(FIELD_LEFT_INDENT + Cell::SIZE * place.x, FIELD_TOP_INDENT + Cell::SIZE * place.y);
                Bonus& bombB = bomb;
                bombB.bonusCell = place;
                Cell& bombG = bombB;
                auto bombCell = std::make_shared<Cell>(bombG);
                field->fieldGrid[place.y][place.x] = bombCell;
                drawInWindow();
                sf::sleep(sf::seconds(0.4f));
                bomb.bonusAction(field);
                auto newCell = std::make_shared<Cell>(Cell(FIELD_LEFT_INDENT + Cell::SIZE * place.x, FIELD_TOP_INDENT + Cell::SIZE * place.y));
                newCell->deleted();
                field->fieldGrid[place.y][place.x] = newCell;
                drawInWindow();
                sf::sleep(sf::seconds(0.2f));
                field->drop(window);
                sf::sleep(sf::seconds(0.2f));
            }
            else if (bonusType == (int)(BonusType_c::REPAINTING)) {
                Repainter repainter(FIELD_LEFT_INDENT + Cell::SIZE * place.x, FIELD_TOP_INDENT + Cell::SIZE * place.y, field->fieldGrid[place.y][place.x]->getColor());
                Bonus& repainterB = repainter;
                repainterB.bonusCell = place;
                Cell& repainterG = repainterB;
                auto repainterCell = std::make_shared<Cell>(repainterG);
                field->fieldGrid[place.y][place.x] = repainterCell;
                drawInWindow();
                sf::sleep(sf::seconds(0.4f));
                repainter.bonusAction(field);
                auto newCell = std::make_shared<Cell>(Cell(FIELD_LEFT_INDENT + Cell::SIZE * place.x, FIELD_TOP_INDENT + Cell::SIZE * place.y));
                newCell->setColor(repainterCell->getColor());
                field->fieldGrid[place.y][place.x] = newCell;
                drawInWindow();
                sf::sleep(sf::seconds(0.3f));
            }
        }
        processMatches();
    }
}

void Game::run(int& countOfClicks, sf::Vector2i& initCell) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left) {
            sf::Vector2i click = sf::Mouse::getPosition(window);
            if (click.x >= RESET_LEFT_INDENT && click.x <= RESET_LEFT_INDENT + 200 && click.y >= W_HEIGHT - RESET_TOP_INDENT && click.y <= W_HEIGHT - RESET_BOTTOM_INDENT)
                resetClicked();
            else if (click.x >= FIELD_LEFT_INDENT && click.x <= (W_WIDTH - FIELD_RIGHT_INDENT) && click.y >= FIELD_TOP_INDENT && click.y <= (W_HEIGHT - FIELD_BOTTOM_INDENT)) {
                sf::Vector2i attendedCell;
                attendedCell.x = (click.x - FIELD_LEFT_INDENT) / Cell::SIZE;
                attendedCell.y = (click.y - FIELD_TOP_INDENT) / Cell::SIZE;
                countOfClicks++;
                if (countOfClicks == 1) {
                    field->fieldGrid[attendedCell.y][attendedCell.x]->clicked();
                    initCell.x = attendedCell.x;
                    initCell.y = attendedCell.y;
                }
                else if (countOfClicks == 2) {
                    field->fieldGrid[initCell.y][initCell.x]->fillColor();
                    if (attendedCell == initCell)
                        countOfClicks = 0;
                    else if (!field->isNeighbours(initCell, attendedCell)) {
                        field->fieldGrid[attendedCell.y][attendedCell.x]->clicked();
                        initCell.x = attendedCell.x;
                        initCell.y = attendedCell.y;
                        countOfClicks = 1;
                    }
                    else {
                        process(initCell, attendedCell);
                        countOfClicks = 0;
                        initCell.x = 0;
                        initCell.y = 0;
                    }
                }
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::drawInWindow() {
    window.clear();
    field->displayGrid(window);
    scoreLine.setString("score: " + std::to_string(score));
    window.draw(scoreLine);
    window.draw(resetButton);
    window.draw(buttonText);
    window.display();
}

void Game::resetClicked() {
    field->grid(FIELD_LEFT_INDENT, FIELD_TOP_INDENT);
    score = 0;
    drawInWindow();
}
