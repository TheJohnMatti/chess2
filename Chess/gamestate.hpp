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
#define IMAGE_SCALE_MULTIPLIER 1.6667

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
    sf::Sprite *WP;
    sf::Sprite *BP;
    sf::Sprite *WB;
    sf::Sprite *BB;
    sf::Sprite *WN;
    sf::Sprite *BN;
    sf::Sprite *WR;
    sf::Sprite *BR;
    sf::Sprite *WQ;
    sf::Sprite *BQ;
    sf::Sprite *WK;
    sf::Sprite *BK;

    sf::Sprite* pieceInd[UNIQUE_PIECES*2] = { WP, BP, WB, BB, WN, BN, WR, BR, WQ, BQ, WK, BK};

    ~Pieces() {
        for (int i = 0; i < UNIQUE_PIECES * 2; i++) {
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
            {BR, BN, BB, BQ, BK, BB, BN, BR},
            {BP, BP, BP, BP, BP, BP, BP, BP},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {E, E, E, E, E, E, E, E},
            {WP, WP, WP, WP, WP, WP, WP, WP},
            {WR, WN, WB, WQ, WK, WB, WN, WR},
        };
        bool whiteMove;
        void drawBoard();
        void makeMove(Coords from, Coords to);
        static Coords getSquare(sf::Event::MouseButtonEvent event);
        sf::RenderWindow* window;

    private:
        void initDrawables();
        bool isLegalMove(Coords from, Coords to);
        bool isRookMove(Coords from, Coords to);
        bool isBishopMove(Coords from, Coords to);
        bool isKnightMove(Coords from, Coords to);
        bool isPawnMove(Coords from, Coords to);
        bool isSelfCapture(Coords from, Coords to);
        sf::RectangleShape squares[ROW_LENGTH][COL_LENGTH];
        Pieces pieces;
        sf::Text labels[ROW_LENGTH + COL_LENGTH];
        sf::Font font;
        sf::Texture textures[2 * UNIQUE_PIECES];
        sf::Sprite sprites[ROW_LENGTH][COL_LENGTH];
};