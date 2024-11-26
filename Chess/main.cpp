#include <iostream>
#include <SFML/Graphics.hpp>
#include "gamestate.hpp"


int main() {
	GameState game;

	while (game.window->isOpen()) {
		sf::Event event;
		while (game.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				game.window->close();
		}
		game.window->clear(sf::Color(GRAY, GRAY, GRAY, 255));
		game.drawBoard();
		game.window->display();
	}
}