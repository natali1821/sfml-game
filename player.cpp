#include "player.h"

Player::Player(sf::Texture& image) {
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
	onGround = true;
}

void Player::restart() {
	countCoins = 0;
	life = 3;
	score = 0;
	rect.left = 0;
	rect.top = 243;
	offsetX = 0;
	offsetY = 0;
	right = true;
}

void Player::update(float time) {
	rect.left += 1.3 * dx * time;
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

void Player::Collision(float dir) {
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
					/*if (TileMap[i][j] == 'b') {
						TileMap[i][j] = '1';
					}*/
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

void Player::setDx(float dx) {
	this->dx = dx;
}

void Player::setDy(float dy) {
	this->dy = dy;
}

void Player::setLive(bool value) {
	this->live = value;
}

void Player::setDraw(bool value) {
	this->draw = value;
}

void Player::setScal(bool value) {
	this->scal = value;
}

void Player::setonGround(bool value) {
	this->onGround = value;
}

void Player::minusLife() {
	--this->life;
}

void Player::plusScore(int value) {
	score += value;
}

int Player::getLife() {
	return this->life;
}

int Player::getScore() {
	return this->score;
}

int Player::getCoins() {
	return this->countCoins;
}

int Player::getLevel() {
	return this->level;
}

float Player::getDx() {
	return this->dx;
}

float Player::getDy() {
	return this->dy;
}

bool Player::is_onGround() {
	return this->onGround;
}

bool Player::is_right() {
	return this->right;
}

bool Player::is_scal() {
	return this->scal;
}

bool Player::is_live() {
	return this->live;
}

bool Player::is_draw() {
	return this->draw;
}

