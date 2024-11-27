#include <iostream>
#include <SFML/Graphics.hpp>
#include "gamestate.hpp"


Coords currentMover(-1, -1);

int main(int argc, char* argv[]) {
	GameState game;

	while (game.window->isOpen()) {
		sf::Event event;
		while (game.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				game.window->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				currentMover = game.getSquare(event.mouseButton);
				if (currentMover.y == -1) continue;
				std::cout << currentMover.x << '\t' << currentMover.y << std::endl;
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				Coords destSquare = game.getSquare(event.mouseButton);
				if (destSquare == currentMover) {
					std::cout << "Cancel Move" << std::endl;
				}
				else {
					std::cout << "Move from ";
					currentMover.printCoords();
					std::cout << " to ";
					destSquare.printCoords();
					std::cout << std::endl;
				}
			}
		}
		game.window->clear(sf::Color(GRAY, GRAY, GRAY, 255));
		game.drawBoard();
		game.window->display();
	}
}