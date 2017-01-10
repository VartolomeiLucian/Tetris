#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Menu.h"
#include "Shapes.h"
#include "ShapesFunction.h"
#include "BoardGame.h"
#include <fstream>


using namespace sf;
using namespace std;


ofstream f("HighScore.txt");

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

	RenderWindow window(VideoMode(500, 730), "TETRIS");
	window.setFramerateLimit(30);

	Menu menu(window.getSize().x, window.getSize().y);
	BoardGame boardGame;
	ShapesFunction shapesFunction;
	int shapeDown = 0;
	int opMenu =-1;
	int colorShape = 0;
	int color = 0;
	int colorShapeBoardGame = 0;
	int ok = 1;


	// Background:

	Texture tbackground;
	Texture tbackgroundBoardGame;
	Texture tgameOver;
	Texture tinstructions;

	tbackground.loadFromFile("back2.jpg");
	tbackgroundBoardGame.loadFromFile("Backboardgamescore.png");
	tgameOver.loadFromFile("GameOver.png");
	tinstructions.loadFromFile("Instructions.png");

	Sprite background(tbackground);
	Sprite backgroundBoarGame(tbackgroundBoardGame);
	Sprite gameOver(tgameOver);
	Sprite instructions(tinstructions);

	


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

				
				cout << menu.Item()<<" "<<opMenu << endl;

				if (windowEvent.key.code == Keyboard::BackSpace)
					opMenu = 4;
				

				//--Pentru piese---


				if (windowEvent.key.code == Keyboard::RControl)
				{
					ShapesFunction shp = shapesFunction;
					shapesFunction.rotateShape();
					if (boardGame.Collision(shapesFunction) != 0)
						shapesFunction = shp;
				}


				if (windowEvent.key.code == Keyboard::Right)
				{
					ShapesFunction shp = shapesFunction;
					shapesFunction.moveShape(1, 0);
					if (boardGame.Collision(shapesFunction) != 0)
						shapesFunction = shp;
				}


				if (windowEvent.key.code == Keyboard::Left)
				{
					ShapesFunction shp = shapesFunction;
					shapesFunction.moveShape(-1, 0);
					if (boardGame.Collision(shapesFunction) != 0)
						shapesFunction = shp;
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

			if (shapeDown % 30 == 0)
				shapesFunction.moveShape(0, 1);

			if (boardGame.Collision(shapesFunction))
			{
				boardGame.addShape(shapesFunction, color);
				shapesFunction = ShapesFunction();
			}

			window.draw(backgroundBoarGame);
			boardGame.drawOnBoardGame(window);
			shapesFunction.drawActualShape(window);
			

			if (shapeDown <= 30)
				shapeDown++;
			else
				shapeDown = 1;

			if (Event::KeyPressed == windowEvent.type)
				if (windowEvent.key.code == Keyboard::RShift)
				{

					if (!boardGame.Collision(shapesFunction))
						shapesFunction.moveShape(0, 1);

				}

		}
		


		if (opMenu == 2)
			window.draw(instructions);

		if (opMenu == 3)
			//window.close();
			window.draw(instructions);


		if (opMenu == 4)
		{
			window.draw(background);
			menu.drawMenu(window);
		}
		

		window.display();
	}

	return 0;
}


