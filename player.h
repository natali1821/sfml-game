#pragma once
#include "global.h"
#include "sound.h"

class Player {
private:
	float dx, dy;
	bool onGround;
	bool right;
	bool scal;
	bool live;
	bool draw;
	int countCoins = 0;
	int life = 3;
	int score = 0;
	int level = 1;
	float currentFrame;
	Sound sound;
public:
	sf::FloatRect rect;
	sf::Sprite sprite;
	int prevX = 0, prevY = 0, prevOffset = 0;

	Player(sf::Texture& image);
	void restart();
	void update(float time);
	void Collision(float dir);

	void setDx(float dx);
	void setDy(float dy);
	void setLive(bool value);
	void setDraw(bool value);
	void setScal(bool value);
	void setonGround(bool value);
	void minusLife();
	void plusScore(int value);

	int getLife();
	int getScore();
	int getCoins();
	int getLevel();
	float getDx();
	float getDy();

	bool is_onGround();
	bool is_right();
	bool is_scal();
	bool is_live();
	bool is_draw();
};