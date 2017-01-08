#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <iostream>
#include "Menu.h"
#include "Shapes.h"
#include "ShapesFunction.h"


using namespace sf;
using namespace std;


/*
void fillShapesMatrix(bool matrix[4][4], int shape, int rotatie)
{
int i, j;
for (int i = 0; i < 4; i++)
for (int j = 0; j < 4; j++)
matrix[i][j] = shapesM[shape][rotatie][i][j];
}
void generateShapes(bool matrix[4][4], int &color, int &rotatie, int &shape)
{
color = rand() % 6;
rotatie = rand() % 4;
shape = rand() % 7;
fillShapesMatrix(matrix, shape, rotatie);
}
*/




int main()
{

	RenderWindow window(VideoMode(450, 700), "TETRIS");
	window.setFramerateLimit(30);

	Menu menu(window.getSize().x, window.getSize().y);

	ShapesFunction shapesFunction;
	bool gameOver = 0;
	int shapeDown = 0;
	int opMenu = -1;

	Texture tbackground;
	Texture tbackgroundBoardGame;

	tbackground.loadFromFile("back2.jpg");
	tbackgroundBoardGame.loadFromFile("Backboardgamescore.png");


	Sprite background(tbackground);
	Sprite backgroundBoarGame(tbackgroundBoardGame);
	


	while (window.isOpen())
	{

		Event windowEvent;

		while (window.pollEvent(windowEvent))
		{


			if (Event::KeyPressed == windowEvent.type)
			{

				//---Pentru meniu---

				if (windowEvent.key.code == Keyboard::Up)
					menu.MoveUp();

				if (windowEvent.key.code == Keyboard::Down)
					menu.MoveDown();

				if (windowEvent.key.code == Keyboard::Return)
				{
					if (menu.Item() == 0)
						opMenu = 1;
					if (menu.Item() == 1)
						opMenu = 2;
					if (menu.Item() == 2)
						window.close();
				}

				if (windowEvent.key.code == Keyboard::BackSpace)
					opMenu = 4;




				//--Pentru piese---


				if (windowEvent.key.code == Keyboard::RControl)
				{
					ShapesFunction shp = shapesFunction;
					shapesFunction.rotateShape();

				}




			}

			if (windowEvent.type == Event::Closed)
				window.close();


		}



		if (opMenu == -1)
		{
			window.draw(background);
			menu.drawMenu(window);
		}



		if (opMenu == 1)
		{

			window.draw(backgroundBoarGame);
			shapesFunction.drawActualShape(window);

			if (shapeDown <= 30)
				shapeDown++;
			else
				shapeDown = 1;
		}



		if (opMenu == 2)
			window.clear(Color::Black);



		if (opMenu == 3)
			window.close();

		if (opMenu == 4)
		{
			window.draw(background);
			menu.drawMenu(window);
		}

		/*generateShapes(matrix, color, rotatie, shape);
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		if (matrix[i][j] == 1)
		drawShapes(window, (j + shapePos.x)*BOARD_GAME_SIZE, (i + shapePos.y)*BOARD_GAME_SIZE, shapeColors[color]);*/




		window.display();
	}

	return 0;
}




