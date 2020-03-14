#pragma once

#include <SFML/Audio.hpp>
#include "State.h"
#include "Menu.h"

class MainState : public State {
private:
	//sf::RenderWindow gameWindow;
	sf::Texture t;
	sf::Music bgMusic;
	sf::Sprite background;
	Menu menu;

public:
	MainState();
	~MainState();

	void playMusic();
	int HandleEvents(sf::RenderWindow& gameWindow);
	void EnterState();
	void ExitState();

	void DrawStuff(sf::RenderWindow& gameWindow);
};