#include "Menu.h"
#include <iostream>
#include <fstream>
#include <string>

Menu::Menu(){ } // samo pravi objekat, za postavljanje svega sluzi SetMenu()

Menu::~Menu(){ }

void Menu::SetMenu(float wwidth, float wheight, int font_size, int no_of_items, std::string fName) {
	if (!font.loadFromFile("font/SiliconeFilled.ttf"))
	{
		std::cout << "Menu font not loaded." << std::endl;
	}
	if (!titleFont.loadFromFile("font/SiliconeHollow.ttf"))
	{
		std::cout << "Title font not loaded." << std::endl;
	}
	width = wwidth;   //   treba da budu sirina i visina prozora, koristim ih da bih relativno odredila
	height = wheight; //   gde se ispisuju stavke na meniju i naslov menija

	noOfItems = no_of_items; // koristim meni klasu i za main menu i za gallery pa mi zato treba ovo da ogranicim broj stavki
	fontSize = font_size;
	std::ifstream inputText(fName, std::ios::out); // iz fajla se cita sadrzaj menija, tj sta pise kao stavka

	for (int i = 0; i < noOfItems; i++) {
		menu[i].setFont(font);
		menu[i].setCharacterSize(fontSize);
		if (i == 0) 
			menu[i].setFillColor(sf::Color(176, 44, 86)); // za prvu stavku se inicijalno bira kao da je highlighted
		else
			menu[i].setFillColor(sf::Color::White); // ostale stavke su bele boje
		std::string s;
		if (inputText.good()) { // citaju se stavke iz fajla
			std::getline(inputText, s);
			menu[i].setString(s);
		}
		else
			std::cout << "Fajl nije dobar." << std::endl;
		menu[i].setPosition(sf::Vector2f(width / (noOfItems * 3), (height / (noOfItems + 1) * (i + 1)) - fontSize / 3));
			// postavlja poziciju stavki na meniju, u odnosu na sirinu i visinu 
			// prozora za game i u zavisnosti od velicine fonta (da se ne preklapa tekst)
	}

	selectedItemIndex = 0; // inicijalno selektovana prva stavka

	Title.setFont(titleFont);
	Title.setStyle(sf::Text::Bold);
	Title.setCharacterSize(48);
	if (inputText.good()) {
		std::string s;
		std::getline(inputText, s); // naslov menija treba da bude napisan na samom kraju fajla
		Title.setString(s);
	}
	else
		std::cout << "Fajl nije dobar." << std::endl;
	Title.setFillColor(sf::Color(27, 9, 66));
	sf::FloatRect bound = Title.getLocalBounds();			// ovo sluzi da bi se naslov menija centrirao
	Title.setOrigin(bound.width / 2, bound.height / 2);		// postavlja na centar naslova tacku u odnosu na koju se setuje pozicija
	Title.setPosition(width / 2, height / 15);				// setuje poziciju na centar game window-a
	inputText.close();
}

void Menu::draw(sf::RenderWindow& window) 
{
	window.draw(Title);			// iscrtava naslov na prozoru koji mu je prosledjen
	for (int i = 0; i < noOfItems; i++)
	{
		window.draw(menu[i]); // iscrtava stavke iz menija
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White); 
		selectedItemIndex--;
		switch (selectedItemIndex) {			// za razlicite boje highlighta za stavke
		case 0:
			menu[selectedItemIndex].setFillColor(sf::Color(176, 44, 86));	// highlight za Play (pinkasto)
			break;
		case 1:
			menu[selectedItemIndex].setFillColor(sf::Color(0, 18, 11));		// highlight za Gallery (teget)
			break;
		case 2:
			menu[selectedItemIndex].setFillColor(sf::Color(255, 217, 135));	// highlight za Exit (zuto)
		}
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < noOfItems)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		switch (selectedItemIndex) {  // isti djavo kao za moveUp
		case 0:
			menu[selectedItemIndex].setFillColor(sf::Color(176, 44, 86));
			break;
		case 1:
			menu[selectedItemIndex].setFillColor(sf::Color(0, 18, 11));
			break;
		case 2:
			menu[selectedItemIndex].setFillColor(sf::Color(255, 217, 135));
		}
	}
}
