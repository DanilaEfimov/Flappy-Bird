#include "Bird.h"
#include<windows.h>

void Bird::initVariables()
{
	// Game logic
	this->maxJumpTimer = 13; // in frames
	this->jumpTimer = this->maxJumpTimer;
	this->held = false;
	this->endGame = false;

	// Samples

	if (!this->BakAI.openFromFile("Sounds/A.mp3"))
	{
		std::cout << "ERROR::BIRD::INITSOUNDS::failed to load sound! " << "\n";
		exit(EXIT_FAILURE); // return 1;
	}

	if (!this->BakDeer.openFromFile("Sounds/Deer.mp3"))
	{
		std::cout << "ERROR::BIRD::INITSOUNDS::failed to load sound! " << "\n";
		exit(EXIT_FAILURE); // return 1;
	}

	if (!this->jump.openFromFile("Sounds/jump.mp3"))
	{
		std::cout << "ERROR::BIRD::INITSOUNDS::failed to load sound! " << "\n";
		exit(EXIT_FAILURE); // return 1;
	}

	//_________________________

	this->pos = sf::Vector2f(400.f, 350.f);
	this->speedDown = sf::Vector2f(0.f, 8.f);
	this->speedUp = this->speedDown + sf::Vector2f(0.f, 7.f);
	// order of initialize is very important
	// because some variable depends of their

	if (!this->textureBack.loadFromFile("Textures/backspace.png"))
	{
		std::cout << "ERROR::BIRD::INITVARIABLES::failed to load the texture! " << "\n";
		exit(EXIT_FAILURE); // #def 1
	}
	this->backGround.setTexture(this->textureBack);

	if (!this->textureBird.loadFromFile("Textures/lesha.jpeg"))
	{
		std::cout << "ERROR::BIRD::INITVARIABLES::failed to load the texture! " << "\n";
		exit(EXIT_FAILURE);
	}
	// make temp const texture for setting
	const sf::Texture* bbb = &textureBird;
	this->body.setTexture(bbb);
}

void Bird::initBird()
{
	this->body.setFillColor(sf::Color::White);
	this->body.setRadius(30.f);
	this->body.setPosition(this->pos);
}

// Constructor & Destructor
Bird::Bird()
{
	this->initVariables();
	this->initBird();
}

Bird::~Bird()
{
}

// Accessors
const unsigned Bird::getGameTime() const
{
	return this->maxJumpTimer;
}

const bool Bird::getEndGame() const
{
	return this->endGame;
}

const sf::Vector2f Bird::getSpeedUp() const
{
	return this->speedUp;
}

const sf::Vector2f Bird::getSpeedDown() const
{
	return this->speedDown;
}

/////////////////////////

// Physics
void Bird::setPhysic(float winY, std::string winType)
{
	// Check of edge and Tubes
	if (this->pos.y <= 0)
	{
		this->speedUp = { 0.f, 0.f };
	}
	///////////////
	if (this->pos.y + 2 * this->body.getRadius() >= winY)
	{
		this->endGame = true;
		this->BakAI.play();
		Sleep(this->BakAI.getDuration().asMilliseconds());

		this->speedUp = { 0.f, 0.f };
		this->speedDown = { 0.f, 0.f };
		// after made little jump 'bump'
	}
	else
	{
		// Jump mechanic
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
			(sf::Mouse::isButtonPressed(sf::Mouse::Left))) &&
			winType == "Game")
		{
			if (this->held == false)
			{
				this->jump.play();
				this->jumpTimer = 0;
				this->held = true;
			}
		}
		else
		{
			this->held = false;
		}
	///////////////
		if (this->jumpTimer <= this->maxJumpTimer)
		{
			this->pos -= this->speedUp;
			jumpTimer++;
		}
		this->pos += this->speedDown;

		this->body.setPosition(pos);
	}
}

void Bird::update(float winY, std::string winType, std::vector<sf::RectangleShape> tubes)
{
	this->setPhysic(winY, winType);
	this->detectCoalision(tubes);
}

void Bird::detectCoalision(std::vector<sf::RectangleShape> tubes)
{
	if (tubes.size() > 4)
	{
		for (int i = 0; i < 8; i++)
		{
			if (tubes.at(i).getGlobalBounds().intersects(this->body.getGlobalBounds()))
			{
				this->endGame = true;
			}
		}
	}

	if (this->endGame)
	{
		this->BakAI.play();
		Sleep(this->BakAI.getDuration().asMilliseconds());
	}
}

// Rendering 
void Bird::renderBird(sf::RenderWindow* window)
{
	(*window).draw(this->backGround);
	(*window).draw(this->body);
}
