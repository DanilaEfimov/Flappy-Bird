#pragma once
#include"Window.h"

class Bird
{
private:
	
	sf::Texture textureBack;
	sf::Texture textureBird;
	sf::Sprite backGround;
	
	// Physics
	unsigned jumpTimer;
	unsigned maxJumpTimer;
	bool held;
	sf::Vector2f pos;
	sf::Vector2f speedUp;
	sf::Vector2f speedDown;
	// after add mass for change hard of game

	// Sounds
	sf::Music BakAI;
	sf::Music BakDeer;
	sf::Music jump;

	bool endGame;

	// Initialize
	void initVariables();
	void initBird();

public:
	sf::CircleShape body;

	// constructor & destructor
	Bird();
	virtual ~Bird();

	// Accessors
	const unsigned getGameTime() const;
	const bool getEndGame() const;
	const sf::Vector2f getSpeedUp() const;
	const sf::Vector2f getSpeedDown() const;

	// Physics
	void setPhysic(float winY, std::string winType);
	void update(float winY, std::string winType, std::vector<sf::RectangleShape> tubes);
	void detectCoalision(std::vector<sf::RectangleShape> tubes);

	// Render
	/*
		Here we call the Window Class for getting info
		about window where we will render our Bird
		I've try some ways and pointer works (look in "Flappy bird.cpp")
	*/
	void renderBird(sf::RenderWindow* window);

};

