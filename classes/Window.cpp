#include "Window.h"

void Window::initVariables()
{
	this->endGame = false;
	this->winType = "Settings";

	this->bonus.changeButtonName("bonus");
	this->bonus.changeButtonPos(sf::Vector2f(300.f, 600.f));

	this->epsilone = 1.f;
	this->delta = 1.f;
}

void Window::initWindows()
{
	this->videoMode.width = 1200;
	this->videoMode.height = 800;

	this->gameWin = new sf::RenderWindow(this->videoMode, "Flappy Bird",
		sf::Style::Titlebar | sf::Style::Close);
	this->settingWin = new sf::RenderWindow(this->videoMode, "Settings",
		sf::Style::Titlebar | sf::Style::Close);

	this->settingWin->setFramerateLimit(60);
	/*this->menuWin = new sf::RenderWindow(videoMode, "Menu",
		sf::Style::Titlebar | sf::Style::Close);*/

	// these will be initialize if winType will changed

	this->gameWin->setFramerateLimit(60);
	//this->menuWin->setFramerateLimit(60);
	//this->settingWin->setFramerateLimit(60);
}

// Constructor & Destructor
Window::Window()
{
	this->initVariables();
	this->initWindows();
}

Window::~Window()
{
	delete this->menuWin;

}

void Window::DESTRUCT()
{
	delete this->gameWin;
	delete this->settingWin;
}

// Accessors
const bool Window::running() const
{
	return this->gameWin->isOpen();
}

const std::string Window::getWinType() const
{
	return this->winType;
}

const sf::Vector2f Window::getWindowSize() const
{
	return static_cast<sf::Vector2f> (this->gameWin->getSize());
}

const float Window::getHard() const
{
	return this->epsilone * 100.f;
}

const float Window::getBonus() const
{
	return this->delta * 10.f;
}

sf::RenderWindow* Window::getWindow()
{
	if (this->winType == "Game")
		return this->gameWin;
	else if (this->winType == "Menu")
		return this->menuWin;
	else if (this->winType == "Settings")
		return this->settingWin;
	return nullptr;
}

void Window::settingsLoop()
{	

	
	while (this->settingWin->isOpen())
	{
		this->pollEvents(this->winType);

		this->settingWin->clear();

		this->hard.renderButton(this->settingWin);
		this->bonus.renderButton(this->settingWin);

		this->settingWin->display();
	}

	this->winType = "Game";
	delete this->settingWin;
}

void Window::pollEvents(std::string& winType)
{
		// Game
		if (winType == "Game")
		{
			while(this->gameWin->pollEvent(this->event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					this->gameWin->close();
					break;
				case sf::Event::KeyPressed:
					// * // * // *
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						this->gameWin->close();
						break;
					default:
						break;
					}
					// * // * // *
				default:
					break;
				}
			}
		}
		///////////

		else if (winType == "Settings")
		{
			// preinit
			sf::Vector2i mouse = sf::Mouse::getPosition() - 
				this->settingWin->getPosition() - sf::Vector2i(0, 30); // last is width of window Name
			sf::Vector2f hardButton = this->hard.getButtonSize();
			sf::Vector2f hardPos = this->hard.getButtonPos();

			sf::Vector2f bonusButton = this->bonus.getButtonSize();
			sf::Vector2f bonusPos = this->bonus.getButtonPos();

			float difXH = mouse.x - hardPos.x;
			float difYH = mouse.y - hardPos.y;

			float difXB = mouse.x - bonusPos.x;
			float difYB = mouse.y - bonusPos.y;

			while (this->settingWin->pollEvent(this->event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					this->settingWin->close();
					break;
				case sf::Event::KeyPressed:
					// * // * // *
					switch (event.key.code)
					{
					case sf::Keyboard::Escape:
						this->settingWin->close();
						break;
					default:
						break;
					}
					// * // * // *
				case sf::Event::MouseButtonPressed:
					if (difXH <= hardButton.x && difXH >= 0 &&
						difYH <= hardButton.y && difYH >= 0)
					{
						this->hard.perCents.setSize(sf::Vector2f(
							difXH, hard.perCents.getSize().y));
						this->epsilone = hard.perCents.getSize().x / hard.button.getSize().x;
					}
					if (difXB <= bonusButton.x && difXB >= 0 &&
						difYB <= bonusButton.y && difYB >= 0)
					{
						this->bonus.perCents.setSize(sf::Vector2f(
							difXB, bonus.perCents.getSize().y));
						this->delta = bonus.perCents.getSize().x / bonus.button.getSize().x;
					}
				default:
					break;
				}
			}
		}
}

void Window::update()
{
	this->pollEvents(this->winType);
}

void Window::render()
{
	if(this->winType == "Game")
	{
		//this->gameWin->clear({ 200,30,90 });

		this->gameWin->display();
	}
	else if (this->winType == "Menu")
	{
		this->menuWin->clear();

		this->menuWin->display();
	}
	else if (this->winType == "Settings")
	{
		this->settingWin->clear();

		this->settingWin->display();
	}
}
