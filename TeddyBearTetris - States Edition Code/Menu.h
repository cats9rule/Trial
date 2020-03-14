#pragma once

#include <SFML/Graphics.hpp>

#define MAX_NUM_OF_ITEMS 21

class Menu // klasa koja sluzi za ispis i funkcionalnu upotrebu stavki na meniju
{
protected:
	float width;
	float height;

	int selectedItemIndex; // highlighted stavka na emniju
	int noOfItems; // broj stavki na meniju
	sf::Font font; // font za stavke
	int fontSize; // velicina slova na stavkama
	sf::Font titleFont; // font za naslov menija
	sf::Text Title;  // naslov menija
	sf::Text menu[MAX_NUM_OF_ITEMS]; // niz koji predstavlja stavke

public:
	Menu();
	~Menu();

	virtual void SetMenu(float width, float height, int font_size, int no_of_items, std::string fName); // fja za postavljanje izgleda menija
	void draw(sf::RenderWindow& window); // za iscrtavanje menija
	virtual void moveUp(); // za pomeranje na stavku iznad hajlajtovane
	virtual void moveDown();  // za pomeranje na stavku ispod
	int getPressedItem() { return selectedItemIndex; } // vraca index hajlajtovane stavke

	float getHeight() { return height; } // ne secam se dal mi ove dve 
	float getWidth() { return width; }  //  uopste trebaju but oky...

};

