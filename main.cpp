#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <conio.h>
#include <sstream>

//const int ground = 150;
const int ts = 32;
const int MAP_HEIGHT = 32;
const int MAP_WIDTH = 212;
float offsetX = 0, offsetY = 0; //движение камеры
int level = 1; //уровень камеры
bool managment = true; //управление игроком
bool cam = true; //управление камерой разрешает либо запрещает двигаться камере
bool finish = false; // пройден ли финальный уровень
bool win = false; //пройден ли уровень
bool bonus = false;
bool backgroundIsBlack = false;
const int count = 15;




sf::String TileMap[MAP_HEIGHT]{
	"                                                                                                                                                                                                                   ",
	"              x                      x                                     x                                                                                                                                       ",
	"                            x                x                                                               x                                           xx                                                        ",
	"                                                                                                                                                                                                     x             ",
	"                                                  x                                       x                                                                                                                        ",
	"                                                                                                                                                                                                                   ",
	"                                                                                                                                                                                   q                               ",
	"                                                                                                         q                                                                        b                                ",
	"           bbqbqbb     bbqbbb                  q                                                                                                     bbbqbbbb                    q                                 ",
	"g                                                                                                                                                                               b                                  ",
	"g                                                                  bbbqbbb                           kl       kl               uu   u                                          q                         h         ",
	"g    b  bbqbbbb                           q    q    q                                     kl         mn       mn              uuu   uu            qqbqq      bbbq                  u         bqb                   ",
	"g                                                                               kl        mn         mn       mn             uuuu   uuu                                kl         uu                               ",
	"g               t        u      t                           t                   mn        mn         mn       mn            uuuuu   uuuu               t               mn       uuuu                t              ",
	"ggggggggggggggggggggg    gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
	"ggggggggggggggggggggg    gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg   ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg",
	"                                                                                                               m                                                                                                   ",
	"                                                                                                               m                                                                                                   ",
	"                                                                                                               m                                                                                                   ",
	"                                                                                                               m                                                                                                   ",
	"                                                                                                               mn                                                                                                  ",
	"                                                                                        vv        vvvvvvvvvvvv mn                                                                                                  ",
	"                                                                                        vv                     mn                                                                                                  ",
	"                                                                                        vv                     mn                                                                                                  ",
	"                                                                                        vv                     mn                                                                                                  ",
	"                                                                                        vv         cccccc      mn                                                                                                  ",
	"                                                                                        vv         cccccc      mn                                                                                                  ",
	"                                                                                        vv        zzzzzzz      mn                                                                                                  ",
	"                                                                                        vv     cccccc          mn                                                                                                  ",
	"                                                                                        vv    cccccccc       f  n                                                                                                  ",
	"                                                                                        vv    zzzzzzzz          n                                                                                                  ",
	"                                                                                        zzzzzzzzzzzzzzzzzzzzzzzzzz                                                                                                 ",
};

class Sound {
public:
	sf::SoundBuffer s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	sf::Sound win, pipe, pause, kill, jump, gameOver, destroyBlock, damage, button, bonus;
	sf::Music music, music_down;

	void setSound() {
		s1.loadFromFile("sound/win.ogg");
		s2.loadFromFile("sound/pipe.ogg");
		s3.loadFromFile("sound/pause.ogg");
		s4.loadFromFile("sound/kill.ogg");
		s5.loadFromFile("sound/jump.ogg");
		s6.loadFromFile("sound/gameOver.ogg");
		s7.loadFromFile("sound/destroyBlock.ogg");
		s8.loadFromFile("sound/damage.ogg");
		s9.loadFromFile("sound/button.ogg");
		s10.loadFromFile("sound/bonus.ogg");

		win.setBuffer(s1);
		pipe.setBuffer(s2);
		pause.setBuffer(s3);
		kill.setBuffer(s4);
		jump.setBuffer(s5);
		gameOver.setBuffer(s6);
		destroyBlock.setBuffer(s7);
		damage.setBuffer(s8);
		button.setBuffer(s9);
		bonus.setBuffer(s10);

		music.openFromFile("sound/music.ogg");
		music.setVolume(20);
		music.setLoop(true);

		music_down.openFromFile("sound/music_down.ogg");
		music.setVolume(20);
		music.setLoop(true);
	}
};

