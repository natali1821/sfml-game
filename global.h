#pragma once
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

enum enemy {
	MUSHROOM = 1,
	TURTLE = 2
};

enum forText {
	SCORE = 1,
	LEVEL = 2,
	COINS = 3,
	LIFE = 4
};

sf::Text textManager(int value, sf::Text text, forText number, sf::View view) {
	std::ostringstream count;
	count << value;
	switch (number) {
	case 1:
		text.setPosition(view.getCenter().x - 11 * ts, view.getCenter().y - 8 * ts);
		text.setString("score : " + count.str());
		break;
	case 2:
		text.setPosition(view.getCenter().x - 4 * ts, view.getCenter().y - 8 * ts);
		text.setString("level : " + count.str());
		break;
	case 3:
		text.setPosition(view.getCenter().x + 2 * ts, view.getCenter().y - 8 * ts);
		text.setString("coins : " + count.str());
		break;
	case 4:
		text.setPosition(view.getCenter().x + 8 * ts, view.getCenter().y - 8 * ts);
		text.setString("life : " + count.str());
		break;
	}
	text.setCharacterSize(45);
	return text;
};


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