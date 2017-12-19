#pragma once
#include "Cell.h"
#include "SFML\Graphics.hpp"

class CellGrid {
public:
	CellGrid();
	~CellGrid();

	void Update();
	void Draw(sf::RenderWindow& window);

	void cellPressed(sf::Vector2i mousePosition);
	void kill(sf::Vector2i mousePosition);
	void giveLife(sf::Vector2i mousePosition);
	bool isAlive(sf::Vector2i mousePosition);

	void pause();
	void play();
	void clear();
	

private:
	int numNeighbors(int row, int col);

	Cell cell;
	Cell grid[30][30];

	bool isRunning = false;
};

