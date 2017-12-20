/* Game of Life

Future Features:
	-pencil/eraser to intuitively draw or erase		(DONE)
	-modifiable generation speed (first implement slider, then a custom entered number as well)
	-save/load templates
	-modifiable grid size?
*/

#include <SFML/Graphics.hpp>
#include "CellGrid.h"
#include "Slider.h"
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
	pauseButton.setPosition(950.0f, 50.0f);
	
	sf::Texture	playButtonTexture;
	playButtonTexture.loadFromFile("playButton.png");

	sf::RectangleShape playButton;
	playButton.setTexture(&playButtonTexture);
	playButton.setSize(sf::Vector2f(80.0f, 60.0f));
	playButton.setOrigin(40.0f, 30.0f);
	playButton.setPosition(950.0f, 125.0f);

	sf::Texture	pencilButtonTexture;
	pencilButtonTexture.loadFromFile("pencilButton.png");

	sf::RectangleShape pencil;
	pencil.setTexture(&pencilButtonTexture);
	pencil.setSize(sf::Vector2f(20.0f, 20.0f));
	pencil.setOrigin(10.0f, 10.0f);
	pencil.setPosition(920.0f, 180.0f);

	sf::Texture	eraserButtonTexture;
	eraserButtonTexture.loadFromFile("eraserButton.png");

	sf::RectangleShape eraser;
	eraser.setTexture(&eraserButtonTexture);
	eraser.setSize(sf::Vector2f(20.0f, 20.0f));
	eraser.setOrigin(10.0f, 10.0f);
	eraser.setPosition(950.0f, 180.0f);

	sf::Texture	trashButtonTexture;
	trashButtonTexture.loadFromFile("trashButton.png");

	sf::RectangleShape trash;
	trash.setTexture(&trashButtonTexture);
	trash.setSize(sf::Vector2f(20.0f, 20.0f));
	trash.setOrigin(10.0f, 10.0f);
	trash.setPosition(980.0f, 180.0f);

	CellGrid grid;
	Slider slider;

	bool mousePressed = false;
	bool killing = false;

	// keeps track of the time since the last update
	float deltaTime = 0.0f;
	sf::Clock clock;

	float cycleTime = 0.5f;

	while (window.isOpen()) {
		// this restarts the clock and adds the elapsed time since the last restart to deltaTime
		deltaTime += clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == event.MouseButtonPressed)
				mousePressed = true;
			else if (event.type == event.MouseButtonReleased) {
				mousePressed = false;
				if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 20 && sf::Mouse::getPosition(window).y < 80) {
					std::cout << "Pressed pause" << std::endl; 
					grid.pause();
				}
				else if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 95 && sf::Mouse::getPosition(window).y < 155) {
					std::cout << "Pressed play" << std::endl;
					grid.play();
				}
				else if (sf::Mouse::getPosition(window).x > 910 && sf::Mouse::getPosition(window).x < 930 && sf::Mouse::getPosition(window).y > 170 && sf::Mouse::getPosition(window).y < 190) {
					std::cout << "Pressed pencil" << std::endl;
					killing = false;
				}
				else if (sf::Mouse::getPosition(window).x > 940 && sf::Mouse::getPosition(window).x < 960 && sf::Mouse::getPosition(window).y > 170 && sf::Mouse::getPosition(window).y < 190) {
					std::cout << "Pressed eraser" << std::endl;
					killing = true;
				}
				else if (sf::Mouse::getPosition(window).x > 970 && sf::Mouse::getPosition(window).x < 990 && sf::Mouse::getPosition(window).y > 170 && sf::Mouse::getPosition(window).y < 190) {
					std::cout << "Pressed clear" << std::endl;
					grid.clear();
				}

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

		if (deltaTime > cycleTime) {
			grid.Update();
			// sets deltaTime = to zero, thereby "ending" the current cycle 
			deltaTime = 0;
		}

		window.clear(sf::Color::White);

		window.draw(pauseButton);
		window.draw(playButton);
		window.draw(pencil);
		window.draw(eraser);
		window.draw(trash);

		grid.Draw(window);
		slider.Draw(window);

		drawGraph(window);

		window.display();
	}

	return 0;
}



void drawGraph(sf::RenderWindow& window) {
	sf::RectangleShape line;
	line.setSize(sf::Vector2f(900.0f, 1.0f));
	line.setFillColor(sf::Color::Black);
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