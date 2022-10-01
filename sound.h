#pragma once
#include <SFML/Audio.hpp>

class Sound {
public:
	sf::SoundBuffer s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;
	sf::Sound win, pipe, pause, kill, jump, gameOver, destroyBlock, damage, button, bonus;
	sf::Music music, music_down;
	void setSound();
};
