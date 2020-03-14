#include "Gallery.h"
#include <iostream>
#include <fstream>

Gallery::Gallery() {
	unlockedIndex = 21; // ovo bi trebalo da se cita iz fajla ali za testiranje sam setovala da su sve unlocked
	imageOpened = false; // inicijalno nije otvrena nijedna slika
	openedImageIndex = -1; // stavnjela nemoguca vrednost
}

Gallery::Gallery(int index, float width, float height, int fsize) : Menu(){ // koristi k za Menu (fuck you LNK2019)
	SetMenu(width, height, fsize, 21, "gallItems.txt"); // setuje izgled menija za galeriju
	unlockedIndex = index; // zamisljeno je da se index cita iz fajla i prosledi konstruktotru
	openedImageIndex = -1;
	imageOpened = false;
}

Gallery::~Gallery() { }

void Gallery::SetMenu(float wwidth, float wheight, int font_size, int no_of_items, std::string fName) {
	if (!font.loadFromFile("font/SiliconeFilled.ttf"))
	{
		// handle error
	}
	if (!titleFont.loadFromFile("font/SiliconeHollow.ttf"))
	{
		// handle error
	}
	width = wwidth;
	height = wheight;

	noOfItems = no_of_items;
	fontSize = font_size;
	std::ifstream inputText(fName, std::ios::out);

	for (int i = 0; i < noOfItems; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(fontSize);
		menu[i].setOutlineThickness(1);
		menu[i].setOutlineColor(sf::Color(27, 9, 66));
		if (i == 0)
			menu[i].setFillColor(sf::Color(255, 217, 135));
		else 
			menu[i].setFillColor(sf::Color::White);

		std::string s;
		if (inputText.good()) { // stavke se citaju iz fajla
			std::getline(inputText, s);
			menu[i].setString(s);
		}
		else
			std::cout << "Fajl nije dobar." << std::endl;
		if (i < 7) { // ovo sluzi da bi se stavke u meniju podelile u tri kolone
			menu[i].setPosition(sf::Vector2f(width / (noOfItems * 3) + 75, (height / (noOfItems + 1) * (i + 1) * 2 + 150) - fontSize / 4 ));
		}
		else if (i<14)
			menu[i].setPosition(sf::Vector2f(width / (noOfItems * 3) + fontSize * 6 + 75, (height / (noOfItems + 1) * (i-6) * 2 + 150) - fontSize / 4 ));
		else
			menu[i].setPosition(sf::Vector2f(width / (noOfItems * 3) + fontSize * 12 + 75, (height / (noOfItems + 1) * (i - 13) * 2 + 150) - fontSize / 4 ));
	}

	selectedItemIndex = 0;

	Title.setFont(titleFont);
	Title.setStyle(sf::Text::Bold);
	Title.setCharacterSize(48);
	if (inputText.good()) { // naslov se nalazi na kraju fajla, a sad shvatam da ne mora and make a mental note to change this xD
		std::string s;
		std::getline(inputText, s);
		Title.setString(s);
	}
	else
		std::cout << "Fajl nije dobar." << std::endl;
	Title.setFillColor(sf::Color(27, 9, 66));
	sf::FloatRect bound = Title.getLocalBounds(); // isto kao za naslov iz Menu
	Title.setOrigin(bound.width / 2, bound.height / 2);
	Title.setPosition(width / 2, height / 15);
	inputText.close();
}

void Gallery::moveUp() {
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color(255, 217, 135)); // setuje highlighted color (zuto)

	}
}

void Gallery::moveDown() {
	if (selectedItemIndex + 1 < noOfItems) 
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color(255, 217, 135)); // isto kao za moveUp
	}
}

bool Gallery::OpenImage(int index) {
	if (index <= unlockedIndex) { // necemo da otvaramo sliku ako nije unlockovana
		std::string ime;
		
		std::ofstream aux("pom.txt", std::ios::trunc);	// fajl sluzi samo da se upise naziv slike koja treba da se otvori
														// cisto da ne bi morao switch sa 21 slucajem
		if (aux.good()) {
			aux << "gallery/";
			aux << "Level" << index + 1 << ".jpg" << std::endl; // upisuje ime fajla za otvaranje u zavisnosti od indeksa slike
			aux.close();
		}
		std::ifstream auxIn("pom.txt");
		if (auxIn.good()){

			auxIn >> ime;
			imgToOpen.loadFromFile(ime); // cita sliku
			collection.setTexture(imgToOpen);
			aux.close();
			openedImageIndex = index;
			imageOpened = true;
			collection.setScale(0.47, 0.47); // setuje scale SLIKE SU JBENO OGROMNE
			return 1;
		}
		else {
			std::cout << "File not good." << std::endl;
			return 0;
		}
	}
	else std::cout << "Image not unlocked." << std::endl; // xoxo nece mocii njanja i swear im sane.
	return 0;
}

void Gallery::displayImage(sf::RenderWindow& window) {
	collection.setPosition(getWidth() / 2, 0); // setuje poziciju tako da se slika prikaze na desnoj polovini prozora
	window.draw(collection); // fja iz SFML-a koja crta sprite na window
}

void Gallery::CloseImage() {
	collection.setScale(0, 0); // prakticno sakriva sliku, idk vrv moze da se drugacije odradi to but who cares ovo radi
	openedImageIndex = -1;
	imageOpened = false;
}