#include "header-files/Menu.h"

void Menu::initDivider(ALLEGRO_BITMAP* div) {
	divider = div;
}

void Menu::initBackground(ALLEGRO_BITMAP* bg) {
	background = bg;
}

void Menu::initButtons(vector<ALLEGRO_BITMAP*> bts) {
	buttons = bts;
}

void Menu::initHoverButtons(vector<ALLEGRO_BITMAP*> bts) {
	hoverButtons = bts;
}

void Menu::initColorButtons(vector<ALLEGRO_BITMAP*> bts) {
	colorButtons = bts;
}

void Menu::initColorHoverButtons(vector<ALLEGRO_BITMAP*> bts) {
	colorHoverButtons = bts;
}

void Menu::initFont(ALLEGRO_FONT* f) {
	font = f;
}

void Menu::draw() {
	// draw background
	al_draw_bitmap(background, 0, 0, 0);
	
	// draw both dividers
	al_draw_bitmap(divider, 0, 75, 0);
	al_draw_bitmap(divider, 0, 103, 0);
	
	// draw buttons before color buttons
	// first 10 buttons follow this sizing scheme
	for (unsigned int i = 0; i < 10; i++) {
		al_draw_bitmap(buttons.at(i), i*75, 0, 0);
	}

	// draw color buttons
	for (unsigned int i = 0; i < 4; i++) {
		al_draw_bitmap(colorButtons.at(i), 10*75 + 37*i, 0, 0);
	}
	for (unsigned int i = 4; i < 8; i++) {
		al_draw_bitmap(colorButtons.at(i), 10*75 + 37*(i-4), 38, 0);
	}
	// draw save button
	al_draw_bitmap(buttons.at(10), 900, 14, 0);
	
	// draw help button
	al_draw_bitmap(buttons.at(11), 950, 14, 0);
}

void Menu::detectMouse(int px, int py) {
	// first 10 buttons follow this sizing scheme
	for (unsigned int i = 0; i < 10; i++) {
		if (py < 75 && py > 0 && px >= i*75 && px < (i+1)*75) {
			al_draw_bitmap(hoverButtons[i], i*75, 0, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[i]);
		}
	}
	for (unsigned int i = 0; i < 4; i++) {
		if (py < 37 && py > 0 && px >= 10 * 75 + 37 * i && px < 10 * 75 + 37 * (i + 1)) {
			al_draw_bitmap(colorHoverButtons.at(i), 10 * 75 + 37 * i, 0, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[i+10]);
		}
	}
	for (unsigned int i = 4; i < 8; i++) {
		if (py < 75 && py > 37 && px >= 10 * 75 + 37 * (i - 4) && px < 10 * 75 + 37 * (i - 4 + 1)) {
			al_draw_bitmap(colorHoverButtons.at(i), 10 * 75 + 37 * (i - 4), 38, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[i-4+14]);
		}
	}

	if (py > 14 && py < 69 && px >= 900 && px < 950) {
		al_draw_bitmap(hoverButtons.at(10), 900, 14, 0);
		al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[18]);
	}
	if (py > 14 && py < 69 && px >= 950 && px < 1000) {
		al_draw_bitmap(hoverButtons.at(11), 950, 14, 0);
		al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[19]);
	}
}
