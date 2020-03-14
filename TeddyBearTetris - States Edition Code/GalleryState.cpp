#include "GalleryState.h"
#include <iostream>


GalleryState::GalleryState(){
	bgMusic.openFromFile("bg-sound/gallerymusic.wav");  // bg music
	if (bgMusic.openFromFile("bg-sound/gallerymusic.wav"))
		std::cout << "psycho loaded successfully" << std::endl;
	bgMusic.setLoop(true);
	bgMusic.setVolume(100);

	if (t.loadFromFile("images/cityscapeBG.jpg")) {  // bg image
		background.setTexture(t);
	}
	else std::cout << "File not good..." << std::endl;
	if (withImage.loadFromFile("images/withImageBG1.jpg")) {
		imageBG.setTexture(withImage);
	}
	else std::cout << "FIle not good..." << std::endl;

	gallery.SetMenu(800, 600, 36, 21, "gallItems.txt"); // font je 36 za stavke u galeriji, i ima 21 stavka
}

GalleryState::~GalleryState() { }

void GalleryState::playMusic() {
	bgMusic.play();
}

int GalleryState::HandleEvents(sf::RenderWindow& gameWindow) {
	sf::Event event;
	int indicator = 0; //  4 for go to main menu

	while (gameWindow.pollEvent(event))
	{
		
		switch (event.type)
		{
		case sf::Event::KeyReleased:  // moguci tasteri: up, down, enter (return in sfml)
			int item = gallery.getPressedItem();
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				gallery.moveUp();
				break;

			case sf::Keyboard::Down:
				gallery.moveDown();
				break;

			case sf::Keyboard::Return:  // kad je pritisnut enter, tj izabrana stavka iz menija
				if (!gallery.isImageOpened()) { // ako nijedna slika nije otvoena, otvara sliku, 
					gallery.OpenImage(item);	// ako jeste otvorena ne radi nista
				}
				break;
			case sf::Keyboard::Escape:
				
				if (gallery.isImageOpened()) {	// ako je neka slika otvorena, vraca se na izbor slika u galeriji
					gallery.CloseImage();		
				}
				else {							// ako nije otvorena nijedna slika, tj nalazi se u galeriji,
					ExitState();				// vraca se u main menu
					indicator = 4;				// ovaj indikator sluzi da se zna da treba da se vrati u mm u mainu
				}
				break;
			}
			break;
		}
	}

	gameWindow.clear(); // brise sve sto se naslo na windowu
	DrawStuff(gameWindow); // crta sta treba (prakticno ove dve fje zaredom sluze kao refresh screen)
	return indicator;
}

void GalleryState::EnterState() {
	bgMusic.play();
	inState = true;
}

void GalleryState::ExitState() {
	inState = false;
	bgMusic.stop();
}

void GalleryState::DrawStuff(sf::RenderWindow& gameWindow) {
	
	if (gallery.isImageOpened()) {	// ako je slika otvorena treba da je iscrta
		gameWindow.draw(imageBG);
		gallery.displayImage(gameWindow);
	}
	else {							// ako nije otvorena nijedna slika crta gallery menu
		gameWindow.draw(background);
		gallery.draw(gameWindow);
	}
	gameWindow.display(); // prikazuje sta treba
}