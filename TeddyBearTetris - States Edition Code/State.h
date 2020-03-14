#pragma once
#define WIDTH 800
#define HEIGHT 600
#include "SFML/Graphics.hpp"
#include "SFML/Graphics.hpp"

class State {
protected:
	bool inState = 0;		// da li se nalazi u stanju ili ne, inicijalno nije u stanju
public:
	State() { }
	virtual ~State(){}
	bool isInState() { return inState; }  // da li je u stanju ili ne
	virtual void playMusic() = 0; // handleuje pozadinsku muziku, tj. pusta
	virtual int HandleEvents(sf::RenderWindow& gameWindow) = 0; // funkcija koja obradjuje moguce dogadjaje u stanju
	virtual void EnterState() = 0;  // fja za ulazenje u stanje
	virtual void ExitState() = 0;  // fja za izlazenje iz stanja
	virtual void DrawStuff(sf::RenderWindow& gameWindow) = 0; // sluzi za iscrtavanje cega god je potrebno
};
