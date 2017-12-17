#pragma once
#include "SFML/Graphics.hpp"

class Cell
{
public:
	Cell();
	~Cell();

	void setPosition(sf::Vector2f position);
	sf::RectangleShape getCell();
	void kill();
	void giveLife();
	
	bool isAlive = false;
	bool isChanging= false;
	
private:
	sf::RectangleShape cell;
};

