#include "CellGrid.h"
#include "Cell.h"
#include <iostream>

CellGrid::CellGrid() {
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++) {
			grid[i][j] = cell;
			grid[i][j].setPosition(sf::Vector2f(15.0f + (j * 30), 15 + (i * 30)));
		}
}


CellGrid::~CellGrid() {
}

void CellGrid::Update() {
	//variable for the number of neighbors for a given cell
	int num = 0;

	// if not paused
	if (isRunning)
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++) {
				num = numNeighbors(i, j);
				//std::cout << num << std::endl;
				if (grid[i][j].isAlive) {
					if (num == 0 || num == 1 || num == 4 || num == 5 || num == 6 || num == 7 || num == 8)
						grid[i][j].kill();
					else if (num == 2 || num == 3)
						grid[i][j].isAlive = true;
				}
				else
					if (num == 3)
						grid[i][j].giveLife();
			}

	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			if (grid[i][j].isChanging) {
				grid[i][j].isAlive = !grid[i][j].isAlive;
				grid[i][j].isChanging = false;
			}
}

void CellGrid::Draw(sf::RenderWindow& window) {
	for (int i = 0; i < 30; i++) 
		for (int j = 0; j < 30; j++) {
			if (grid[i][j].isAlive)
				window.draw(grid[i][j].getCell());
		}
}

void CellGrid::cellPressed(sf::Vector2i mousePosition) {
	int cellRow = mousePosition.y / 30;
	int cellCol = mousePosition.x / 30;

	if (grid[cellRow][cellCol].isAlive)
		grid[cellRow][cellCol].kill();
	else
		grid[cellRow][cellCol].giveLife();

	if (grid[cellRow][cellCol].isChanging) {
		grid[cellRow][cellCol].isAlive = !grid[cellRow][cellCol].isAlive;
		grid[cellRow][cellCol].isChanging = false;
	}
}

void CellGrid::kill(sf::Vector2i mousePosition) {
	int cellRow = mousePosition.y / 30;
	int cellCol = mousePosition.x / 30;

	grid[cellRow][cellCol].kill();
}

void CellGrid::giveLife(sf::Vector2i mousePosition) {
	int cellRow = mousePosition.y / 30;
	int cellCol = mousePosition.x / 30;

	grid[cellRow][cellCol].giveLife();
}

bool CellGrid::isAlive(sf::Vector2i mousePosition) {
	int cellRow = mousePosition.y / 30;
	int cellCol = mousePosition.x / 30;

	if (grid[cellRow][cellCol].isAlive)
		return true;
	else
		return false;
}

void CellGrid::pause() {
	isRunning = false;
}

void CellGrid::play() {
	isRunning = true;
}

void CellGrid::clear() {
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++) {
			grid[i][j].isAlive = false;
		}
	isRunning = false;
}

int CellGrid::numNeighbors(int row, int col)
{
	int count = 0;
	
	bool topRow = false;
	bool bottomRow = false;
	bool leftCol = false;
	bool rightCol = false;

	if (row == 0) 
		topRow = true;
	if (row == 29)
		bottomRow = true;
	if (col == 0)
		leftCol = true;
	if (col == 29)
		rightCol = true;

	if (!topRow) {
		if (!leftCol)
			if (grid[row - 1][col - 1].isAlive)
				count++;
		if (grid[row - 1][col].isAlive)
			count++;
		if (!rightCol)
			if (grid[row - 1][col + 1].isAlive)
				count++;
	}

	if (!leftCol) {
		if (grid[row][col - 1].isAlive)
			count++;
	}
	if (!rightCol) {
		if (grid[row][col + 1].isAlive)
			count++;
	}

	if (!bottomRow) {
		if (!leftCol)
			if (grid[row + 1][col - 1].isAlive)
				count++;
		if (grid[row + 1][col].isAlive)
			count++;
		if (!rightCol)
			if (grid[row + 1][col + 1].isAlive)
				count++;
	}

	return count;

	topRow = false;
	bottomRow = false;
	leftCol = false;
	rightCol = false;
}