Sound sound;

class Menu {
public:
	sf::Texture t_exit, t_pause, t_start, t_back, t_back_to_menu, t_end, t_restart, t_screen, t_title;
	sf::Texture t_control, t_control_1, t_control_2, t_control_3, t_control_4, t_continue, t_win;
	sf::Sprite exit, s_pause, start, back, back_to_menu, end, restart, screen, title;
	sf::Sprite s_control, control_1, control_2, control_3, control_4, s_continue, s_win;
	bool menu, game, play, pause, win, die, control, run;
	int px;
	Menu() {
		t_title.loadFromFile("images/title.png");
		t_exit.loadFromFile("images/exit.png");
		t_back.loadFromFile("images/back.png");
		t_back_to_menu.loadFromFile("images/back_to_menu.png");
		t_start.loadFromFile("images/start.png");
		t_end.loadFromFile("images/end.png");
		t_pause.loadFromFile("images/pause.png");
		t_continue.loadFromFile("images/continue.png");
		t_restart.loadFromFile("images/restart.png");
		t_control.loadFromFile("images/control.png");
		t_control_1.loadFromFile("images/control_1.png");
		t_control_2.loadFromFile("images/control_2.png");
		t_control_3.loadFromFile("images/control_3.png");
		t_control_4.loadFromFile("images/control_4.png");
		t_screen.loadFromFile("images/screen.png");
		t_win.loadFromFile("images/win.png");

		title.setTexture(t_title);
		exit.setTexture(t_exit);
		back.setTexture(t_back);
		back_to_menu.setTexture(t_back_to_menu);
		start.setTexture(t_start);
		end.setTexture(t_end);
		restart.setTexture(t_restart);
		s_pause.setTexture(t_pause);
		s_continue.setTexture(t_continue);
		s_control.setTexture(t_control);
		control_1.setTexture(t_control_1);
		control_2.setTexture(t_control_2);
		control_3.setTexture(t_control_3);
		control_4.setTexture(t_control_4);
		screen.setTexture(t_screen);
		s_win.setTexture(t_win);

		title.setPosition(250, 100);
		exit.setPosition(480, 250);
		start.setPosition(130, 250);
		s_control.setPosition(310, 350);
		menu = true;
		game = false;
		play = false;
		win = false;
		die = false;
		pause = false;
		control = false;
		run = false;
	}
};


class Player {
public:
	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	bool right;
	bool scal;
	bool live;
	bool draw;
	sf::Sprite sprite;
	int countCoins = 0;
	int life = 3;
	int score = 0;
	float currentFrame;
	Player(sf::Texture& image) {
		sprite.setTexture(image);
		rect = sf::FloatRect(0, 0, 45, 45);
		sprite.setTextureRect(sf::IntRect(19, 0, 15, 15));
		sprite.scale(sf::Vector2f(3.f, 3.f));
		dx = dy = 0;
		currentFrame = 0;
		draw = true;
		live = true;
		right = true; //контролировать отображение спрайта при остановке и прыжке (нужная сторона)
		scal = true; //взаимодействие с платформами
	}

