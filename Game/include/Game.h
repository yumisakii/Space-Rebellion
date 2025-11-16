#pragma once
#include "Image.h"
class Menu;

class Game {
public:
	Game() = default;
	int game();

private:
	int WINDOW_WIDTH = 1920;
	int WINDOW_HEIGHT = 1080;

	Image imageBackground;
};