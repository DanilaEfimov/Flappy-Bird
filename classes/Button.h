#pragma once
#include<iostream>
#include<vector>

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
// предварительно скомпилированные заголовки

class Button
{
private:
	
	// Text
	std::string name;
	sf::Font font;
	sf::Text text;

	void initMolds();
	void initText();

public:
	Button();
	virtual ~Button();

	// Molds
	sf::RectangleShape button;
	sf::RectangleShape perCents;

	// Acccessors
	const sf::Vector2f getButtonSize() const;
	const sf::Vector2f getButtonPos() const;

	// Update
	void updateButton(float clickX);
	void changeButtonName(std::string newName);
	void changeButtonPos(sf::Vector2f newPos);

	// render
	void renderButton(sf::RenderWindow* pWin);
};

