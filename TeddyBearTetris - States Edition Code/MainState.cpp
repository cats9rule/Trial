#include "MainState.h"
#include <iostream>

MainState::MainState() : State(), background(), bgMusic() {
		// background() i bgMusic() su u stvari poziv default konstruktora za ova dva objekta is SFML
		// nisam siurna ali cini mi se da bez ovoga baca neki exception
		// also mozda sam pre nego sto sam napisala to uspela da napravim virus xD
	
	bgMusic.openFromFile("bg-sound/dumbdumb.wav"); // ucitava pozadinsku muziku
	if (bgMusic.openFromFile("bg-sound/dumbdumb.wav"))
		std::cout << "dumb loaded successfully" << std::endl;
	bgMusic.setLoop(true); // setuje da se na kraju pesme ponovo pusta od pocetka
	bgMusic.setVolume(100);

	if (t.loadFromFile("images/cityscapeBG.jpg")) { // ucitava pozadinu
		background.setTexture(t);
	}
	else std::cout << "File not good..." << std::endl;

	menu.SetMenu(800, 600, 60, 3, "mm.txt"); // setuje meni na 800x600 velicinu, font za stavke je 60, a ima 3 stavke
}

MainState::~MainState() {}

void MainState::playMusic() {
	bgMusic.play(); // samo pusta muziku lol, mislimd a mi je mozda trebalo za nesto van klase da je pustim pa je zato tu fja
}

void MainState::EnterState() {
	playMusic(); // dok je u stanju, ide muzika
	inState = true; // setuje idnikator na true da je u stanju MainState
}

void MainState::ExitState() {
	inState = false; // nije vise u stanju
	bgMusic.stop(); // prekida muziku, sta ce nam ako nije u tom stanju
}

int MainState::HandleEvents(sf::RenderWindow& gameWindow) { // this gets tricky
	sf::Event event;
	int indicator = 0;	// 1 for play, 2 for gallery, 3 for exit, prakticno povratna vrednost jer mi treba za main()
						// da se zna gde treba da ode, u mainu ima mnogo petlji
	while (gameWindow.pollEvent(event)) // ako ima nekog "dogadjaja" ima i petlje
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:  // moguci tasteri: up, down, enter (return in sfml)
			switch (event.key.code)
			{
			case sf::Keyboard::Up: // ide stavku gore
				menu.moveUp();
				break;

			case sf::Keyboard::Down: // ide stavku dole
				menu.moveDown();
				break;

			case sf::Keyboard::Return:  // kad je pritisnut enter, tj izabrana stavka iz menija
				switch (menu.getPressedItem()) 
				{
				case 0: // ako ej ziaran play
					std::cout << "Play button has been pressed" << std::endl;
					indicator = 1; // ovo ce da sluzi da se uveze sa GameState-om
					break;
				case 1: // ako je izabrana galerija
					std::cout << "Gallery button has been pressed" << std::endl;
					indicator = 2;
					break;
				case 2: // ovo ako je izabran exit
					ExitState();
					indicator = 3;
					gameWindow.close(); // zatvara game
					break;
				}

				break;
			}

			break;

		}
	}

	gameWindow.clear();
	DrawStuff(gameWindow);
	/*gameWindow.draw(background);
	menu.draw(gameWindow);
	gameWindow.display();*/
	return indicator;
}

void MainState::DrawStuff(sf::RenderWindow& gameWindow) { // iscrtava stvari jednu preko druge u redosledu navodjenja
	gameWindow.draw(background); // izcrtava pozadinu
	menu.draw(gameWindow); // izcrtava meni
	gameWindow.display(); // prikazuje sve sto je nacrtao
}