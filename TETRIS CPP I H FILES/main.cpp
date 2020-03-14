#include "ScoreNLevel.h"

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
	
	RenderWindow window(VideoMode(800, 600), "TETRIS!", Style::Default | Style::Close);
	window.setFramerateLimit(60);
	
	//background and frames
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/backgroung.png");
	t3.loadFromFile("images/grid.png");
	
	Sprite s(t1), background(t2), frame(t3);

	frame.move(18, 18);
	//numbers 
	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;
	ScoreOrLevel.setScore(700); //Ne treba  nam ovo u zavrsnom delu,setovano je u 
	// clasi na 0

	//bool
	bool levelUp = false;
	bool gameplay = true;
	bool paused = false;
	bool restartGame = false;
	bool gameover = false;
	bool makeFigures = true;

	//FONT
	Font font;
	font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf");

	//TEXT
	Text myscore;
	myscore.setFont(font);
	myscore.setCharacterSize(30);
	myscore.move(110, 7);

	String GameoverText = "GAME OVER";
	Text textGameover(GameoverText, font, 80);
	textGameover.Bold;
	textGameover.move(200, 240);

	String pausetext = "PAUSED";
	Text text(pausetext, font, 60);
	text.Bold;
	text.move(295, 240);

	String scoreText = "SCORE";
	Text textScore(scoreText, font, 30);
	textScore.Bold;
	textScore.move(10, 7);

	String levelText = "LEVEL";
	Text TextLevel(levelText, font, 30);
	TextLevel.Bold;
	TextLevel.move(10, 550);

	Text mylevel;
	mylevel.setFont(font);
	mylevel.setCharacterSize(30);
	mylevel.move(110, 550);

	String startAgainText = "Press ENTER to start again";
	Text startAgain(startAgainText, font, 20);
	startAgain.Italic;
	startAgain.setFillColor(Color::Yellow);
	startAgain.move(259, 350);

	//clock
	Clock clock;

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

			if (e.type == Event::Closed)
				window.close();
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
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Space)
				{
					if (gameplay == false)
						gameplay = true;
					else
						gameplay = false;
				}
				
		}
		if(gameplay == true)
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
			std::cout << ScoreOrLevel.returnScore() <<std::endl;
			std::cout << delay << std::endl;
			levelUp = false;
		}
		if (ScoreOrLevel.returnScore() >= 500 && ScoreOrLevel.returnLevel() < 21)
		{
			ScoreOrLevel.LevelUp();
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
		window.draw(background);
		window.draw(textScore);
		window.draw(myscore);
		if (gameover == false)
		{
			window.draw(mylevel);
			window.draw(TextLevel);
		}
		window.draw(frame);
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
		if(makeFigures == true)
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31); //offset
			window.draw(s);
			
		}
		window.display();
	}
	return 0;
}
