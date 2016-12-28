#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>
using namespace sf;
using namespace std;


 
int main()
{

	RenderWindow window(VideoMode(750,900), "TETRIS");
	Menu menu(window.getSize().x, window.getSize().y);

	Texture tbackground;
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
			window.draw(background);
			menu.drawMenu(window); 
			//window.draw(background);
			window.display();

		}
	}


}



