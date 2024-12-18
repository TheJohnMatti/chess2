#include "gamestate.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>



GameState::GameState() {
    this->whiteMove = true;
    this->whiteCastlingRights = KINGSIDE_CASTLE | QUEENSIDE_CASTLE;
    this->blackCastlingRights = KINGSIDE_CASTLE | QUEENSIDE_CASTLE;
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!", sf::Style::Close);
    window->setTitle("Chess Engine");

    initDrawables();
}

GameState::GameState(bool whiteMove, char board[ROW_LENGTH][COL_LENGTH]) {
    this->whiteMove = whiteMove;
    memcpy(this->board, board, 64);
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!", sf::Style::Close);

    initDrawables();
}

GameState::~GameState() {
    delete this->window;
}

void GameState::initDrawables() {

    if (!font.loadFromFile("./assets/arial.ttf")) {
        printf("error loading font\n");
    }

    const char numToAlpha[ROW_LENGTH] = {
    'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'
    };

    for (int i = 0; i < ROW_LENGTH; i++) {
        
        labels[i].setFont(font);
        labels[i + ROW_LENGTH].setFont(font);
        labels[i].setCharacterSize(FONT_SIZE);
        labels[i + ROW_LENGTH].setCharacterSize(FONT_SIZE);
        labels[i].setString(sf::String((char)(COL_LENGTH - i + '0')));
        labels[i + ROW_LENGTH].setString(sf::String(numToAlpha[COL_LENGTH-i-1]));
        labels[i].setPosition(sf::Vector2f(25.f - FONT_SIZE/2, i * 100 + 50 - FONT_SIZE/2));
        labels[i + ROW_LENGTH].setPosition(sf::Vector2f(i * 100 + 50 + LABELS_SIZE - FONT_SIZE/2, WINDOW_SIZE - 25 - FONT_SIZE/2));
        labels[i].setFillColor(sf::Color::Black);
        labels[i + ROW_LENGTH].setFillColor(sf::Color::Black);
        for (int j = 0; j < COL_LENGTH; j++) {
            int ind = i + j;
            squares[i][j].setSize(sf::Vector2f(100.f, 100.f));
            squares[i][j].setPosition(sf::Vector2f(100.f * j + LABELS_SIZE, 100.f * i));
            squares[i][j].setFillColor(ind % 2 ? sf::Color::Green : sf::Color::White);
        }
    }

    for (int i = 0; i < UNIQUE_PIECES * 2; i++) {
        pieces.pieceInd[i] = new sf::Sprite();
    }


    textures[0].loadFromFile("./assets/Chess_plt60.png", sf::IntRect(100, 100, 0, 0));
    textures[1].loadFromFile("./assets/Chess_pdt60.png", sf::IntRect(100, 100, 0, 0));
    textures[2].loadFromFile("./assets/Chess_blt60.png", sf::IntRect(100, 100, 0, 0));
    textures[3].loadFromFile("./assets/Chess_bdt60.png", sf::IntRect(100, 100, 0, 0));
    textures[4].loadFromFile("./assets/Chess_nlt60.png", sf::IntRect(100, 100, 0, 0));
    textures[5].loadFromFile("./assets/Chess_ndt60.png", sf::IntRect(100, 100, 0, 0));
    textures[6].loadFromFile("./assets/Chess_rlt60.png", sf::IntRect(100, 100, 0, 0));
    textures[7].loadFromFile("./assets/Chess_rdt60.png", sf::IntRect(100, 100, 0, 0));
    textures[8].loadFromFile("./assets/Chess_qlt60.png", sf::IntRect(100, 100, 0, 0));
    textures[9].loadFromFile("./assets/Chess_qdt60.png", sf::IntRect(100, 100, 0, 0));
    textures[10].loadFromFile("./assets/Chess_klt60.png", sf::IntRect(100, 100, 0, 0));
    textures[11].loadFromFile("./assets/Chess_kdt60.png", sf::IntRect(100, 100, 0, 0));

    for (int i = 0; i < UNIQUE_PIECES * 2; i++) {
        pieces.pieceInd[i]->setTexture(textures[i]);
        pieces.pieceInd[i]->setScale(IMAGE_SCALE_MULTIPLIER, IMAGE_SCALE_MULTIPLIER);
    }

}

void GameState::drawBoard() {
    for (int i = 0; i < ROW_LENGTH; i++) {
        window->draw(labels[i]);
        window->draw(labels[i + ROW_LENGTH]);
        for (int j = 0; j < COL_LENGTH; j++) {
            window->draw(squares[i][j]);
            if (board[i][j] != E) {
                sf::Sprite* curImg = pieces.pieceInd[board[i][j] - 1];
                memcpy(&sprites[i][j], curImg, sizeof(sf::Sprite));
            }
            else {
                sprites[i][j] = sf::Sprite();
            }
            sprites[i][j].setPosition(sf::Vector2f(100.f * j + LABELS_SIZE, 100.f * i));
            window->draw(sprites[i][j]);
        }
    }
}

