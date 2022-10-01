#include "enemy.h"

void Enemy::set(sf::Texture& texture, int x, int y, enemy type) {
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

void Enemy::update(float time) {
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

void Enemy::Collision() {
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
}

void Enemy::plusRun() {
	this->run++;
}

void Enemy::setDx(float dx) {
	this->dx = dx;
}

void Enemy::setDy(float dy) {
	this->dy = dy;
}

void Enemy::setLive(bool value) {
	this->live = value;
}

void Enemy::setDraw(bool value) {
	this->draw = value;
}

void Enemy::setGo(bool value) {
	this->go = value;
}

void Enemy::setRun(int value) {
	this->run = value;
}

float Enemy::getDx() {
	return this->dx;
}

float Enemy::getDy() {
	return this->dy;
}

int Enemy::getRun() {
	return this->run;
}

enum enemy Enemy::getType() {
	return this->typeOfEnemy;
}

bool Enemy::is_live() {
	return this->live;
}

bool Enemy::is_draw() {
	return this->draw;
}

bool Enemy::is_go() {
	return this->go;
}