	void restart() {
		countCoins = 0;
		life = 3;
		score = 0;
		rect.left = 0;
		rect.top = 243;
		offsetX = 0;
		offsetY = 0;
		right = true;
		dx = 0;
		dy = 0;
	}
	void update(float time) {
		rect.left +=  1.3 * dx * time;
		Collision(0);
		if (!onGround) {
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		onGround = false;
		Collision(1);
		if (dx != 0 || live) {
			currentFrame += 0.006 * time;
			if (currentFrame > 3) {
				currentFrame -= 3;
			}
		}
		else if (!live) {
			sprite.setTextureRect(sf::IntRect(15, 0, 15, 15));
		}
		if (dx > 0) {
			if (dy == 0) {
				sprite.setTextureRect(sf::IntRect(17 * int(currentFrame), 0, 15, 15));
			}
			else {
				sprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
			}
			right = true;
		}
		if (dx < 0) {
			if (dy == 0) {
				sprite.setTextureRect(sf::IntRect(17 * int(currentFrame) + 17, 0, -15, 15));
			}
			else {
				sprite.setTextureRect(sf::IntRect(15, 0, -15, 15));
			}
			right = false;
		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	void Collision(float dir) {
		for (int i = rect.top / ts; i < (rect.top + rect.height) / ts; ++i) {
			for (int j = rect.left / ts; j < (rect.left + rect.width) / ts; ++j) {
				if ((TileMap[i][j] == 'g' || TileMap[i][j] == 'e' || TileMap[i][j] == 'b' || TileMap[i][j] == 'q' ||
					TileMap[i][j] == 'k' || TileMap[i][j] == 'l' || TileMap[i][j] == 'n' || TileMap[i][j] == 'u' ||
					TileMap[i][j] == 'z' || TileMap[i][j] == 'v' || TileMap[i][j] == 'm' || TileMap[i][j] == 'f' || TileMap[i][j] == 'w') && scal) {
					if (dx > 0 && dir == 0) {
						rect.left = j * ts - rect.width;
					}
					if (dx < 0 && dir == 0) {
						rect.left = j * ts + ts;
					}
					if (dy > 0 && dir == 1) {
						rect.top = i * ts - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && dir == 1) {
						rect.top = i * ts + ts;
						dy = 0;
						if (TileMap[i][j] == 'q') {
							TileMap[i][j] = 'w';
							TileMap[i - 1][j] = 'c';
							sound.destroyBlock.play();
						}
					}
				}
				if (TileMap[i][j] == 'c') {
					TileMap[i][j] = '6';
					countCoins++;
					score += 20;
					sound.bonus.play();
				}
			}
		}
	}

};

enum enemy {
	MUSHROOM = 1,
	TURTLE = 2
};

class Enemy {
public:
	float dx, dy;
	sf::FloatRect rect;
	sf::Sprite sprite;
	float currentFrame;
	bool go, live, draw;
	enemy typeOfEnemy;
	int t = 0, run; //run for turtle, t for mushroom

	void set(sf::Texture& texture, int x, int y, enemy type) {
		sprite.setTexture(texture);
		typeOfEnemy = type;
		if (typeOfEnemy < 3) {
			rect = sf::FloatRect(x, y - 14 * (typeOfEnemy - 1), ts, ts);
			if (!backgroundIsBlack) {
				sprite.setTextureRect(sf::IntRect(0, 0, ts, ts + 14 * (typeOfEnemy - 1))); // (0, 0, 32, 32) for mushroom and (0, 0, 32, 46) for turtle
			}
			else {
				sprite.setTextureRect(sf::IntRect(0, ts, ts, ts + 14 * (typeOfEnemy - 1))); //underground
			}

			if (typeOfEnemy == 1) {
				dx = 0.06;
			}
			else if (typeOfEnemy == 2) {
				dx = 0.04;
			}
			currentFrame = 0;
			go = true;
			draw = true;
			live = true;
			t = 0;
			run = 1;
		}
	}

	void update(float time) {
		if ((go && live && typeOfEnemy == 1) || (typeOfEnemy == 2 && (run == 1 || run == 3))) {
			rect.left += dx * time;
		}
		Collision();
		if (typeOfEnemy < 3) {
			if (live) {
				currentFrame += 0.01;
				if (currentFrame > 2) {
					currentFrame -= 2;
				}
			}
			else {
				currentFrame = 2;
			}

			if (typeOfEnemy == 1) {
				if (!backgroundIsBlack) {
					sprite.setTextureRect(sf::IntRect(ts * int(currentFrame), 0, ts, ts));
				}
				else {
					sprite.setTextureRect(sf::IntRect(ts * int(currentFrame), ts, ts, ts));
				}
			}
			else if (typeOfEnemy == 2) {
				if (dx < 0) {
					if (!backgroundIsBlack) {
						sprite.setTextureRect(sf::IntRect(ts * int(currentFrame), 0, ts, ts + 14));
					}
					else {
						sprite.setTextureRect(sf::IntRect(ts * int(currentFrame), ts + 14, ts, ts + 14));
					}
				}
				if (dx > 0) {
					if (!backgroundIsBlack) {
						sprite.setTextureRect(sf::IntRect(ts * int(currentFrame) + ts, 0, 0, -ts + 14));
					}
					else {
						sprite.setTextureRect(sf::IntRect(ts * int(currentFrame) + ts, ts + 14, ts, -ts + 14));
					}
				}
			}
		}

		if (typeOfEnemy == 1 && t <= 50 && !live) {
			t++;
			if (t == 50) {
				draw = false;
			}
		}

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision() {
		
			for (int i = rect.top / ts; i < (rect.top + rect.height) / ts; ++i) {
				for (int j = rect.left / ts; j < (rect.left + rect.width) / ts; ++j) {
					if (TileMap[i][j] == 'm' || TileMap[i][j] == 'n' || TileMap[i][j] == 'u'
						|| TileMap[i][j] == 'v' || TileMap[i][j] == 'z' || TileMap[i][j] == 'f') {
						if (dx > 0) {
							rect.left = j * ts - rect.width;
							dx *= -1;
						}
						else if (dx < 0) {
							rect.left = j * ts + ts;
							dx *= -1;
						}
					}
				}
			}
		
		/*else if (typeOfEnemy == 2) {
			for (int i = rect.top / (ts + 14); i < (rect.top + rect.height) / (ts + 14); ++i) {
				for (int j = rect.left / ts; j < (rect.left + rect.width) / ts; ++j) {
					if (TileMap[i][j] == 'm' || TileMap[i][j] == 'n' || TileMap[i][j] == 'u'
						|| TileMap[i][j] == 'v' || TileMap[i][j] == 'z' || TileMap[i][j] == 'f') {
						if (dx > 0) {
							rect.left = j * ts - rect.width;
							dx *= -1;
						}
						else if (dx < 0) {
							rect.left = j * ts + ts;
							dx *= -1;
						}
					}
				}
			}

		}*/
	}
};

enum forText {
	SCORE = 1,
	LEVEL = 2,
	COINS = 3,
	LIFE = 4
};


sf::Text textManager(Player player, sf::Text text, forText number, sf::View view) {
	std::ostringstream count;
	switch (number) {
	case 1:
		count << player.score;
		text.setPosition(view.getCenter().x - 11 * ts, view.getCenter().y - 8 * ts);
		text.setString("score : " + count.str());
		break;
	case 2:
		count << level;
		text.setPosition(view.getCenter().x - 4 * ts, view.getCenter().y - 8 * ts);
		text.setString("level : " + count.str());
		break;
	case 3:
		count << player.countCoins;
		text.setPosition(view.getCenter().x + 2 * ts, view.getCenter().y - 8 * ts);
		text.setString("coins : " + count.str());
		break;
	case 4:
		count << player.life;
		text.setPosition(view.getCenter().x + 8 * ts, view.getCenter().y - 8 * ts);
		text.setString("life : " + count.str());
		break;
	}
	text.setCharacterSize(45);
	return text;
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(25 * ts, 16 * ts), "Mario!");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 25 * ts, 16 * ts));

	sf::Texture mario;
	mario.loadFromFile("images/Mario.png");
	Player p(mario);

	sf::Texture map1;
	map1.loadFromFile("images/map.png");
	sf::Sprite map(map1);

	float currentFrame = 0;

	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("images/font.ttf");
	sf::Text textScore("", font, 15);
	sf::Text textLevel("", font, 15);
	sf::Text textCoins("", font, 15);
	sf::Text textLife("", font, 15);

	sf::Texture mushroom, turtle;
	mushroom.loadFromFile("images/mushroom.png");
	turtle.loadFromFile("images/turtle.png");
	Enemy enemies[count];

	Menu menu;

	enemies[0].set(mushroom, ts * 28, ts * 13, MUSHROOM);
	enemies[1].set(mushroom, ts * 44, ts * 13, MUSHROOM);
	enemies[2].set(mushroom, ts * 75, ts * 13, MUSHROOM);
	enemies[3].set(mushroom, ts * 86, ts * 13, MUSHROOM);
	enemies[4].set(mushroom, ts * 106, ts * 13, MUSHROOM);
	enemies[5].set(mushroom, ts * 115, ts * 13, MUSHROOM);
	enemies[6].set(mushroom, ts * 121, ts * 13, MUSHROOM);
	enemies[7].set(mushroom, ts * 154, ts * 13, MUSHROOM);
	enemies[8].set(mushroom, ts * 160, ts * 13, MUSHROOM);
	enemies[9].set(mushroom, ts * 138, ts * 13, MUSHROOM);
	enemies[10].set(mushroom, ts * 150, ts * 13, MUSHROOM);
	enemies[11].set(mushroom, ts * 70, ts * 13, MUSHROOM);
	enemies[12].set(turtle, ts * 31, ts * 13, TURTLE);
	enemies[13].set(turtle, ts * 154, ts * 13, TURTLE);
	enemies[14].set(mushroom, ts * 102, ts * 30, MUSHROOM);

	sound.setSound();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition(window);
				if (event.key.code == sf::Mouse::Left) {
					if (menu.menu) {
						if (menu.exit.getGlobalBounds().contains(position.x, position.y)) {
							window.close();
							sound.button.play();
						}
						if (menu.start.getGlobalBounds().contains(position.x, position.y)) {
							menu.menu = false;
							menu.run = true;
							menu.play = true;
							menu.game = false;
							sound.button.play();
							sound.music.play();
						}
						if (menu.s_control.getGlobalBounds().contains(position.x, position.y)) {
							menu.menu = false;
							menu.control = true;
							menu.s_control.setPosition(300, 100);
							menu.control_1.setPosition(170, 200);
							menu.control_2.setPosition(170, 250);
							menu.control_3.setPosition(200, 300);
							menu.control_4.setPosition(200, 350);
							menu.back.setPosition(50, 450);
							sound.button.play();
						}
					}
					else if (menu.control) {
						if (menu.back.getGlobalBounds().contains(position.x, position.y)) {
							menu.menu = true;
							menu.control = false;
							menu.s_control.setPosition(310, 350);
							sound.button.play();
						}
					}
					if (menu.s_continue.getGlobalBounds().contains(position.x, position.y)) {
						//menu.run = true;
						menu.play = true;
						menu.pause = false;
						//menu.game = true;
						sound.button.play();
					}
					if (menu.back_to_menu.getGlobalBounds().contains(position.x, position.y)) {
						menu.run = false;
						menu.play = false;
						menu.menu = true;
						menu.pause = false;
						menu.die = false;
						menu.win = false;
						//menu.game = false;
						sound.button.play();
					}
					if (menu.restart.getGlobalBounds().contains(position.x, position.y)) {
						menu.run = true;
						menu.play = true;
						menu.pause = false;
						menu.die = false;
						menu.win = false;
						menu.game = false;
						sound.button.play();
					}
				}
				else if (event.key.code == sf::Mouse::Right) {
					menu.pause = true;
					menu.play = false;
					menu.s_pause.setPosition(260, 100);
					menu.restart.setPosition(130, 250);
					menu.s_continue.setPosition(490, 250);
					menu.back_to_menu.setPosition(270, 350);
					sound.pause.play();
					sound.music.pause();
				}
			}

		}
		if (menu.die || menu.win) {
			menu.run = false;
			menu.play = false;
			//menu.game = false;
			menu.restart.setPosition(120, 250);
			menu.back_to_menu.setPosition(390, 250);
			if (menu.die) {
				menu.end.setPosition(240, 100);
				sound.music.stop();
			}
			else {
				menu.s_win.setPosition(240, 100);
				sound.music.stop();
			}
		}

		if (!menu.game) {
			p.restart();
			backgroundIsBlack = false;
			enemies[0].set(mushroom, ts * 28, ts * 13, MUSHROOM);
			enemies[1].set(mushroom, ts * 44, ts * 13, MUSHROOM);
			enemies[2].set(mushroom, ts * 75, ts * 13, MUSHROOM);
			enemies[3].set(mushroom, ts * 86, ts * 13, MUSHROOM);
			enemies[4].set(mushroom, ts * 106, ts * 13, MUSHROOM);
			enemies[5].set(mushroom, ts * 115, ts * 13, MUSHROOM);
			enemies[6].set(mushroom, ts * 121, ts * 13, MUSHROOM);
			enemies[7].set(mushroom, ts * 154, ts * 13, MUSHROOM);
			enemies[8].set(mushroom, ts * 160, ts * 13, MUSHROOM);
			enemies[9].set(mushroom, ts * 138, ts * 13, MUSHROOM);
			enemies[10].set(mushroom, ts * 150, ts * 13, MUSHROOM);
			enemies[11].set(mushroom, ts * 70, ts * 13, MUSHROOM);
			enemies[12].set(turtle, ts * 31, ts * 13, TURTLE);
			enemies[13].set(turtle, ts * 154, ts * 13, TURTLE);
			enemies[14].set(mushroom, ts * 102, ts * 30, MUSHROOM);
			for (int i = 0; i < count; ++i) {
				enemies[i].go = true;
				enemies[i].live = true;
				enemies[i].draw = true;
				enemies[i].t = 0;
			}
			for (int i = 0; i < MAP_HEIGHT; ++i) {
				for (int j = 0; j < MAP_WIDTH; ++j) {
					if (TileMap[i][j] == 'w') {
						TileMap[i][j] = 'q';
						TileMap[i - 1][j] = ' ';
					}
					if (TileMap[i][j] == '6') {
						TileMap[i][j] = 'c';
					}
				}
			}
		}

		if (menu.play) {
			if (menu.run) {
				menu.run = false;
				menu.win = false;
				menu.die = false;
				menu.pause = false;
				menu.game = true;

				p.live = true;
				p.scal = true;

				//menu.play = true;
				managment = true;

				win = false;
				finish = false;
				cam = true;
			}

			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;

			if (!_kbhit()) { //если нет нажатия на клавиши, подгружается спрайт обычный стойки в зависимости от последней нажатой клавиши(влево или вправо), за это и отвечает перменная right
				if (p.onGround) {
					if (p.right) {
						p.sprite.setTextureRect(sf::IntRect(19, 0, 15, 15));

					}
					else {
						p.sprite.setTextureRect(sf::IntRect(19 + 15, 0, -15, 15));
					}
				}
			}


			if (managment && p.live) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					p.dx = -0.1;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					p.dx = 0.1;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					if (p.onGround) {
						p.dy = -0.4;
						p.onGround = false;
						if (p.right) {
							p.sprite.setTextureRect(sf::IntRect(0, 0, 15, 15)); //0 0 15 15
						}
						else {
							p.sprite.setTextureRect(sf::IntRect(15, 0, -15, 15)); // 15 0 -15 15
						}
					}
				}
			}

			//Движок камеры
			// 212 плиток по 32 пикселя - 6784 (конец карты)
			if (level == 1) {
				if (p.rect.left > 400 && p.rect.left < 212 * ts && cam) { //с какого расстояния от спрайта игрока до стены камера начнет и закончит движение
					offsetX = p.rect.left - 400;
				}
				if (p.rect.left >= 87 * ts && p.rect.left <= 96 * ts && p.rect.top >= 16 * ts) {  //для нижнего уровня снова работает гравитация
					p.scal = true;
					managment = true;
					p.draw = true;
					cam = false;
					backgroundIsBlack = true;
					offsetX = 87 * ts;
					offsetY = 17 * ts;
				}
			}


			//Движок игрока
			if (level == 1) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					if (p.rect.left > 89 * ts && p.rect.left < 91 * ts
						&& p.rect.top < 15 * ts && p.scal) {
						p.scal = false;    //отключаем все во время падения
						managment = false;
						p.draw = false;
						sound.pipe.play();
						sound.music.stop();
						sound.music_down.play();
					}
				}
				if (p.rect.left > 197 * ts) {
					p.dx = 0.2;
					menu.win = true;
					sound.win.play();
				}
			}

			//Движок камеры и игрока
			if (level == 1) {
				if (p.rect.left == 3443 && p.rect.top > 29 * ts) {
					managment = true;
					cam = true;
					backgroundIsBlack = false;
					p.rect.left = 92 * ts;
					p.rect.top = 10 * ts;
					offsetX = 88 * ts;
					offsetY = 0;
					sound.pipe.play();
					sound.music.play();
					sound.music_down.stop();
				}

				// возвращение игрока после смерти на определенные кординаты в зависимости от части карты
				if (!p.live && p.life > 0) {
					p.live = true;
					p.scal = true;
					if (!backgroundIsBlack) {
						if (p.rect.left > 21 * ts && p.rect.left < 25 * ts) {
							p.rect.left = ts;
							p.rect.top = 12 * ts;
							offsetX = 0;
						}
						if (p.rect.left >= 26 * ts && p.rect.left <= 78 * ts) {
							p.rect.left = 28 * ts;
							p.rect.top = 6 * ts;
						}
						if (p.rect.left >= 79 * ts && p.rect.left <= 127 * ts) {
							p.rect.left = 73 * ts;
							p.rect.top = 8 * ts;
						}
						if (p.rect.left > 128 * ts && p.rect.left < 132 * ts) {
							p.rect.left = 128 * ts;
							p.rect.top = 8 * ts;
						}
						if (p.rect.left >= 128 * ts && p.rect.left < 167 * ts) {
							p.rect.left = 132 * ts;
							p.rect.top = 8 * ts;
						}
					}
					else {
						if (p.rect.left >= 87 * ts && p.rect.left <= 108 * ts) {
							p.rect.left = 90 * ts;
							p.rect.top = 29 * ts;
						}
					}
				}
				else if (p.life == 0) {
					sound.gameOver.play();
					menu.die = true;
				}
			}

			if (!menu.die && !menu.pause) {
				p.update(time);
				// пропасть (участок без земли)
				if ((p.rect.left > 21 * ts && p.rect.left < 25 * ts && p.rect.top >= 14 * ts)
					|| (p.rect.left > 128 * ts && p.rect.left < 132 * ts && p.rect.top >= 16 * ts)) {
					--p.life;
					p.live = false;
					p.scal = false;
					sound.damage.play();
				}

				for (int i = 0; i < count; ++i) {
					if (p.rect.intersects(enemies[i].rect) && p.live) {
						if (p.dy > 0 && enemies[i].typeOfEnemy < 3) {
							if (enemies[i].typeOfEnemy == 1) {
								enemies[i].go = false;
							}
							else if (enemies[i].typeOfEnemy == 2) {
								enemies[i].run++;
							}
							if (enemies[i].run == 3) {
								enemies[i].dx *= 5;
							}
							if (enemies[i].run == 5) {
								enemies[i].run = 3;
							}
							if (enemies[i].live) {
								p.score += 200;
								enemies[i].live = false;
								sound.kill.play();
							}
							if ((enemies[i].typeOfEnemy == 1 && enemies[i].live) || enemies[i].typeOfEnemy == 2) {
								p.dy = -0.2;
							}
						}
						else if ((enemies[i].live || (enemies[i].run == 3 && enemies[i].typeOfEnemy == 2)) && p.onGround) {
							--p.life;
							p.scal = false;
							p.live = false;
							p.dy = -0.2;
							sound.damage.play();
						}
					}
				}


				for (int i = 0; i < count - 2; ++i) {
					for (int j = count - 2; j < count; ++j) {
						if (enemies[i].rect.left < enemies[j].rect.left && enemies[i].rect.left + 32 > enemies[j].rect.left && enemies[i].live
							&& enemies[j].run == 3 && enemies[i].rect.top > enemies[j].rect.top - 14 && enemies[i].rect.top < enemies[j].rect.top + 32) {
							enemies[i].live = false;
							p.score += 100;
						}
					}
				}

				for (int i = 0; i < count; ++i) {
					enemies[i].update(time);
				}
			}

			window.setView(view);
			if (!backgroundIsBlack) {
				window.clear(sf::Color::Color(8, 200, 254));
			}
			else {
				window.clear(sf::Color::Black);
			}

			for (int i = 0; i < MAP_HEIGHT; ++i) {
				for (int j = 0; j < MAP_WIDTH; ++j) {
					if (TileMap[i][j] == ' ' || TileMap[i][j] == '6' || TileMap[i][j] == '1' || TileMap[i][j] == '0') {
						continue;
					}
					if (TileMap[i][j] == 'g') {
						map.setTextureRect(sf::IntRect(0, 0, ts, ts));
					}
					if (TileMap[i][j] == 'e') {
						map.setTextureRect(sf::IntRect(416, 0, ts, ts));
					}
					if (TileMap[i][j] == 'b') {
						map.setTextureRect(sf::IntRect(64, 0, ts, ts));
					}
					if (TileMap[i][j] == 'q') {
						map.setTextureRect(sf::IntRect(32, 0, ts, ts));
					}
					if (TileMap[i][j] == 'k') {
						map.setTextureRect(sf::IntRect(0, 32, ts, ts));
					}
					if (TileMap[i][j] == 'l') {
						map.setTextureRect(sf::IntRect(32, 32, ts, ts));
					}
					if (TileMap[i][j] == 'm') {
						map.setTextureRect(sf::IntRect(0, 64, ts, ts));
					}
					if (TileMap[i][j] == 'n') {
						map.setTextureRect(sf::IntRect(32, 64, ts, ts));
					}
					if (TileMap[i][j] == 't') {
						map.setTextureRect(sf::IntRect(827, 0, ts * 3, ts * 3));
					}
					if (TileMap[i][j] == 'x') {
						map.setTextureRect(sf::IntRect(914, 0, ts * 3, ts * 3));
					}
					if (TileMap[i][j] == 'u') {
						map.setTextureRect(sf::IntRect(96, 0, ts, ts));
					}
					if (TileMap[i][j] == 'w') {
						map.setTextureRect(sf::IntRect(416, 0, ts, ts));
					}
					if (TileMap[i][j] == 'c') {
						map.setTextureRect(sf::IntRect(160, 0, ts, ts));
					}
					if (TileMap[i][j] == 'z') {
						map.setTextureRect(sf::IntRect(128, 0, ts, ts));
					}
					if (TileMap[i][j] == 'v') {
						map.setTextureRect(sf::IntRect(192, 0, ts, ts));
					}
					if (TileMap[i][j] == 'f') {
						map.setTextureRect(sf::IntRect(96, 288, ts * 3, ts * 3));
					}
					if (TileMap[i][j] == 'h') {
						map.setTextureRect(sf::IntRect(224, 32, ts * 5, ts * 5));
					}
					map.setPosition(j * ts - offsetX, i * ts - offsetY);
					window.draw(map);
				}
			}
			for (int i = 0; i < count; ++i) {
				if (enemies[i].draw) { //было draw
					window.draw(enemies[i].sprite);
				}
			}

			window.draw(textManager(p, textScore, SCORE, view));
			window.draw(textManager(p, textLevel, LEVEL, view));
			window.draw(textManager(p, textCoins, COINS, view));
			window.draw(textManager(p, textLife, LIFE, view));

			if (p.draw) {
				window.draw(p.sprite);
			}
		}

		if (!menu.play) {
			window.draw(menu.screen);
		}

		if (menu.die) {
			window.draw(menu.restart);
			window.draw(menu.end);
			window.draw(menu.back_to_menu);
		}

		if (menu.win) {
			window.draw(menu.restart);
			window.draw(menu.s_win);
			window.draw(menu.back_to_menu);
		}

		if (menu.pause) {
			window.draw(menu.s_pause);
			window.draw(menu.restart);
			window.draw(menu.s_continue);
			window.draw(menu.back_to_menu);
		}
		if (menu.menu) {
			window.draw(menu.title);
			window.draw(menu.exit);
			window.draw(menu.start);
			window.draw(menu.s_control);
		}
		else if (menu.control) {
			window.draw(menu.s_control);
			window.draw(menu.control_1);
			window.draw(menu.control_2);
			window.draw(menu.control_3);
			window.draw(menu.control_4);
			window.draw(menu.back);
		}
		window.display();
	}

	return 0;
}