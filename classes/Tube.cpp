#include "Tube.h"
#include<cmath>

// Initialize
void Tube::initVariables(float eps, float del)
{
	srand(time(0));

	this->epsilon = eps; 
	this->delta = del; 

	// YYYYYYYYYYYYEEEEEEEEEEEAAAAAAAAAAAAAAAA

	this->cloneSpeedUp = this->birdCopy.getSpeedUp();
	this->cloneSpeedDown = this->birdCopy.getSpeedDown();
	this->cloneWinSize = this->gameWinCopy.getWindowSize();
	this->cloneTimer = this->birdCopy.getGameTime();

	///////////////////////////////////////////////
	float winX = this->cloneWinSize.x;
	float winY = this->cloneWinSize.y;
	unsigned Timer = this->cloneTimer;
	sf::Vector2f speedUp = this->cloneSpeedUp;
	sf::Vector2f speedDown = this->cloneSpeedDown;
	sf::Vector2f different = sf::Vector2f(0.f, abs( speedDown.y - speedUp.y));

	// How many tubes can be on the screen
	this->distance = 330.f + this->delta; // in pixels
	this->distanceTimer = 0;
	this->maxTubesCount = static_cast<unsigned>(4 * winX / this->distance); // не нужно

	// 4 because two molds up & two down
	this->holeWidth = this->distance / 2.f + 2.f * this->epsilon;
	this->speed = sf::Vector2f(-(3.f + this->epsilon / 10.f), 0.f);

	if (!this->textureBigPart.loadFromFile("Textures/tube.png"))
	{
		std::cout << "ERROR::TUBE::INITTUBES::failed to load the texture! " << "\n";
		exit(EXIT_FAILURE);
	}
	this->tTube = &this->textureBigPart;

	if (!this->textureHole.loadFromFile("Textures/tube.png"))
	{
		std::cout << "ERROR::TUBE::INITTUBES::failed to load the texture! " << "\n";
		exit(EXIT_FAILURE);
	}

	this->U = float(Timer) * different.y + 3.f * this->delta;

	this->bigTube.setSize(sf::Vector2f(this->holeWidth - 2.f * this->epsilon, winY));
	this->hole.setSize(sf::Vector2f(this->holeWidth, 0.5f * winY / this->delta));

}

const sf::Vector2f Tube::getSpeed() const
{
	return this->speed;
}

void Tube::setHard(float h)
{
	this->epsilon = 100.f * h;
}

void Tube::setBonus(float b)
{
	this->delta = 50.f * b;
}

void Tube::spawnTubes()
{
	unsigned Timer = this->cloneTimer;
	sf::Vector2f speedUp = this->cloneSpeedUp;
	float winX = this->cloneWinSize.x;
	float winY = this->cloneWinSize.y;
	float holeW = this->holeWidth;

	// they use same texture yet
	this->bigTube.setTexture(tTube);
	this->hole.setTexture(tTube);

	// Outlines
	this->bigTube.setOutlineThickness(this->delta + 3.f);
	this->bigTube.setOutlineColor(sf::Color::Black);

	this->hole.setOutlineThickness(this->delta + 3.f);
	this->hole.setOutlineColor(sf::Color::Black);

	// Mold
	// These Vectors2f is VERY important
	// Here we contain base calculations of game
	// Calculate positions and size of tubes depends
	// of window and game parameters
	// Timer * speedUp.y = 1 jump
	
	// Randomize
	int levels = static_cast<int>(this->cloneWinSize.y / this->U / 2.f);
	float shift = static_cast<float>(rand() % levels * this-> U * pow(-1, rand() % levels));

	this->bigTube.setPosition(sf::Vector2f(winX + this->epsilon, winY / 2.f + this->U + 3.f * this->delta + shift));
	this->hole.setPosition(sf::Vector2f(this->bigTube.getPosition() - sf::Vector2f(this->epsilon, 0.f)));

	// Order is important, because by other way bigTube will be upper hole!!!
	this->tubes.push_back(this->bigTube); // down pair
	this->tubes.push_back(this->hole);

	// For up pair we set new coordinates
	this->bigTube.setPosition(sf::Vector2f(winX + this->epsilon, -winY / 2.f - this->U - 3.f * this->delta + shift));
	this->hole.setPosition(sf::Vector2f(this->bigTube.getPosition() - sf::Vector2f(this->epsilon, -this->bigTube.getSize().y + this->hole.getSize().y)));

	this->tubes.push_back(this->bigTube); // up pair
	this->tubes.push_back(this->hole);
}

void Tube::updateTubes()
{
	if (this->tubes.size() + 4 <= this->maxTubesCount)
	{
		float beetwenTubes = this->tubes.at(this->tubes.size() - 1).getPosition().x +
			this->distance + this->tubes.at(this->tubes.size() - 1).getSize().x;
		if (beetwenTubes >= this->cloneWinSize.x && 
			beetwenTubes + this->speed.x <= this->cloneWinSize.x)
		{
  			this->spawnTubes();
		}
	}

	float size, pos;
	for (int i = 0; i < this->tubes.size(); i++)
	{
		this->tubes[i].setPosition(this->tubes[i].getPosition() + this->speed);
		size = this->tubes.at(i).getSize().x;
		pos = this->tubes.at(i).getPosition().x;
		if ((pos + size) / 2.f < 0)
		{
			this->tubes.erase(this->tubes.begin() + i);
		}
	}
}

void Tube::renderTubes(sf::RenderWindow* window)
{
	for (auto& t : this->tubes)
	{
		window->draw(t);
	}
}

// Constructors and destructors
Tube::Tube(float eps, float del)
{
	this->initVariables(eps, del);
	this->spawnTubes();
	this->gameWinCopy.getWindow()->close();
	this->gameWinCopy.DESTRUCT();
}

Tube::~Tube()
{
}
