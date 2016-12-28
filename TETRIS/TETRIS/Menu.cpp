#include "Menu.h"
using namespace sf;



Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("arial.ttf"))
	{

	}


	menuText[0].setFont(font);
	menuText[0].setFillColor(Color::White);
	menuText[0].setPosition(Vector2f(width / 2, height /(NR_ITEMS+2) * 1));
	menuText[0].setString("Play");


	menuText[1].setFont(font);
	menuText[1].setFillColor(Color::Black);
	menuText[1].setPosition(Vector2f(width / 2, height / (NR_ITEMS + 2) * 2));
	menuText[1].setString("Options");

	menuText[2].setFont(font);
	menuText[2].setFillColor(Color::Black);
	menuText[2].setPosition(Vector2f(width / 2, height / (NR_ITEMS + 2) * 3));
	menuText[2].setString("High-score");


	menuText[3].setFont(font);
	menuText[3].setFillColor(Color::Black);
	menuText[3].setPosition(Vector2f(width / 2, height / (NR_ITEMS + 2) * 4));
	menuText[3].setString("Exit");


	selectItem = 0; // Item-ul selectat
}


Menu::~Menu()
{
}

void Menu::drawMenu(sf::RenderWindow &window)
{
	int i = 0;
	for (i = 0; i < NR_ITEMS; i++)
		window.draw(menuText[i]);

}


void Menu::MoveUp()
{
	if (selectItem - 1 >= 0)
	{
		menuText[selectItem].setFillColor(Color::Black);
		selectItem--;
		menuText[selectItem].setFillColor(Color::White);
	}
}

void Menu::MoveDown()
{
	if (selectItem +1 < NR_ITEMS)
	{
		menuText[selectItem].setFillColor(Color::Black);
		selectItem++;
		menuText[selectItem].setFillColor(Color::White);
	}
}
