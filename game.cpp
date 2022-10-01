#include "global.h"
#include "menu.h"
#include "player.h"
#include "sound.h"
#include "enemy.h"


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
	Sound sound;

	enemies[0].set(mushroom, ts * 28, ts * 13, MUSHROOM);
	enemies[1].set(mushroom, ts * 44, ts * 13, MUSHROOM);
	enemies[2].set(mushroom, ts * 75, ts * 13, MUSHROOM);
	enemies[3].set(mushroom, ts * 86, ts * 13, MUSHROOM);
	enemies[4].set(mushroom, ts * 106, ts * 13, MUSHROOM);
	enemies[5].set(mushroom, ts * 115, ts * 13, MUSHROOM);
	enemies[6].set(mushroom, ts * 122, ts * 13, MUSHROOM);
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
						menu.play = true;
						menu.pause = false;
						sound.button.play();
					}
					if (menu.back_to_menu.getGlobalBounds().contains(position.x, position.y)) {
						menu.run = false;
						menu.play = false;
						menu.menu = true;
						menu.pause = false;
						menu.die = false;
						menu.win = false;
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
			enemies[6].set(mushroom, ts * 122, ts * 13, MUSHROOM);
			enemies[7].set(mushroom, ts * 154, ts * 13, MUSHROOM);
			enemies[8].set(mushroom, ts * 160, ts * 13, MUSHROOM);
			enemies[9].set(mushroom, ts * 138, ts * 13, MUSHROOM);
			enemies[10].set(mushroom, ts * 150, ts * 13, MUSHROOM);
			enemies[11].set(mushroom, ts * 70, ts * 13, MUSHROOM);
			enemies[12].set(turtle, ts * 31, ts * 13, TURTLE);
			enemies[13].set(turtle, ts * 154, ts * 13, TURTLE);
			enemies[14].set(mushroom, ts * 102, ts * 30, MUSHROOM);
			for (int i = 0; i < count; ++i) {
				enemies[i].setGo(true);
				enemies[i].setLive(true);
				enemies[i].setDraw(true);
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

				p.setLive(true);
				p.setScal(true);

				managment = true;

				win = false;
				finish = false;
				cam = true;
			}

			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time = time / 800;

			if (!_kbhit()) { //если нет нажатия на клавиши, подгружается спрайт обычный стойки в зависимости от последней нажатой клавиши(влево или вправо), за это и отвечает перменная right
				if (p.is_onGround()) {
					if (p.is_right()) {
						p.sprite.setTextureRect(sf::IntRect(19, 0, 15, 15));

					}
					else {
						p.sprite.setTextureRect(sf::IntRect(19 + 15, 0, -15, 15));
					}
				}
			}


			if (managment && p.is_live()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					p.setDx(-0.1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					p.setDx(0.1);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					if (p.is_onGround()) {
						p.setDy(-0.4);
						p.setonGround(false);
						if (p.is_right()) {
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
					p.setScal(true);
					managment = true;
					p.setDraw(true);
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
						&& p.rect.top < 15 * ts && p.is_scal()) {
						p.setScal(false);   //отключаем все во время падения
						managment = false;
						p.setDraw(false);
						sound.pipe.play();
						sound.music.stop();
						sound.music_down.play();
					}
				}
				if (p.rect.left > 197 * ts) {
					p.setDx(0.2);
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
				if (!p.is_live() && p.getLife() > 0) {
					p.setLive(true);
					p.setScal(true);
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
				else if (p.getLife() == 0) {
					sound.gameOver.play();
					menu.die = true;
				}
			}

			if (!menu.die && !menu.pause) {
				p.update(time);
				// пропасть (участок без земли)
				if ((p.rect.left > 21 * ts && p.rect.left < 25 * ts && p.rect.top >= 14 * ts)
					|| (p.rect.left > 128 * ts && p.rect.left < 132 * ts && p.rect.top >= 16 * ts)) {
					p.minusLife();
					p.setLive(false);
					p.setScal(false);
					sound.damage.play();
				}

				for (int i = 0; i < count; ++i) {
					if (p.rect.intersects(enemies[i].rect) && p.is_live()) {
						if (p.getDy() > 0 && enemies[i].getType() < 3) {
							if (enemies[i].getType() == 1) {
								enemies[i].setGo(false);
							}
							else if (enemies[i].getType() == 2) {
								enemies[i].plusRun();
							}
							if (enemies[i].getRun() == 3) {
								int dx = enemies[i].getDx() * 5;
								enemies[i].setDx(dx);
							}
							if (enemies[i].getRun() == 5) {
								enemies[i].setRun(3);
							}
							if (enemies[i].is_live()) {
								p.plusScore(200);
								enemies[i].setLive(false);
								sound.kill.play();
							}
							if ((enemies[i].getType() == 1 && enemies[i].is_live()) || enemies[i].getType() == 2) {
								p.setDy(-0.2);
							}
						}
						else if ((enemies[i].is_live() || (enemies[i].getRun() == 3 && enemies[i].getType() == 2)) && p.is_onGround()) {
							p.prevX = p.rect.left;
							p.prevY = p.rect.top;
							p.prevOffset = offsetX;
							p.minusLife();
							p.setScal(false);
							p.setLive(false);
							p.setDy(-0.2);
							sound.damage.play();
						}
					}
				}


				for (int i = 0; i < count - 2; ++i) {
					for (int j = count - 2; j < count; ++j) {
						if (enemies[i].rect.left < enemies[j].rect.left && enemies[i].rect.left + 32 > enemies[j].rect.left && enemies[i].is_live()
							&& enemies[j].getRun() == 3 && enemies[i].rect.top > enemies[j].rect.top - 14 && enemies[i].rect.top < enemies[j].rect.top + 32) {
							enemies[i].setLive(false);
							p.plusScore(100);
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
					//части трубы (4шт)
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
				if (enemies[i].is_draw()) { 
					window.draw(enemies[i].sprite);
				}
			}

			window.draw(textManager(p.getScore(), textScore, SCORE, view));
			window.draw(textManager(p.getLevel(), textLevel, LEVEL, view));
			window.draw(textManager(p.getCoins(), textCoins, COINS, view));
			window.draw(textManager(p.getLife(), textLife, LIFE, view));

			if (p.is_draw()) {
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


