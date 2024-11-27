#include "gamestate.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>



GameState::GameState() {
    this->whiteMove = true;
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!", sf::Style::Close);
    window->setTitle("meow");

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
        labels[i].setString(sf::String(numToAlpha[i]));
        labels[i + ROW_LENGTH].setString(sf::String((char)(i + 1 + '0')));
        labels[i].setPosition(sf::Vector2f(25.f - FONT_SIZE/2, i * 100 + 50 - FONT_SIZE/2));
        labels[i + ROW_LENGTH].setPosition(sf::Vector2f(i * 100 + 50 + LABELS_SIZE - FONT_SIZE/2, WINDOW_SIZE - 25 - FONT_SIZE/2));
        labels[i].setFillColor(sf::Color::Black);
        labels[i + ROW_LENGTH].setFillColor(sf::Color::Black);
        for (int j = 0; j < COL_LENGTH; j++) {
            int ind = i + j;
            squares[i][j].setSize(sf::Vector2f(100.f, 100.f));
            squares[i][j].setPosition(sf::Vector2f(100.f * i+LABELS_SIZE, 100.f * j));
            squares[i][j].setFillColor(ind % 2 ? sf::Color::Green : sf::Color::White);
        }
    }

    for (int i = 1; i < UNIQUE_PIECES * 2 + 1; i++) {
        pieces.pieceInd[i] = new sf::Image();
    }

    pieces.WP->loadFromFile("./assets/Chess_plt60.png");
    pieces.BP->loadFromFile("./assets/Chess_pdt60.png");
    pieces.WB->loadFromFile("./assets/Chess_blt60.png");
    pieces.BB->loadFromFile("./assets/Chess_bdt60.png");
    pieces.WN->loadFromFile("./assets/Chess_nlt60.png");
    pieces.BN->loadFromFile("./assets/Chess_ndt60.png");
    pieces.WR->loadFromFile("./assets/Chess_rlt60.png");
    pieces.BR->loadFromFile("./assets/Chess_rdt60.png");
    pieces.WQ->loadFromFile("./assets/Chess_qlt60.png");
    pieces.BQ->loadFromFile("./assets/Chess_qdt60.png");
    pieces.WK->loadFromFile("./assets/Chess_qlt60.png");
    pieces.BK->loadFromFile("./assets/Chess_qdt60.png");
}

void GameState::drawBoard() {
    for (int i = 0; i < ROW_LENGTH; i++) {
        window->draw(labels[i]);
        window->draw(labels[i + ROW_LENGTH]);
        for (int j = 0; j < COL_LENGTH; j++) {
            window->draw(squares[i][j]);
            if (board[i][j] == E) continue;
            sf::Image* curImg = pieces.pieceInd[board[i][j]];
            //window->draw(*curImg);
            //curImg->(sf::Vector2f(100.f * i + LABELS_SIZE, 100.f * j));
        }
    }
}

Coords GameState::getSquare(sf::Event::MouseButtonEvent event) {
    if (event.x < 50 || event.x > 850 || event.y < 0 || event.y > 800) return Coords(-1, -1);
    return Coords((int)((event.x - 50) / 100), (int)(event.y / 100));
}