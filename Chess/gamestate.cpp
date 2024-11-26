#include "gamestate.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>



GameState::GameState() {
    this->whiteMove = true;
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!", sf::Style::Titlebar);
    window->setTitle("meow");

    initSquares();
}

GameState::GameState(bool whiteMove, char board[ROW_LENGTH][COL_LENGTH]) {
    this->whiteMove = whiteMove;
    memcpy(this->board, board, 64);
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML works!", sf::Style::Titlebar);

    initSquares();
}

GameState::~GameState() {
    delete this->window;
}

void GameState::initSquares() {

    if (!font.loadFromFile("./Assets/arial.ttf")) {
        printf("error\n");
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
}

void GameState::drawBoard() {
    for (int i = 0; i < ROW_LENGTH; i++) {
        window->draw(labels[i]);
        window->draw(labels[i + ROW_LENGTH]);
        for (int j = 0; j < COL_LENGTH; j++) {
            window->draw(squares[i][j]);
        }
    }
}