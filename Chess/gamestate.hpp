#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#define NUM_SQUARES 64
#define ROW_LENGTH 8
#define COL_LENGTH ROW_LENGTH
#define WINDOW_SIZE 850
#define LABELS_SIZE 50
#define GRAY 0xDC
#define FONT_SIZE 24
#define UNIQUE_PIECES 6

const char numToAlpha[ROW_LENGTH] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
};

const char pieceOrder[UNIQUE_PIECES] = {
    'p', 'r', 'n', 'b', 'q', 'k'
};

enum Square{
    E = 0,
    WP,
    BP,
    WB,
    BB,
    WN,
    BN,
    WR,
    BR,
    WQ,
    BQ,
    WK,
    BK
};

struct Coords {
    int x;
    int y;
    Coords(int x, int y) { this->x = x; this->y = y; }
    void operator=(Coords newCords) {
        x = newCords.x;
        y = newCords.y;
    }

    bool operator==(Coords newCords) {
        return x == newCords.x && y == newCords.y;
    }

    void printCoords() {
        std::cout << x << ", " << y;
    };
};

struct Pieces {
    sf::Image *WP;
    sf::Image *BP;
    sf::Image *WB;
    sf::Image *BB;
    sf::Image *WN;
    sf::Image *BN;
    sf::Image *WR;
    sf::Image *BR;
    sf::Image *WQ;
    sf::Image *BQ;
    sf::Image *WK;
    sf::Image *BK;

    sf::Image* pieceInd[UNIQUE_PIECES*2+1] = { NULL, WP, BP, WB, BB, WN, BN, WR, BR, WQ, BQ, WK, BK};

    ~Pieces() {
        for (int i = 1; i < UNIQUE_PIECES * 2 + 1; i++) {
            delete pieceInd[i];
        }
    }
};


class GameState {
    public:
        GameState();
        GameState(bool whiteMove, char board[ROW_LENGTH][COL_LENGTH]);
        ~GameState();
        uint8_t board[8][8] = {
            {BR, BK, BB, BQ, BK, BB, BN, BR},
            {BP, BP, BP, BP, BP, BP, BP, BP},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {WR, WK, WB, WQ, WK, WB, WN, WR},
            {WP, WP, WP, WP, WP, WP, WP, WP},

        };
        bool whiteMove;
        void drawBoard();
        static Coords getSquare(sf::Event::MouseButtonEvent event);

        sf::RenderWindow* window;
        sf::RectangleShape squares[ROW_LENGTH][COL_LENGTH];
        Pieces pieces;
        sf::Text labels[ROW_LENGTH + COL_LENGTH];
        sf::Font font;

    private:
        void initDrawables();
};