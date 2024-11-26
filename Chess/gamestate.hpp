#include <stdint.h>
#include <SFML/Graphics.hpp>

#define NUM_SQUARES 64
#define ROW_LENGTH 8
#define COL_LENGTH ROW_LENGTH
#define WINDOW_SIZE 850
#define LABELS_SIZE 50
#define GRAY 0xDC
#define FONT_SIZE 24

const char numToAlpha[ROW_LENGTH] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'
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
        sf::RenderWindow* window;
        sf::RectangleShape squares[ROW_LENGTH][COL_LENGTH];
        sf::Text labels[ROW_LENGTH + COL_LENGTH];
        sf::Font font;

    private:
        void initSquares();
};