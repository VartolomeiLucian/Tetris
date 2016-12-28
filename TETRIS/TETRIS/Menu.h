#pragma once
#include "SFML/Graphics.hpp"
#define NR_ITEMS 4
using namespace sf;


class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void drawMenu(RenderWindow &window); 
	void MoveUp();
	void MoveDown();

private:
	int selectItem;
	Font font;
	Text menuText[NR_ITEMS];

};

