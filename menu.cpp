#include "menu.h"

Menu::Menu() {
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