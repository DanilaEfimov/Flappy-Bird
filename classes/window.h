#pragma once
#include"Button.h"

class Window
{
private:
	sf::RenderWindow* gameWin;
	sf::RenderWindow* menuWin;
	sf::RenderWindow* settingWin;
	sf::VideoMode videoMode;
	std::string winType; // Menu, Settings, Game...
	sf::Event event;

	// Molds
	Button hard;
	Button bonus;

	// Game Logic
	bool endGame;
	float epsilone;
	float delta;

	// Initialize
	void initVariables();
	void initWindows();

public:
	Window();
	virtual ~Window();
	void DESTRUCT();

	// Accessors
	const bool running() const;
	const std::string getWinType() const;
	const sf::Vector2f getWindowSize() const;
	const float getHard() const;
	const float getBonus() const;
	
	// for entityes, they know where they must render
	// what must render there and all that
	sf::RenderWindow* getWindow();
	void settingsLoop();

	// Updating
	void pollEvents(std::string& winType);
	void update();

	void render();

};

