#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include "Menu.h"
#include "Gallery.h"
#include "MainState.h"
#include "GalleryState.h"

#define WIDTH 800
#define HEIGHT 600
int main()
{
	int ind = -1;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TeddyBear Tetris", sf::Style::Titlebar);
	MainState maain;
	GalleryState galleryy;
	maain.EnterState();
	while (window.isOpen()) {
		while (maain.isInState()) {
			ind = maain.HandleEvents(window);
			if (ind == 2) {
				maain.ExitState();
			}
			maain.DrawStuff(window);
			window.display();
		}
		if (!maain.isInState() && ind == 2) {

			galleryy.EnterState();
			while (galleryy.isInState()) {
				ind = galleryy.HandleEvents(window);
				if (ind == 4) {
					galleryy.ExitState();
					maain.EnterState();
				}
					
				galleryy.DrawStuff(window);
				window.display();
			}
		}
	}


	return 0;
}


///////////////// DALJI KOD JE ONO STARO, TU JE JUST IN CASE WE F UP ////////////////

	//sf::Music bgMusic;
	//bgMusic.openFromFile("bg-sound/dumbdumb.wav");
	//if (bgMusic.openFromFile("bg-sound/dumbdumb.wav"))
	//	std::cout << "dumb loaded successfully" << std::endl;
	//bgMusic.setLoop(true);
	//bgMusic.setVolume(100);
	//bgMusic.play();

	//sf::Texture t;
	//t.loadFromFile("images/cityscapeBG.jpg");

	//sf::Sprite background(t); // do ovoga je dodato za window

	//sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TeddyBear Tetris", sf::Style::Titlebar);

	//Menu menu;
	//menu.SetMenu(window.getSize().x, window.getSize().y, 60, 3, "mm.txt");

	//

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	
	//	while (window.pollEvent(event))
	//	{
	//		switch (event.type)
	//		{
	//		case sf::Event::KeyReleased:
	//			switch (event.key.code)
	//			{
	//			case sf::Keyboard::Up:
	//				menu.moveUp();
	//				break;

	//			case sf::Keyboard::Down:
	//				menu.moveDown();
	//				break;

	//			case sf::Keyboard::Return:
	//				switch (menu.getPressedItem()) // cisto za proveru
	//				{
	//				case 0:
	//					std::cout << "Play button has been pressed" << std::endl;
	//					break;
	//				case 1:
	//					std::cout << "Gallery button has been pressed" << std::endl;
	//					break;
	//				case 2:
	//					window.close();
	//					break;
	//				}

	//				break;
	//			}

	//			break;
	//		case sf::Event::Closed:
	//			window.close();

	//			break;

	//		}
	//	}

	//	window.clear();
	//	window.draw(background);
	//	menu.draw(window);
	//	

	//	window.display();
	//}
//Galerija:
//	window.close();
//	sf::RenderWindow gall(sf::VideoMode(WIDTH, HEIGHT), "TeddyBear Tetris", sf::Style::Titlebar);
//	Gallery gallery(6, WIDTH, HEIGHT, 18);
//	while (gall.isOpen()) {
//		gall.clear();
//		sf::Event event;
//
//		while (gall.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case sf::Event::KeyReleased:
//				switch (event.key.code)
//				{
//				case sf::Keyboard::Up:
//					menu.moveUp();
//					break;
//
//				case sf::Keyboard::Down:
//					menu.moveDown();
//					break;
//
//				case sf::Keyboard::Return:
//					int ind = menu.getPressedItem(); 
//					gallery.OpenImage(ind);
//					while (gallery.isImageOpened()) {
//						gallery.displayImage(gall);
//						if (event.key.code == sf::Keyboard::Escape) {
//							gallery.CloseImage();
//						}
//					}
//					
//				}
//
//				break;
//			case sf::Event::Closed:
//				gall.close();
//
//				break;
//
//			}
//		}
//
//
//
//		gall.clear();
//		gall.draw(background);
//		gallery.draw(window);
//
//
//		gall.display();
//		
//	}
