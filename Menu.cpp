#include "header-files/Menu.h"

Menu::Menu(EditModeMouseFunction& e, InsertModeMouseFunction& i) : editModeMouseFunction(e), insertModeMouseFunction(i) {
	for (int i = 0; i < 20; i++) {
		currentHover.push_back(false);
	}
}

Menu::~Menu() {
	al_destroy_bitmap(divider);
	al_destroy_bitmap(background);
	al_destroy_font(font);
	for (auto i : buttons) {
		al_destroy_bitmap(i);
	}
	for (auto i : hoverButtons) {
		al_destroy_bitmap(i);
	}
	for (auto i : colorButtons) {
		al_destroy_bitmap(i);
	}
	for (auto i : colorHoverButtons) {
		al_destroy_bitmap(i);
	}
}

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

void Menu::timer(int mode) {
	if (!mode) {
		editModeMouseFunction.timer();
	}
	else if (mode == 1) {
		insertModeMouseFunction.timer();
	}
	
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
			currentHover.at(i) = true;
		}
		else {
			currentHover.at(i) = false;
		}
	}
	for (unsigned int i = 0; i < 4; i++) {
		if (py < 37 && py > 0 && px >= 10 * 75 + 37 * i && px < 10 * 75 + 37 * (i + 1)) {
			al_draw_bitmap(colorHoverButtons.at(i), 10 * 75 + 37 * i, 0, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[i+10]);
			currentHover.at(i + 10) = true;
		}
		else {
			currentHover.at(i + 10) = false;
		}
	}
	for (unsigned int i = 4; i < 8; i++) {
		if (py < 75 && py > 37 && px >= 10 * 75 + 37 * (i - 4) && px < 10 * 75 + 37 * (i - 4 + 1)) {
			al_draw_bitmap(colorHoverButtons.at(i), 10 * 75 + 37 * (i - 4), 38, 0);
			al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[i-4+14]);
			currentHover.at(i + 10) = true;
		}
		else {
			currentHover.at(i + 10) = false;
		}
	}

	if (py > 14 && py < 69 && px >= 900 && px < 950) {
		al_draw_bitmap(hoverButtons.at(10), 900, 14, 0);
		al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[18]);
		currentHover.at(18) = true;
	}
	else {
		currentHover.at(18) = false;
	}
	if (py > 14 && py < 69 && px >= 950 && px < 1000) {
		al_draw_bitmap(hoverButtons.at(11), 950, 14, 0);
		al_draw_text(font, al_map_rgb(0, 0, 0), 3, 80, ALLEGRO_ALIGN_LEFT, hoverStrings[19]);
		currentHover.at(19) = true;
	}
	else {
		currentHover.at(19) = false;
	}
}

bool Menu::checkOverButton(int x) {
	return currentHover.at(x);
}
