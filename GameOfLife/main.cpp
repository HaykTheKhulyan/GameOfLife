#include <SFML/Graphics.hpp>
#include "CellGrid.h"
#include <iostream>

void drawGraph(sf::RectangleShape line, sf::RenderWindow& window);

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Conway's Game of Life");
	window.setKeyRepeatEnabled(false);
	
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(900.0f, 1.0f));
	line.setFillColor(sf::Color::Black);
	line.setOrigin(450.0f, 0.5f);

	sf::Texture pauseButtonTexture;
	pauseButtonTexture.loadFromFile("pauseButton.png");

	sf::RectangleShape pauseButton;
	pauseButton.setTexture(&pauseButtonTexture);
	pauseButton.setSize(sf::Vector2f(80.0f, 60.0f));
	pauseButton.setOrigin(40.0f, 30.0f);
	pauseButton.setPosition(sf::Vector2f(950.0f, 50.0f));
	
	sf::Texture	playButtonTexture;
	playButtonTexture.loadFromFile("playButton.png");

	sf::RectangleShape playButton;
	playButton.setTexture(&playButtonTexture);
	playButton.setSize(sf::Vector2f(80.0f, 60.0f));
	playButton.setOrigin(40.0f, 30.0f);
	playButton.setPosition(sf::Vector2f(950.0f, 125.0f));

	CellGrid grid;

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime += clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == event.MouseButtonReleased) {
				if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 20 && sf::Mouse::getPosition(window).y < 80) {
					std::cout << "Pressed pause" << std::endl; 
					grid.pause();
				}
				else if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 95 && sf::Mouse::getPosition(window).y < 155) {
					std::cout << "Pressed play" << std::endl;
					grid.play();
				}
				else if (sf::Mouse::getPosition(window).x < 900) {
					std::cout << "Pressed a cell" << std::endl;
					grid.cellPressed(sf::Mouse::getPosition(window));
				}
			}
				
		}

		//std::cout << sf::Mouse::getPosition(window).x << "   " << sf::Mouse::getPosition(window).y << std::endl;

		if (deltaTime > 0.75f) {
			grid.Update();
			deltaTime = 0;
		}

		window.clear(sf::Color::White);

		window.draw(pauseButton);
		window.draw(playButton);

		grid.Draw(window);
		drawGraph(line, window);

		window.display();
	}

	return 0;
}



void drawGraph(sf::RectangleShape line, sf::RenderWindow& window) {
	for (int i = 0; i <= 900 / 30; i++) {
		line.setRotation(90.0f);
		line.setPosition(sf::Vector2f(i * 30.0f, 450.0f));
		window.draw(line);

		line.setRotation(0.0f);
		line.setPosition(sf::Vector2f(450.0f, i * 30));
		window.draw(line);
	}
	line.setRotation(0.0f);
	line.setPosition(sf::Vector2f(450.0f, 1));
	window.draw(line);
}