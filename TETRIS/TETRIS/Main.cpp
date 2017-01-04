#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Shapes.h"
using namespace sf;
using namespace std;


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





int main()
{

	bool matrix[4][4];
	int boardGame[16][10] = { 0 };
	int rotatie, shape, color;

	Vector2f shapePos, windowSize;



	RenderWindow window(VideoMode(450, 700), "TETRIS");
	windowSize.x = (float)window.getSize().x;
	windowSize.y = (float)window.getSize().y;
	
	shapePos.x = windowSize.x / BOARD_GAME_SIZE/ 3;
	shapePos.y = 0;


	Menu menu(window.getSize().x, window.getSize().y);

	Texture tbackground,tshape;
	tbackground.loadFromFile("back.jpg");

	Sprite background(tbackground);

	

	while (window.isOpen())
	{
		Event windowEvent;
		while (window.pollEvent(windowEvent))
		{

			switch (windowEvent.type)
			{
			case Event::KeyReleased:
				switch (windowEvent.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;
				}

				break;

			case Event::Closed:
				window.close();
				break;
			}

			window.clear();
			
			


			generateShapes(matrix, color, rotatie, shape);
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					if (matrix[i][j] == 1)
						drawShapes(window, (j + shapePos.x)*BOARD_GAME_SIZE, (i + shapePos.y)*BOARD_GAME_SIZE, shapeColors[color]);


		
			//window.draw(background);
			//menu.drawMenu(window);
			window.display();

		}
	}


}