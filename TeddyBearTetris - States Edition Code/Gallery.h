#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"

class Gallery :public Menu {
private:
	sf::Texture imgToOpen; // pamti sliku koja treba da se otvori
	sf::Sprite collection; // sprite koji sluzi kao placeholder da iscrta sliku (posto je samo sprite drawable)
	int unlockedIndex; // cuva indeks poslednje unlockovane slike
	int openedImageIndex; // cuva indeks otvorene slike
	bool imageOpened; // stanje da li je slika otvorena ili ne

public:
	Gallery();
	Gallery(int index, float width, float height, int fsize);	// k koji setuje font menija za galeriju, poziva funkciju SetMenu
																// i to vrv moze da se optimizuje u klasi Menu...
	~Gallery();
	void SetMenu(float wwidth, float wheight, int font_size, int no_of_items, std::string fName); 
			// radi isto sto i SetMenu iz Menu, ali ima vise stavki pa ne vodi racuna o nekim stvarima, kao npr boja hajlajta
			// i jos neke izmene
	void moveUp(); // stavka gore
	void moveDown(); // stavka dole

	bool OpenImage(int index); // fja za otvaranje slike (ucitavanje, pre bi se reklo)
	void CloseImage(); // zatvaranje slike
	int GetUnlockedIndex() { return unlockedIndex; }
	bool isImageOpened() { return imageOpened; } // vraca stanje da li je neka slika otvorena
	void displayImage(sf::RenderWindow& window); // prikazuje sliku na prozor

};