Coords GameState::getSquare(sf::Event::MouseButtonEvent event) {
    if (event.x < LABELS_SIZE || event.x > WINDOW_SIZE || event.y < 0 || event.y > WINDOW_SIZE-LABELS_SIZE) return Coords(-1, -1);
    return Coords((int)((event.x - 50) / 100), (int)(event.y / 100));
}

void GameState::makeMove(Coords from, Coords to) {
    int movingPiece = board[from.y][from.x];
    /*if (isCastle(from, to)) {

    }*/
    int moveType = this->isLegalMove(from, to);
    if (!moveType || (movingPiece && (movingPiece % 2 == 1) ^ whiteMove)) return;
    board[to.y][to.x] = board[from.y][from.x];
    board[from.y][from.x] = E;
    printf("%d - %d\n", moveType, isPawnPromotion(from, to));
    if (moveType == PAWNMOVE && isPawnPromotion(from, to)) {
        printf("PAWN PROMOTION\n");
        board[to.y][to.x] = movingPiece % 2 ? WQ : BQ;
    }
    whiteMove = !whiteMove;
}

int GameState::isLegalMove(Coords from, Coords to) {
    if (isSelfCapture(from, to)) return false;
    switch (board[from.y][from.x]) {
        case (E):
            return false;
        case (WK):
        case (BK):
            return (abs(from.x - to.x) <= 1 && abs(from.y - to.y) <= 1)*KINGMOVE;
        case (WQ):
        case (BQ):
            return (isRookMove(from, to) || isBishopMove(from, to))*QUEENMOVE;
        case (WR):
        case (BR):
            return isRookMove(from, to)*ROOKMOVE;
        case (WB):
        case (BB):
            return isBishopMove(from, to)*BISHOPMOVE;
        case (WN):
        case (BN):
            return isKnightMove(from, to)*KNIGHTMOVE;
        case (WP):
        case (BP):
            return isPawnMove(from, to)*PAWNMOVE;
        
    }

    return true;
}

bool GameState::isRookMove(Coords from, Coords to) {
    if (from.x == to.x) {
        for (int i = from.y + (from.y > to.y ? -1 : 1); i != to.y; from.y > to.y ? i-- : i++) {
            if (board[i][from.x] != E) return false;
        }
        return true;
    }
    if (from.y == to.y) {
        for (int i = from.x + (from.x > to.x ? -1 : 1); i != to.x; from.x > to.x ? i-- : i++) {
            if (board[from.y][i] != E) return false;
        }
        return true;
    }


    return false;
}

bool GameState::isBishopMove(Coords from, Coords to) {
    if ((abs(from.x - to.x) != abs(from.y - to.y))) return false;
    int dirs[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    int dir[2];
    memcpy(dir, (to.x > from.x) && (to.y > from.y) ? dirs[0] :
        (to.x > from.x) && (to.y < from.y) ? dirs[1] :
        (to.x < from.x) && (to.y > from.y) ? dirs[2] : 
        (to.x < from.x) && (to.y < from.y) ? dirs[3] : dirs[0], 2*sizeof(int));
    int curX = from.x;
    int curY = from.y;
    curX += dir[0];
    curY += dir[1];
    while (curX != to.x) {
        if (curX > COL_LENGTH || curY > ROW_LENGTH) return false;
        if (board[curY][curX] != E) return false;
        curX += dir[0];
        curY += dir[1];
    }
    return true;
}

bool GameState::isKnightMove(Coords from, Coords to) {
    return (abs(from.x - to.x) == 2 && abs(from.y - to.y) == 1) || (abs(from.x - to.x) == 1 && abs(from.y - to.y) == 2);
}
bool GameState::isPawnMove(Coords from, Coords to) {
    int fromPiece = board[from.y][from.x];
    int destPiece = board[to.y][to.x];
    if (fromPiece == WP) {
        if (from.y - 1 == to.y) {
            if (from.x == to.x && destPiece == E) return true;
            if (abs(from.x - to.x) == 1 && destPiece && destPiece % 2 == 0) return true;
        } 
        else if (from.y - 2 == to.y) {
            if (from.y == 6 && from.x == to.x) return true;
        }
    }
    else if (fromPiece == BP) {
        if (from.y + 1 == to.y) {
            if (from.x == to.x && destPiece == E) return true;
            if (abs(from.x - to.x) == 1 && destPiece % 2 == 1) return true;
        }
        else if (from.y + 2 == to.y) {
            if (from.y == 1 && from.x == to.x) return true;
        }
    }
    return false;
}
bool GameState::isSelfCapture(Coords from, Coords to) {
    return board[to.y][to.x] != E && board[from.y][from.x] % 2 == board[to.y][to.x] % 2;
}

bool GameState::isPawnPromotion(Coords from, Coords to) {
    if (board[to.y][to.x] && board[to.y][to.x] % 2 == 0 && to.y == COL_LENGTH - 1) return true;
    if (board[to.y][to.x] % 2 && to.y == 0) return true;
    return false;
}