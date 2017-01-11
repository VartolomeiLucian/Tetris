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



int main()
{

	RenderWindow window(VideoMode(500, 730), "TETRIS");
	window.setFramerateLimit(30);

	
	Menu menu(window.getSize().x, window.getSize().y);
	BoardGame boardGame;
	ShapesFunction shapesFunction;

	
	int shapeDown = 0;
	int opMenu = -1;
	int colorShape = 0;
	int color = 0;
	int colorShapeBoardGame = 0;
	int ok = 1;
	int speedShapeDown = 30;


	// Background:

	Texture tbackground;
	Texture tbackgroundBoardGame;
	Texture tgameOver;
	Texture tinstructions;

	tbackground.loadFromFile("BackMenu.png");
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

				//Pentru meniu---

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


		
				if (windowEvent.key.code == Keyboard::Escape)
					opMenu = -1;


			

				if (windowEvent.key.code == Keyboard::R) 
					opMenu = 1;
				


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

		//Optiuni Meniu----------------------

		if (opMenu == -1)
		{
			window.draw(background);
			menu.drawMenu(window);
		}


		if (opMenu == 1)
		{	
			
			
			if (shapeDown % speedShapeDown == 0)
				shapesFunction.moveShape(0, 1);

			if (boardGame.Collision(shapesFunction))
			{
				boardGame.addShape(shapesFunction, color);
				boardGame.destroyFullLines(s, l, ok);
				
				shapesFunction = ShapesFunction();
			}



			//Draw on Board Game

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


			if (boardGame.fullBoardGame() != 0)
				window.draw(gameOver);

			
		}




		if (opMenu == 2)
			window.draw(instructions);

		if (opMenu == 3)
			window.close();



		window.display();
	}

	return 0;
}


