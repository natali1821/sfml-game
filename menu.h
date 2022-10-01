#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
	sf::Texture t_exit, t_pause, t_start, t_back, t_back_to_menu, t_end, t_restart, t_screen, t_title;
	sf::Texture t_control, t_control_1, t_control_2, t_control_3, t_control_4, t_continue, t_win;
	sf::Sprite exit, s_pause, start, back, back_to_menu, end, restart, screen, title;
	sf::Sprite s_control, control_1, control_2, control_3, control_4, s_continue, s_win;
	bool menu, game, play, pause, win, die, control, run;
	int px;
	Menu();
};
