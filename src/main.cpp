#include"Window.h"
#include"Bird.h"
#include"Tube.h"
#include"Text.h"

#include<fstream>
#include<string>

using namespace std;

Window window;
Bird player;
Text score;

void writeScore(int score) { // костыльно, но я уже устал
	std::string scorrre = std::to_string(score);
	std::string str;
	
	ifstream fff;
	fff.open("scores.txt");
	std::getline(fff, str);
	int last = std::stoi(str);
	int now = std::stoi(scorrre);
	if (last < now)
	{
		ofstream file;
		file.open("scores.txt", ofstream::trunc);
		file << score << "\n" << "it's your record! ";
		file.close();
	}
}

int main() {
	// здесь будет меню
	// потом сделаем окно настроек, которое будет доступно из окна меню

	window.settingsLoop();
	// игровой цикл (поместим в отдельную функцию

	// if we change winType -> we change pWin and render it !!!
	sf::RenderWindow* pWin = window.getWindow();

	Tube tubes(window.getHard(), window.getBonus());

	while (window.running() && !player.getEndGame())
	{
		// Updating
		player.update(pWin->getSize().y - 10.f, window.getWinType(), tubes.tubes);
		tubes.updateTubes();
		score.updateText(player, tubes);
		window.update();

		// Rendering
		player.renderBird(pWin);
		tubes.renderTubes(pWin);
		score.renderText(pWin);
		window.render();
	}
	
	writeScore(score.getScore());

	return 0;
}
