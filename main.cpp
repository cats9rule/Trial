#include "ScoreNLevel.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include "Menu.h"
#include "Gallery.h"
#include "MainState.h"
#include "GalleryState.h"

#define WIDTH 800
#define HEIGHT 600

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;

	return 1;
};


int main()
{
	srand(time(0));
	ScoreNLevel ScoreOrLevel;
	
	RenderWindow window(VideoMode(800, 600), "TeddyBear Tetris", sf::Style::Titlebar);
	window.setFramerateLimit(60);
	
	//background and frames
	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/backgroung.png");
	t3.loadFromFile("images/index.png");
	t4.loadFromFile("images/background1.png");
	t5.loadFromFile("images/background2.png");
	
	Sprite s(t1), background(t2), background2(t4), background3(t5);// frame(t3);
	//frame.move(28,69);
	
	//numbers 
	int brojac = 1;
	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;
	ScoreOrLevel.setScore(0); //Ne treba  nam ovo u zavrsnom delu,setovano je u 
	// clasi na 0

	//bool
	bool neveninDeo = true;
	bool play = false;
	bool levelUp = false;
	bool gameplay = true;
	bool paused = false;
	bool restartGame = false;
	bool gameover = false;
	bool makeFigures = true;

	//FONT
	Font fontDusan;
	fontDusan.loadFromFile("font/VCR_OSD_MONO_1.001.ttf");

	//TEXT
	Text myscore;
	myscore.setFont(fontDusan);
	myscore.setCharacterSize(30);
	myscore.move(110, 7);

	String GameoverText = "GAME OVER";
	Text textGameover(GameoverText, fontDusan, 80);
	textGameover.Bold;
	textGameover.move(200, 240);

	String pausetext = "PAUSED";
	Text text(pausetext, fontDusan, 60);
	text.Bold;
	text.move(295, 240);

	String scoreText = "SCORE";
	Text textScore(scoreText, fontDusan, 30);
	textScore.Bold;
	textScore.move(10, 7);

	String levelText = "LEVEL";
	Text TextLevel(levelText, fontDusan, 30);
	TextLevel.Bold;
	TextLevel.move(10, 550);

	Text mylevel;
	mylevel.setFont(fontDusan);
	mylevel.setCharacterSize(30);
	mylevel.move(110, 550);

	String startAgainText = "Press ENTER to start again";
	Text startAgain(startAgainText, fontDusan, 20);
	startAgain.Italic;
	startAgain.setFillColor(Color::Yellow);
	startAgain.move(259, 350);

	//clock
	Clock clock;

	// Nevenin DEO
	int ind = -1;
	//sf::RenderWindow windoww(sf::VideoMode(WIDTH, HEIGHT), "TeddyBear Tetris", sf::Style::Titlebar);
	MainState maain;
	GalleryState galleryy;
	maain.EnterState();

	//Nevenin DEO
	mjau:
	if (neveninDeo == true) {
		while (maain.isInState()) {
			here:
			ind = maain.HandleEvents(window);
			if (ind == 2) {
				maain.ExitState();
			}
			maain.DrawStuff(window);
			window.display();
			if (ind == 1)
			{
				play = true;
				neveninDeo = false;
				goto thiss;
			}
		}
		if (!maain.isInState() && ind == 2) {

			galleryy.EnterState();
			while (galleryy.isInState()) {
				ind = galleryy.HandleEvents(window);
				if (ind == 4) {
					galleryy.ExitState();
					maain.EnterState();
					goto here;
				}

				galleryy.DrawStuff(window);
				window.display();
			}
			
		}
	}
thiss:
	if (play == true) {
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event e;
			while (window.pollEvent(e))
			{

			start:
				if (restartGame == true)
				{
					makeFigures = true;
					gameover = false;
					paused = false;
					gameplay = true;
					ScoreOrLevel.levelOne();
					ScoreOrLevel.setScore(0);
					restartGame = false;
					for (int i = 0; i < M; i++)
						for (int j = 0; j < N; j++)
							field[i][j] = 0;
					window.clear(Color::Black);
					goto start;
				}
				///Ispisivanje scora i levela
				std::stringstream ss;
				ss << ScoreOrLevel.returnScore();
				myscore.setString(ss.str());

				std::stringstream ll;
				ll << ScoreOrLevel.returnLevel();
				mylevel.setString(ll.str());

				if (gameplay == true) {
					if (e.type == Event::KeyPressed)
						if (e.key.code == Keyboard::Up) rotate = true;
						else if (e.key.code == Keyboard::Left) dx = -1;
						else if (e.key.code == Keyboard::Right) dx = 1;
				}
				if (gameover == true)
					if (e.type == Event::KeyPressed)
						if (e.key.code == Keyboard::Enter)
						{
							restartGame = true;
							std::cout << restartGame << std::endl;
						}
				if (e.type == Event::KeyPressed) {
					if (e.key.code == Keyboard::Space)
					{
						if (gameplay == false)
							gameplay = true;
						else
							gameplay = false;
					}
					if (e.key.code == Keyboard::Escape)
					{
						play = false;
						neveninDeo = true;
						restartGame = true;
						goto mjau;
					}

				}


			}
			if (gameplay == true)
				if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;


			//// <- Move -> ///
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
			if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

			//////Rotate//////
			if (rotate)
			{
				Point p = a[1]; //center of rotation
				for (int i = 0; i < 4; i++)
				{
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
			}

			///////Tick//////
			if (timer > delay)
			{
				for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

				if (!check())
				{
					for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;

					colorNum = 1 + rand() % 7;
					int n = rand() % 7;
					for (int i = 0; i < 4; i++)
					{
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				}

				timer = 0;
			}


			///////check lines//////////
			int k = M - 1;
			for (int i = M - 1; i > 1; i--)
			{
				int count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[i][j]) count++;
					field[k][j] = field[i][j];
				}

				if (count < N)
				{
					k--;
				}
				if (count == N) //ovo govno je trebalo za skor
				{
					ScoreOrLevel.ScoreUp();
					levelUp = true;
				}
			}

			dx = 0; rotate = 0;
			///Uslovi za evente
			if (gameplay == true)
			{
				delay = 0.3 - ((float)ScoreOrLevel.returnLevel() / 100);
				paused = false;
			}
			else
			{
				delay = 100;
				paused = true;
			}
			if (levelUp == true)
			{
				std::cout << ScoreOrLevel.returnLevel() << std::endl;
				std::cout << ScoreOrLevel.returnScore() << std::endl;
				std::cout << delay << std::endl;
				levelUp = false;
			}
			if (ScoreOrLevel.returnScore() >= 500 && ScoreOrLevel.returnLevel() < 21)
			{
				ScoreOrLevel.LevelUp();
				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
						field[i][j] = 0;
				ScoreOrLevel.setScore(0);

			}
			//VRH FIELDA
			for (int j = 0; j < 4; j++)
				for (int i = N - 1; i > 0; i--)
					if (field[j][i] == true) //focus on this shit!!!
					{
						delay = 0.001;
						gameover = true;
					}

			/////////draw//////////
			window.clear(Color::Black);
			if (ScoreOrLevel.returnLevel() <= 7)window.draw(background);
			else if (ScoreOrLevel.returnLevel() > 7 && ScoreOrLevel.returnLevel() <= 14) window.draw(background2);
			else if (ScoreOrLevel.returnLevel() > 14 && ScoreOrLevel.returnLevel() <= 21) window.draw(background3);
			window.draw(textScore);
			window.draw(myscore);
			if (gameover == false)
			{
				window.draw(mylevel);
				window.draw(TextLevel);
			}
			//window.draw(frame);
			if (paused == true && gameover == false) window.draw(text);
			if (gameover == true)
			{
				window.draw(textGameover);
				gameplay = false;
				makeFigures = false;
				window.draw(startAgain);
			}

			if (makeFigures == true) {
				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
					{
						if (field[i][j] == 0) continue;
						s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
						s.setPosition(j * 18, i * 18);
						s.move(28, 31); //offset
						window.draw(s);
					}
			}
			if (makeFigures == true)
				for (int i = 0; i < 4; i++)
				{
					s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
					s.setPosition(a[i].x * 18, a[i].y * 18);
					s.move(28, 31); //offset
					window.draw(s);

				}
			window.display();

		}
	}
	return 0;
}