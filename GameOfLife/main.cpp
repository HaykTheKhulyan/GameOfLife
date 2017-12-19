/* Game of Life

Future Features:
	-pencil/eraser to intuitively draw or erase
	-modifiable generation speed
	-save/load templates
	-modifiable grid size?
*/

#include <SFML/Graphics.hpp>
#include "CellGrid.h"
#include <iostream>

void drawGraph(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 900), "Conway's Game of Life");
	window.setKeyRepeatEnabled(false);
	

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

	sf::Texture	clearButtonTexture;
	clearButtonTexture.loadFromFile("clearButton.png");

	sf::RectangleShape clearButton;
	clearButton.setTexture(&clearButtonTexture);
	clearButton.setSize(sf::Vector2f(80.0f, 60.0f));
	clearButton.setOrigin(40.0f, 30.0f);
	clearButton.setPosition(sf::Vector2f(950.0f, 200.0f));

	sf::Texture	pencilButtonTexture;
	pencilButtonTexture.loadFromFile("pencilButton.png");

	sf::RectangleShape pencil;
	pencil.setTexture(&pencilButtonTexture);
	pencil.setSize(sf::Vector2f(20.0f, 20.0f));
	pencil.setOrigin(10.0f, 10.0f);
	pencil.setPosition(sf::Vector2f(920.0f, 255.0f));

	sf::Texture	eraserButtonTexture;
	eraserButtonTexture.loadFromFile("eraserButton.png");

	sf::RectangleShape eraser;
	eraser.setTexture(&eraserButtonTexture);
	eraser.setSize(sf::Vector2f(20.0f, 20.0f));
	eraser.setOrigin(10.0f, 10.0f);
	eraser.setPosition(sf::Vector2f(950.0f, 255.0f));

	sf::Texture	trashButtonTexture;
	trashButtonTexture.loadFromFile("trashButton.png");

	sf::RectangleShape trash;
	trash.setTexture(&trashButtonTexture);
	trash.setSize(sf::Vector2f(20.0f, 20.0f));
	trash.setOrigin(10.0f, 10.0f);
	trash.setPosition(sf::Vector2f(980.0f, 255.0f));

	CellGrid grid;

	bool pencil2 = true;
	bool mousePressed = false;
	bool killing;

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime += clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == event.MouseButtonReleased) {
				mousePressed = false;
				if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 20 && sf::Mouse::getPosition(window).y < 80) {
					std::cout << "Pressed pause" << std::endl; 
					grid.pause();
				}
				else if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 95 && sf::Mouse::getPosition(window).y < 155) {
					std::cout << "Pressed play" << std::endl;
					grid.play();
				}
				else if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 170 && sf::Mouse::getPosition(window).y < 230) {
					std::cout << "Pressed clear" << std::endl;
					grid.clear();
				}
			}
			if (event.type == event.MouseButtonPressed) {
				if (grid.isAlive(sf::Mouse::getPosition(window)) && !mousePressed)
					killing = true;
				else
					killing = false;
				mousePressed = true;
			}
				
		}

		if (mousePressed) {
			if (sf::Mouse::getPosition(window).x < 900) {
				if (killing) {
					if (grid.isAlive(sf::Mouse::getPosition(window))) {
						grid.cellPressed(sf::Mouse::getPosition(window));
					}
				}	
				else {
					if (!grid.isAlive(sf::Mouse::getPosition(window))) {
						grid.cellPressed(sf::Mouse::getPosition(window));
					}
				}
			}
		}

		//std::cout << sf::Mouse::getPosition(window).x << "   " << sf::Mouse::getPosition(window).y << std::endl;

		if (deltaTime > 0.5f) {
			grid.Update();
			deltaTime = 0;
		}

		window.clear(sf::Color::Black);

		window.draw(pauseButton);
		window.draw(playButton);
		window.draw(clearButton);
		window.draw(pencil);
		window.draw(eraser);
		window.draw(trash);

		grid.Draw(window);
		drawGraph(window);

		window.display();
	}

	return 0;
}



void drawGraph(sf::RenderWindow& window) {
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(900.0f, 1.0f));
	line.setFillColor(sf::Color::White);
	line.setOrigin(450.0f, 0.5f);

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