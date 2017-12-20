#pragma once
#include <SFML/Graphics.hpp>

class Slider {
public:
	Slider();
	~Slider();




	void Draw(sf::RenderWindow& window);


private:
	sf::Texture sliderFrameTexture;
	sf::RectangleShape sliderFrame;

	sf::Texture sliderButtonTexture;
	sf::RectangleShape sliderButton;
};

