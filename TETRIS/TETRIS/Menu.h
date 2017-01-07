#pragma once
#include "SFML/Graphics.hpp"
#define NR_ITEMS 4
using namespace sf;


class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	int Item()
	{
		return selectItem;
	}
	void drawMenu(RenderWindow &window); 
	void MoveUp();
	void MoveDown();

private:
	int selectItem=0;
	Font font;
	Text menuText[NR_ITEMS];

};

