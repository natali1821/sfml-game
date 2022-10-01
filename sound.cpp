#include "sound.h"

void Sound::setSound() {
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