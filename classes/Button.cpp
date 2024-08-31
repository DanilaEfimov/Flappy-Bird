#include "Button.h"

void Button::initMolds()
{
	this->button.setFillColor(sf::Color::Blue);
	this->perCents.setFillColor(sf::Color::Red);

	this->button.setSize(sf::Vector2f(500.f, 50.f));
	this->perCents.setSize(sf::Vector2f(0.f, this->button.getSize().y));

	this->button.setOutlineThickness(5);

	this->button.setPosition(sf::Vector2f(300.f, 300.f));
	this->perCents.setPosition(this->button.getPosition());
}

void Button::initText()
{
	if (!this->font.loadFromFile("Fonts/Deledda Open Thin.ttf"))
	{
		std::cout << "ERROR::BUTTON::INITTEXT::failed to load font! " << "\n";
		exit(EXIT_FAILURE);
	}

	this->name = "HARD";
	this->text.setString(this->name);
	this->text.setCharacterSize(this->button.getSize().y - 10.f);
	this->text.setFillColor(sf::Color::Green);
	this->text.setPosition(this->button.getPosition() + sf::Vector2f(200.f, 5.f));
	this->text.setFont(this->font);
}

Button::Button()
{
	this->initMolds();
	this->initText();
}

Button::~Button()
{
}

const sf::Vector2f Button::getButtonSize() const
{
	return this->button.getSize();
}

const sf::Vector2f Button::getButtonPos() const
{
	return this->button.getPosition();
}

void Button::updateButton(float clickX)
{
	this->perCents.setSize(sf::Vector2f(clickX, this->perCents.getSize().y));
}

void Button::changeButtonName(std::string newName)
{
	this->name = newName;
	this->text.setString(newName);
}

void Button::changeButtonPos(sf::Vector2f newPos)
{
	this->button.setPosition(newPos);
	this->perCents.setPosition(newPos);
	this->text.setPosition(newPos + sf::Vector2f(200.f, 5.f));
}

void Button::renderButton(sf::RenderWindow* pWin)
{
	pWin->draw(this->button);
	pWin->draw(this->perCents);
	pWin->draw(this->text);
}
