#pragma once
#include"Window.h"
#include"Bird.h"
#include"Tube.h"

class Text
{
private:
	int score;
	std::string str;
	sf::Font font;
	sf::Text text;

	sf::Music point;

	// clone for copy window size
	Window cloneWin;

	void initVariables();
public:
	Text();
	virtual ~Text();

	const int getScore() const;

	void updateText(Bird& player, Tube& tubes);

	void renderText(sf::RenderWindow* win);
};

