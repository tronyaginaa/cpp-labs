#include "gameControl.hpp"

bool Field::rowMatch(const sf::Vector2i& coordinates) {
    int matchLength = 1;
    Color_c attendedColor = fieldGrid[coordinates.y][coordinates.x]->getColor();
    int col = coordinates.x;
    int row = coordinates.y;
    while (col > 0 && fieldGrid[row][--col]->getColor() == attendedColor)
        matchLength++;
    if (gridIsFilled) {
        col = coordinates.x;
        while (col < (SIZE - 1) && fieldGrid[row][++col]->getColor() == attendedColor)
            matchLength++;
    }
    return matchLength > 2;
}

bool Field::columnMatch(const sf::Vector2i& coordinates) {
    int matchLength = 1;
    Color_c curCellColor_c = fieldGrid[coordinates.y][coordinates.x]->getColor();
    int col = coordinates.x;
    int row = coordinates.y;
    while (row > 0 && fieldGrid[--row][col]->getColor() == curCellColor_c)
        matchLength++;
    if (gridIsFilled) {
        row = coordinates.y;
        while (row < (SIZE - 1) && fieldGrid[++row][col]->getColor() == curCellColor_c)
            matchLength++;
    }
    return matchLength > 2;
}

void Field::grid(const int leftIndent, const int topIndent) {
    int x;
    int y = topIndent;
    for (int i = 0; i < SIZE; i++) {
        x = leftIndent;
        for (int j = 0; j < SIZE; j++) {
            auto cell = std::make_shared<Cell>(Cell(x, y));
            fieldGrid[i][j] = cell;
            x += Cell::SIZE;
            sf::Vector2i coordinates(j, i);
            while (rowMatch(coordinates) || columnMatch(coordinates))
                fieldGrid[i][j]->updateColor();
        }
        y += Cell::SIZE;
    }
    gridIsFilled = true;
}

void Field::displayGrid(sf::RenderWindow& window) const {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            window.draw(*fieldGrid[i][j]);
}

bool Field::isNeighbours(const sf::Vector2i& prevClickCoordinates, const sf::Vector2i& curClickCoordinates) {
    if ((curClickCoordinates.x == prevClickCoordinates.x - 1 || curClickCoordinates.x == prevClickCoordinates.x + 1) && curClickCoordinates.y == prevClickCoordinates.y)
        return true;
    if ((curClickCoordinates.y == prevClickCoordinates.y - 1 || curClickCoordinates.y == prevClickCoordinates.y + 1) && prevClickCoordinates.x == curClickCoordinates.x)
        return true;
    return false;
}

void Field::swapCells(const sf::Vector2i& initCell, const sf::Vector2i& atendedCell) {
    Color_c initColor = fieldGrid[initCell.y][initCell.x]->getColor();
    fieldGrid[initCell.y][initCell.x]->setColor(fieldGrid[atendedCell.y][atendedCell.x]->getColor());
    fieldGrid[atendedCell.y][atendedCell.x]->setColor(initColor);
}

bool Field::findForMatch(const sf::Vector2i& cellCoordinates) {
    Color_c color = fieldGrid[cellCoordinates.y][cellCoordinates.x]->getColor();
    int col = cellCoordinates.x;
    int row = cellCoordinates.y;
    int numOfMarked = 0;
    if (rowMatch(cellCoordinates)) {
        while (col > 0 && fieldGrid[row][--col]->getColor() == color) {
            fieldGrid[row][col]->isInMatch = true;
            numOfMarked++;
        }
        col = cellCoordinates.x;
        while (col < (SIZE - 1) && fieldGrid[row][++col]->getColor() == color) {
            fieldGrid[row][col]->isInMatch = true;
            numOfMarked++;
        }
        fieldGrid[cellCoordinates.y][cellCoordinates.x]->isInMatch = true;
        return true;
    }
    numOfMarked = 0;
    if (columnMatch(cellCoordinates)) {
        while (row > 0 && fieldGrid[--row][col]->getColor() == color) {
            fieldGrid[row][col]->isInMatch = true;
            numOfMarked++;
        }
        row = cellCoordinates.y;
        while (row < (SIZE - 1) && fieldGrid[++row][col]->getColor() == color) {
            fieldGrid[row][col]->isInMatch = true;
            numOfMarked++;
        }
        fieldGrid[cellCoordinates.y][cellCoordinates.x]->isInMatch = true;
        return true;
    }
    return false;
}

