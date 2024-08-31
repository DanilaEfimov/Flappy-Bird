#include "Text.h"

void Text::initVariables()
{
	this->score = 0;
	this->str = std::to_string(this->score);
	
	if (!this->font.loadFromFile("Fonts/SmallestPixel7.ttf"))
	{
		std::cout << "ERROR::TEXT::INITVARIABLES::failed to load font! " << "\n";
		exit(EXIT_FAILURE);
	}

	if (!this->point.openFromFile("Sounds/coin.mp3"))
	{
		std::cout << "ERROR::TEXT::INITVARIABLES::failed to load sound! " << "\n";
		exit(EXIT_FAILURE);
	}

	this->text.setString(this->str);
	this->text.setFont(this->font);
	this->text.setCharacterSize(110);
	this->text.setOutlineThickness(2);
	this->text.setFillColor(sf::Color::Red);

	sf::Vector2f size = this->cloneWin.Window::getWindowSize();
	this->text.setPosition(size.x / 2.f, size.y / 8.f);
}



Text::Text()
{
	this->initVariables();
	this->cloneWin.DESTRUCT();
}

Text::~Text()
{

}

const int Text::getScore() const
{
	return this->score;
}

void Text::updateText(Bird& player, Tube& tubes)
{
	int size = tubes.tubes.size() - 1;
	float playerPosX = player.body.getPosition().x;
	float tubeSpeedX = tubes.getSpeed().x;
	bool gotten = false;
	for (int i = 0; i < size && !gotten; i += 4)
	{
		sf::RectangleShape temp = tubes.tubes.at(i);
		if ((temp.getPosition().x + temp.getSize().x) >= playerPosX &&
			(temp.getPosition().x + temp.getSize().x) + tubeSpeedX <= playerPosX)
		{
			gotten = true;
			this->point.play();
			this->score++;
			this->str = std::to_string(this->score);
			this->text.setString(this->str);
		}
	}
}

void Text::renderText(sf::RenderWindow* win)
{
	win->draw(this->text);
}
