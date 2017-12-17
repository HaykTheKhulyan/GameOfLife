#include "Cell.h"

Cell::Cell() {
	cell.setSize(sf::Vector2f(28.0f, 28.0f));
	cell.setFillColor(sf::Color(255, 0, 0));
	cell.setOrigin(14.0f, 14.0f);
	cell.setPosition(sf::Vector2f(500.0f, 500.0f));
}


Cell::~Cell() {
}

void Cell::setPosition(sf::Vector2f position) {
	cell.setPosition(position);
}

sf::RectangleShape Cell::getCell() {
	return cell;
}

void Cell::kill() {
	isChanging = true;
}

void Cell::giveLife() {
	isChanging = true;
}
