#pragma once
#include <SFML\Graphics.hpp>
#include "ShapesFunction.h"
#include "Shapes.h"
#include <iostream>

using namespace std;
using namespace sf;


class BoardGame
{
private:
	int boardGameMatrix[BOARD_GAME_HEIGHT][BOARD_GAME_WIDTH];
	int matrix[4][4];
	int color;
	int score;



public:

	void addShape(ShapesFunction shapefunction, int &color)
	{

		int x;
		int y;

		color++;
		if (color == 6)
			color = 1;

		for (y = 0; y < 4; y++)
			for (x = 0; x < 4; x++)
				if (shapefunction.returnShape(x, y))
					boardGameMatrix[shapefunction.returnPositionY() + y][shapefunction.returnPositionX() + x] = 1;
	}



	BoardGame()
	{
		resetGame();
	}


	void resetGame()
	{
		score = 0;
		int y;
		int x;

		for (y = 0; y < BOARD_GAME_HEIGHT; y++)
			for (x = 0; x < BOARD_GAME_WIDTH; x++)
				boardGameMatrix[y][x] = 0;
	}




	void shapeDown(int down)
	{

		int x;
		int y;

		for (y = down; y > -1; y--)
			for (x = 0; x < BOARD_GAME_WIDTH; x++)
				if (y < BOARD_GAME_HEIGHT - 1 && boardGameMatrix[y + 1][x] == 0 && boardGameMatrix[y][x])
				{
					boardGameMatrix[y][x] = 0;
					boardGameMatrix[y + 1][x] = 1;
				}
	}



	bool Collision(ShapesFunction shapefunction)
	{

		int x;
		int y;

		for (y = 0; y < 4; y++)
			for (x = 0; x < 4; x++)
				if ((shapefunction.returnPositionY() + y >= 0) && ((boardGameMatrix[shapefunction.returnPositionY() + y + 1][shapefunction.returnPositionX() + x] && shapefunction.returnShape(x, y)) ||
					(shapefunction.returnShape(x, y) && shapefunction.returnPositionY() + y >= BOARD_GAME_HEIGHT - 1)))
					return 1;

		return 0;
	}



	bool fullBoardGame()
	{
		int x;
	
		for (x = 0; x < BOARD_GAME_WIDTH; x++)
			if (boardGameMatrix[0][x] != 0)
				return 1;
			

		return 0;
	}



	void destroyFullLines(int &score, int &line, int &ok2)
	{
		int x;
		int y;
		ok2 = 0; //pentru sound


		for (y = 0; y < BOARD_GAME_HEIGHT; y++)
		{

			bool ok = 1;

			for (x = 0; x < BOARD_GAME_WIDTH; x++)
				if (!boardGameMatrix[y][x])
				{
					ok = 0;
					break;
				}


			if (ok)
			{
				line++;
				score = score + 100;
				ok2 = 1;

				int x;
				for (x = 0; x < BOARD_GAME_WIDTH; x++)
					boardGameMatrix[y][x] = 0;

				shapeDown(y);
				y = 0;
			}
		}
	}

	int returnScore()
	{
		cout << score;
		return score;
	}



	void drawOnBoardGame(RenderWindow & window)
	{
		int i;
		int j;

		for (i = 0; i < BOARD_GAME_HEIGHT; i++)
			for (j = 0; j < BOARD_GAME_WIDTH; j++)
				if (boardGameMatrix[i][j])
					drawShapes(window, j* BOARD_GAME_SIZE, i * BOARD_GAME_SIZE, Color::Cyan);


	}


};




