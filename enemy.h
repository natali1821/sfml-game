#pragma once
#include "global.h"

class Enemy {
private:
	float dx, dy;
	bool go, live, draw;
	float currentFrame;
	enemy typeOfEnemy;
	int t = 0, run; //run for turtle, t for mushroom
public:
	sf::FloatRect rect;
	sf::Sprite sprite;

	void set(sf::Texture& texture, int x, int y, enemy type);
	void update(float time);
	void Collision();
	void plusRun();

	void setDx(float dx);
	void setDy(float dy);
	void setLive(bool value);
	void setDraw(bool value);
	void setGo(bool value);
	void setRun(int value);

	float getDx();
	float getDy();
	int getRun();
	enum enemy getType();

	bool is_go();
	bool is_live();
	bool is_draw();
};