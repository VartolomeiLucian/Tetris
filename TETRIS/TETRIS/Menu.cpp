#include <SFML/Graphics.hpp>
#include "Menu.h"
using namespace sf;



Menu::Menu(float width, float height)
{

	if (!font.loadFromFile("peppermint.ttf"))
	{

	}


	menuText[0].setFont(font);
	menuText[0].setFillColor(Color::Yellow);
	menuText[0].setCharacterSize(70);
	menuText[0].setPosition(Vector2f(width / 4, height /(NR_ITEMS+2)*2));
	menuText[0].setString("Play");


	menuText[1].setFont(font);
	menuText[1].setFillColor(Color::White);
	menuText[1].setCharacterSize(60);
	menuText[1].setPosition(Vector2f(width / 4, height / (NR_ITEMS+3)*3));
	menuText[1].setString("Instructions");

	menuText[2].setFont(font);
	menuText[2].setFillColor(Color::White);
	menuText[2].setCharacterSize(70);
	menuText[2].setPosition(Vector2f(width / 4, height / (NR_ITEMS + 4) *4 ));
	menuText[2].setString("Exit");

	selectItem = -1;
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
		menuText[selectItem].setFillColor(Color::White);
		selectItem--;
		menuText[selectItem].setFillColor(Color::Yellow);
	}


}

void Menu::MoveDown()
{
	if (selectItem +1 < NR_ITEMS)
	{
		menuText[selectItem].setFillColor(Color::White);
		selectItem++;
		menuText[selectItem].setFillColor(Color::Yellow);
	}

	

}
