#pragma once
#include "input.h"
#include "Audio.h"
#include "Image.h"

extern bool restart_game;
extern bool game_over;
extern bool victory;

class Menu {
public:

	static Menu& getInstance() {
		static Menu instance;
		return instance;
	}

	Menu() = default;
	
	// ----- Fonction pour load la font -----
	bool LoadFont();
	void reset();
	void DrawText(sf::RenderWindow& window, const std::string& text, int fontSize, float x, float y, sf::Color color);

	void setVictory(bool value) {
		victory = value;
	}

	void setGameOver(bool value) {
		game_over = value;
	}

	// ----- Fonction pour load les images -----
	void loadResourcesBackground();
	void loadResources();

	// ----- Fonctions pour créer les boutons -----
	void initializeButtonsTitle(const sf::RenderWindow& window);
	void initializeButtonsOptions(const sf::RenderWindow& window);
	void initializeButtonsPause(const sf::RenderWindow& window);
	void initializeButtonsGameOver(const sf::RenderWindow& window);
	void initializeButtonsVictory(const sf::RenderWindow& window);
	void initializeButtonsCredit(const sf::RenderWindow& window);

	// ----- Fonctions pour créer les menus -----
	void startMenu(sf::RenderWindow& window);
	void optionsMenu(sf::RenderWindow& window);
	void PauseMenu(sf::RenderWindow& window);
	void gameOverMenu(sf::RenderWindow& window);
	void VictoryMenu(sf::RenderWindow& window);
	void creditMenu(sf::RenderWindow& window);

	void goToPause();
	void differentsMenus(sf::RenderWindow& window);

	bool getPause();

	Image imageCharacter;

private:

	sf::Font font;
	sf::Vector2i mousePos;

	sf::RectangleShape buttonPlay;
	sf::RectangleShape buttonOption;
	sf::RectangleShape buttonQuit;
	sf::RectangleShape buttonBack;
	sf::RectangleShape buttonContinue;
	sf::RectangleShape buttonRestart;
	sf::RectangleShape buttonCredit;

	bool pause = true;
	bool start_menu = true;
	bool option_menu = false;
	bool pause_menu = false;
	bool credits = false;
	bool since_pause_menu = false;
	bool since_start_menu = false;
	bool alwaysClick = false;
	bool resourcesLoaded = false;

	InputManager inputManager;
	Audio& audio = Audio::getInstance();
	Image imageCadre;
	Image imageFond;
	Image imageTitle;
	Image imagePlay;
	Image imageOptions;
	Image imageExit;
	Image imageMusic;
	Image imageBack;
	Image imagePause;
	Image imageContinue;
	Image imageGameOver;
	Image imageRestart;
	Image imageVictory;
	Image imageCredit;
	Image imageArtDevelopment;
	Image imageDevelopmentDepartment;
	Image imageArt;
	Image imageDev;
};