sf::Vector2i Field::findEmpty(const sf::Vector2i& begin)const {
    int col = begin.x;
    int row = begin.y;
    while (row >= 0 && fieldGrid[row][col]->getColor() != Color_c::EMPTY)
        row--;
    sf::Vector2i result;
    if (row < 0) {
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.x = col;
    result.y = row;
    return result;
}

int Field::maxNumOfEmpty(vector<sf::Vector2i>& firstEmpty)const {
    int maxNum = 0;
    for (int i = 0; i < SIZE; ++i) {
        int num = 0;
        for (int j = firstEmpty[i].y; j >= 0; --j)
            if (fieldGrid[j][i]->getColor() == Color_c::EMPTY)
                num++;
        if (num > maxNum)
            maxNum = num;
    }
    return maxNum;
}

void Field::dropColumn(sf::Vector2i& firstEmptyCell) {
    int row = firstEmptyCell.y;
    int col = firstEmptyCell.x;
    int i = row;
    while (i > 0) {
        fieldGrid[i][col]->setColor(fieldGrid[i - 1][col]->getColor());
        i--;
    }
    fieldGrid[i][col]->updateColor();
}

bool Field::swapCells(const sf::Vector2i& initCell, const sf::Vector2i& attendedCell, sf::RenderWindow& window) {
    swapCells(initCell, attendedCell);
    displayGrid(window);
    window.display();
    sf::sleep(sf::seconds(0.3f));
    if (!findForMatch(initCell) && !findForMatch(attendedCell)) {
        swapCells(initCell, attendedCell);
        return false;
    }
    return true;
}

int Field::deleteMatches() {
    int numOfDeleted = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (fieldGrid[i][j]->isInMatch || fieldGrid[i][j]->getColor() == Color_c::EMPTY) {
                fieldGrid[i][j]->isInMatch = false;
                numOfDeleted++;
                fieldGrid[i][j]->deleted();
            }
    return numOfDeleted;
}

void Field::drop(sf::RenderWindow& window) {
    vector<sf::Vector2i> firstEmptyCell;
    sf::Vector2i noEmptyCell(-1, -1);
    for (int i = 0; i < SIZE; ++i)
        firstEmptyCell.push_back(noEmptyCell);
    for (int i = 0; i < SIZE; ++i) {
        sf::Vector2i lowerCell(i, SIZE - 1);
        firstEmptyCell[i] = findEmpty(lowerCell);
    }
    int maxNum = maxNumOfEmpty(firstEmptyCell);
    for (int filledEmptyCells = 0; filledEmptyCells < maxNum; filledEmptyCells++) {
        for (int i = 0; i < SIZE; ++i)
            if (firstEmptyCell[i] != noEmptyCell) {
                dropColumn(firstEmptyCell[i]);
                sf::Vector2i lowerCell(i, SIZE - 1);
                firstEmptyCell[i] = findEmpty(lowerCell);
            }
        window.clear();
        displayGrid(window);
        window.display();
        sf::sleep(sf::seconds(0.1f));
    }
}

int Field::deleteAllMatches() {
    int numOfDeleted = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            sf::Vector2i attendedCell(j, i);
            findForMatch(attendedCell);
        }
    return numOfDeleted = deleteMatches();
}

Bomb::Bomb(int x, int y) : Bonus(x, y) {
    setFillColor(sf::Color(250, 0, 0, 250));
}

Repainter::Repainter(int x, int y, Color_c bonusCellType) : Bonus(x, y) {
    setFillColor(sf::Color(255, 136, 0, 250));
    cellColor = bonusCellType;
}

vector<sf::Vector2i> Bomb::bonusActionCells(Field* field) {
    vector<sf::Vector2i> actionCells;
    actionCells.push_back(bonusCell);
    int randX, randY;
    do {
        randX = rand() % Field::SIZE;
        randY = rand() % Field::SIZE;
        for (int j = 0; j < actionCells.size(); ++j) {
            if (randX == actionCells[j].x && randY == actionCells[j].y)
                break;
            sf::Vector2i oneOfActionCells(randX, randY);
            actionCells.push_back(oneOfActionCells);
        }
    } while (actionCells.size() < 5);
    return actionCells;
}

vector<sf::Vector2i> Repainter::bonusActionCells(Field* field) {
    vector<sf::Vector2i> actionCells;
    actionCells.push_back(bonusCell);
    int randX, randY;
    do {
        randX = rand() % Field::SIZE;
        randY = rand() % Field::SIZE;
        sf::Vector2i oneOfActionCells(randX, randY);
        for (int j = 0; j < actionCells.size(); ++j) {
            if (actionCells[j] == oneOfActionCells || field->isNeighbours(bonusCell, oneOfActionCells))
                break;
            actionCells.push_back(oneOfActionCells);
        }
    } while (actionCells.size() < 5);
    return actionCells;
}

void Bomb::bonusAction(Field* field) {
    vector<sf::Vector2i> deletedCells = bonusActionCells(field);
    for (int i = 0; i < deletedCells.size(); i++)
        field->fieldGrid[deletedCells[i].y][deletedCells[i].x]->deleted();
}

void Repainter::bonusAction(Field* field) {
    vector<sf::Vector2i> repaintedCells = bonusActionCells(field);
    for (int i = 0; i < repaintedCells.size(); ++i) {
        field->fieldGrid[repaintedCells[i].y][repaintedCells[i].x]->setColor(this->getColor());
    }
}
