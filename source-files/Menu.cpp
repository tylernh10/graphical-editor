#include "header-files/Menu.h"

void Menu::initBackrgound(ALLEGRO_BITMAP* bg) {
	background = bg;
}

void Menu::draw() {
	al_draw_bitmap(background, 0, 0, 0);
}
