#pragma once
#include "Shapes.h"
#include <iostream>
#include "SFML\Graphics.hpp"

using namespace std;
using namespace sf;

class ShapesFunction
{
private:
	int shapeIdx;
	int matrixShape[4][4]; //matricea in care am forma
	int Xposition;
	int Yposition;
	int color;

	void fillShapesMatrix()
	{
		for (int i = 0; i < 4; i++)
			for (int m = 0; m < 4; m++)
				matrixShape[i][m] = allShapes[shapeIdx][i][m];
	}

public:
	ShapesFunction()
	{
		Xposition = 2;
		Yposition = -4;
		generateShapes();
	}

	void generateShapes()
	{
		int shapeG = rand() % 7;
		shapeIdx = (ShapeIndx)shapeG;
		color = rand() % 6;
		fillShapesMatrix();
	}


	void moveShape(int x, int y)
	{
		if (ValidShapeRotate(x, y) != 0)
		{
			Xposition = Xposition + x;
			Yposition = Yposition + y;
		}
	}


	void rotateShape()
	{
		int auxIdx = shapeIdx;

		shapeIdx = ((shapeIdx + 1) % 4 == 0 ? shapeIdx - 3 : shapeIdx + 1);

		fillShapesMatrix();

		if (!ValidShapeRotate())
		{
			shapeIdx = auxIdx;
			fillShapesMatrix();
		}
	}

	bool ValidShapeRotate(int axaX = 0, int axaY = 0)
	{

		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if ((matrixShape[y][x] != 0 && (Xposition + x + axaX >= BOARD_GAME_WIDTH || Xposition + axaX < 0)) || (matrixShape[y][x] && (Yposition + y + axaY > BOARD_GAME_HEIGHT)))
					return 0;


		return true;
	}

	void drawActualShape(sf::RenderWindow & window)
	{

		int x, y;

		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if (matrixShape[y][x])
					drawShapes(window, (x + Xposition) * BOARD_GAME_SIZE, (y + Yposition) * BOARD_GAME_SIZE, shapeColors[color]);
				
	}



	int returnPositionX()
	{
		return Xposition;
	}

	int(returnPositionY())
	{
		return Yposition;
	}


	int returnShape(int x, int y)
	{
		return matrixShape[y][x];
	}
	
};




