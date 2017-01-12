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
	bool GameOver = 0;
	int shapeDown = 0;
	int opMenu = -1;
	int colorShape = 0;
	int color = 0;
	int colorShapeBoardGame = 0;
	int ok = 0;
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

	//Score:

	int s = 0;
	int score = 0;
	int l = 0;
	int line = 0;
	int scoreGameOver = 0;


	Font arial;
	arial.loadFromFile("arial.ttf");

	ostringstream sScore;
	ostringstream sLine;


	sScore << score;
	sLine << line;


	Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 390, 125 }); //Pozitia pe boardgame
	lblScore.setFont(arial);
	lblScore.setString(sScore.str());

	Text lblLine;
	lblLine.setCharacterSize(30);
	lblLine.setPosition({ 390,265 });
	lblLine.setFont(arial);
	lblLine.setString(sLine.str());




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
				{

					s = 0;
					l = 0;
					score = 0;
					boardGame.resetGame();
					opMenu = -1;
					GameOver = 0;


					//Resetare score pe Board Game:

					sScore.str("");
					sScore << score;
					lblScore.setString(sScore.str());

					line = l;
					sLine.str("");
					sLine << line;
					lblLine.setString(sLine.str());




				}

				if (windowEvent.key.code == Keyboard::R)
				{
					s = 0;
					l = 0;
					score = 0;
					opMenu = 1;
					boardGame.resetGame();
					GameOver = 0;


					//Resetare score pe Board Game:

					sScore.str("");
					sScore << score;
					lblScore.setString(sScore.str());

					line = l;
					sLine.str("");
					sLine << line;
					lblLine.setString(sLine.str());
				}


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

			GameOver == 0;
			if (shapeDown % speedShapeDown == 0)
				shapesFunction.moveShape(0, 1);

			if (boardGame.Collision(shapesFunction))
			{
				boardGame.addShape(shapesFunction, color);
				boardGame.destroyFullLines(s, l, ok);

				

				score = s;
				if (score >= 0)
					speedShapeDown = 30;
				if (score >= 600)
					speedShapeDown = 10;
				if (score >= 800)
					speedShapeDown = 5;
				if (score >= 1200)
					speedShapeDown = 3;

				sScore.str("");
				sScore << score;
				lblScore.setString(sScore.str());

				line = l;
				sLine.str("");
				sLine << line;
				lblLine.setString(sLine.str());

				shapesFunction = ShapesFunction();
			}

			//High Score on Board Game ----------------------------

			int hg;
			ostringstream sHighScore;
			fstream f("HighScore.txt", ios::in);

			while (!f.eof())
			{
				f >> hg;

			}

			int highScore = hg;

			
			Text lblHighScore;
			lblHighScore.setCharacterSize(30);
			lblHighScore.setPosition({ 390,530 });
			lblHighScore.setFont(arial);
			lblHighScore.setString(sHighScore.str());


			sHighScore.str("");
			sHighScore << highScore;
			lblHighScore.setString(sHighScore.str());



			//Speed on Board Game -----------------------------

			ostringstream sSpeed;
			int speed = speedShapeDown;
			sSpeed << speed;

			Text lblSpeed;
			lblSpeed.setCharacterSize(30);
			lblSpeed.setPosition({ 390,408 });
			lblSpeed.setFont(arial);
			lblSpeed.setString(sLine.str());


			sSpeed.str("");
			sSpeed << speed;
			lblSpeed.setString(sSpeed.str());




			//Draw on Board Game

			window.draw(backgroundBoarGame);
			boardGame.drawOnBoardGame(window);
			shapesFunction.drawActualShape(window);
			window.draw(lblScore);
			window.draw(lblLine);
			window.draw(lblHighScore);
			window.draw(lblSpeed);


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
			{
				GameOver = 1;

				//Score dupa Game Over-------------------------


				ostringstream sScoreGameOver;
				int scoreGameOver = score;
				sScoreGameOver << scoreGameOver;

				Text lblScoreGameOver;
				lblScoreGameOver.setCharacterSize(30);
				lblScoreGameOver.setPosition({ 240,524 });
				lblScoreGameOver.setFont(arial);
				lblScoreGameOver.setString(sScoreGameOver.str());



				sScoreGameOver.str("");
				sScoreGameOver << scoreGameOver;
				lblScoreGameOver.setString(sScoreGameOver.str());

				//Update High Score------------

				fstream f("HighScore.txt", ios::app);

				if (score > hg)
				{
					f << endl;
					f << score;
				}

				window.draw(gameOver);
				window.draw(lblScoreGameOver);

			}
		}


		if (opMenu == 2)
			window.draw(instructions);

		if (opMenu == 3)
			window.close();



		window.display();
	}

	return 0;
}


