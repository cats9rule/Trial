#pragma once
#include <SFML/Audio.hpp>
#include "State.h"
#include "Gallery.h"

class GalleryState : public State {
private:
	Gallery gallery;
	sf::Texture t; // za sliku koja sluzi kao pozadina (ista ko za mm)
	sf::Music bgMusic;
	sf::Sprite background; // pozadina
	sf::Texture withImage; // ucitava pozadinu koja je na ekranu kad se otvori slika
	sf::Sprite imageBG; // pozxadina dok je otvorena slika
public:
	GalleryState();
	~GalleryState();

	void playMusic();
	int HandleEvents(sf::RenderWindow& gameWindow);
	void EnterState();
	void ExitState();

	void DrawStuff(sf::RenderWindow& gameWindow);

};