#pragma once
#include"Button.h"
#include"Bird.h"
#include<ctime>

class Tube
{
private:
	// Molds
	sf::RectangleShape bigTube;
	sf::RectangleShape hole;
	float holeWidth;

	// Textures
	sf::Texture textureBigPart;
	sf::Texture textureHole;
	const sf::Texture* tTube;

	sf::Vector2f speed;

	// Game logic
	Window gameWinCopy;
	Bird birdCopy;
	unsigned cloneTimer;
	sf::Vector2f cloneSpeedUp;
	sf::Vector2f cloneSpeedDown;
	sf::Vector2f cloneWinSize;

	unsigned maxTubesCount;
	float distance; // max distance timer;
	float distanceTimer;
	float U; // vertical interval beetwen tubes

	float epsilon; // for hard (bigger -> harder)
	float delta; // for custom (bigger -> littel easier & more boring)

	void initVariables(float eps, float del);

public:
	std::vector<sf::RectangleShape> tubes;

	// constructor & dectructor
	Tube(float eps, float del);
	virtual ~Tube();

	// Acsessors
	const sf::Vector2f getSpeed() const;
	void setHard(float h);
	void setBonus(float b);

	void spawnTubes();
	void updateTubes();

	// Rendering 
	void renderTubes(sf::RenderWindow* window);
};

