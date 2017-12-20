#include "Slider.h"



Slider::Slider() {
	sliderFrameTexture.loadFromFile("sliderFrame.png");
	sliderFrame.setTexture(&sliderFrameTexture);
	sliderFrame.setSize(sf::Vector2f(20.0f, 90.0f));
	sliderFrame.setOrigin(10.0f, 45.0f);
	sliderFrame.setPosition(930.0f, 260.0f);

	sliderButtonTexture.loadFromFile("sliderButton.png");
	sliderButton.setTexture(&sliderButtonTexture);
	sliderButton.setSize(sf::Vector2f(20.0f, 8.0f));
	sliderButton.setOrigin(10.0f, 4.0f);
	sliderButton.setPosition(930.0f, 260.0f);
}


Slider::~Slider() {
}

void Slider::Draw(sf::RenderWindow & window) {
	window.draw(sliderFrame);
	window.draw(sliderButton);
}
