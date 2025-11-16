#include "Game.h"
#include "Menu.h"
#include "Audio.h"
#include "playerEntity.h"

bool restart_game = false;
bool game_over = false;
bool victory = false;

// ----- Fonction pour load la font -----
bool Menu::LoadFont() {
    if (!font.loadFromFile("Assets/Fonts/SourGummy-LightItalic.ttf")) {
        std::cerr << "Erreur de chargement de la police ! " << std::endl;
        return false;
    }
    return true;
}

// ----- Fonction pour afficher la font -----
void Menu::DrawText(sf::RenderWindow& window, const std::string& text, int fontSize, float x, float y, sf::Color color) {
    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(color);
    sfText.setPosition(x, y);
    window.draw(sfText);
}

// ----- Fonction pour load le background -----
void Menu::loadResourcesBackground() {

    if (!imageFond.loadImage("Assets/UI_UX/fond.png")) {
        std::cerr << "Impossible de charger l'image de fond de menu." << std::endl;
    }

    if (!imageCadre.loadImage("Assets/UI_UX/encadré.png")) {
        std::cerr << "Impossible de charger l'image de l'encadré du menu." << std::endl;
    }

}

// ----- Fonction pour load une seule fois toutes les images -----
void Menu::loadResources() {
    if (resourcesLoaded) return;

    loadResourcesBackground();

    if (!imageTitle.loadImage("Assets/UI_UX/titre.png")) {
        std::cerr << "Impossible de charger l'image du titre du jeu." << std::endl;
    }

    if (!imagePlay.loadImage("Assets/UI_UX/play.png")) {
        std::cerr << "Impossible de charger l'image du bouton play." << std::endl;
    }

    if (!imageOptions.loadImage("Assets/UI_UX/options.png")) {
        std::cerr << "Impossible de charger l'image du bouton options." << std::endl;
    }

    if (!imageExit.loadImage("Assets/UI_UX/exit.png")) {
        std::cerr << "Impossible de charger l'image du bouton exit." << std::endl;
    }

    if (!imageMusic.loadImage("Assets/UI_UX/music volume.png")) {
        std::cerr << "Impossible de charger l'image du volume de son." << std::endl;
    }
    
    if (!imageBack.loadImage("Assets/UI_UX/Back.png")) {
        std::cerr << "Impossible de charger l'image de back." << std::endl;
    }
    
    if (!imagePause.loadImage("Assets/UI_UX/Pause.png")) {
        std::cerr << "Impossible de charger l'image du volume de son." << std::endl;
    }
    
    if (!imageContinue.loadImage("Assets/UI_UX/continue.png")) {
        std::cerr << "Impossible de charger l'image de back." << std::endl;
    }
    
    if (!imageGameOver.loadImage("Assets/UI_UX/Game over.png")) {
        std::cerr << "Impossible de charger l'image du game over." << std::endl;
    }
    
    if (!imageRestart.loadImage("Assets/UI_UX/restart.png")) {
        std::cerr << "Impossible de charger l'image de restart." << std::endl;
    }
    
    if (!imageVictory.loadImage("Assets/UI_UX/Victory.png")) {
        std::cerr << "Impossible de charger l'image de victoire." << std::endl;
    }
    
    if (!imageCredit.loadImage("Assets/UI_UX/crédits.png")) {
        std::cerr << "Impossible de charger l'image de victoire." << std::endl;
    }
    
    if (!imageArtDevelopment.loadImage("Assets/UI_UX/Art Development.png")) {
        std::cerr << "Impossible de charger l'image d'art development." << std::endl;
    }
    
    if (!imageDevelopmentDepartment.loadImage("Assets/UI_UX/Development department.png")) {
        std::cerr << "Impossible de charger l'image du development department." << std::endl;
    }
    
    if (!imageArt.loadImage("Assets/UI_UX/personnes art.png")) {
        std::cerr << "Impossible de charger l'image des personnes en Art." << std::endl;
    }
    
    if (!imageDev.loadImage("Assets/UI_UX/personnes dev.png")) {
        std::cerr << "Impossible de charger l'image des personnes en Dev." << std::endl;
    }

    resourcesLoaded = true; // Marque les ressources comme chargées
}

// ----- Toutes les fonctions pour créer chaque bouton des menus -----
void Menu::initializeButtonsTitle(const sf::RenderWindow& window) {
    buttonPlay.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonPlay.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 2.5));
    buttonPlay.setOutlineThickness(5);
    buttonPlay.setFillColor(sf::Color::Transparent);

    buttonOption.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonOption.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.7));
    buttonOption.setOutlineThickness(5);
    buttonOption.setFillColor(sf::Color::Transparent);

    buttonQuit.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonQuit.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.3));
    buttonQuit.setOutlineThickness(5);
    buttonQuit.setFillColor(sf::Color::Transparent);
}

void Menu::initializeButtonsOptions(const sf::RenderWindow& window) {
    buttonBack.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonBack.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.3));
    buttonBack.setOutlineThickness(5);
    buttonBack.setFillColor(sf::Color::Transparent);
}

void Menu::initializeButtonsPause(const sf::RenderWindow& window) {
    buttonContinue.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonContinue.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 2.5));
    buttonContinue.setOutlineThickness(5);
    buttonContinue.setFillColor(sf::Color::Transparent);

    buttonOption.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonOption.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.7));
    buttonOption.setOutlineThickness(5);
    buttonOption.setFillColor(sf::Color::Transparent);

    buttonQuit.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonQuit.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.3));
    buttonQuit.setOutlineThickness(5);
    buttonQuit.setFillColor(sf::Color::Transparent);
}

void Menu::initializeButtonsGameOver(const sf::RenderWindow& window) {
    buttonRestart.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonRestart.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 2));
    buttonRestart.setOutlineThickness(5);
    buttonRestart.setFillColor(sf::Color::Transparent);

    buttonQuit.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonQuit.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.5));
    buttonQuit.setOutlineThickness(5);
    buttonQuit.setFillColor(sf::Color::Transparent);
}

void Menu::initializeButtonsVictory(const sf::RenderWindow& window) {
    buttonRestart.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonRestart.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 2.5));
    buttonRestart.setOutlineThickness(5);
    buttonRestart.setFillColor(sf::Color::Transparent);

    buttonCredit.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonCredit.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.7));
    buttonCredit.setOutlineThickness(5);
    buttonCredit.setFillColor(sf::Color::Transparent);

    buttonQuit.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonQuit.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.3));
    buttonQuit.setOutlineThickness(5);
    buttonQuit.setFillColor(sf::Color::Transparent);
}

void Menu::initializeButtonsCredit(const sf::RenderWindow& window) {
    buttonBack.setSize(sf::Vector2f(float(window.getSize().x / 5), float(window.getSize().y / 11)));
    buttonBack.setPosition(float(window.getSize().x / 2.5), float(window.getSize().y / 1.2));
    buttonBack.setOutlineThickness(5);
    buttonBack.setFillColor(sf::Color::Transparent);
}

// ----- Menu principal -----
void Menu::startMenu(sf::RenderWindow& window) {

    loadResources();
    mousePos = sf::Mouse::getPosition(window);
    LoadFont();

    window.clear(sf::Color::Black);

    initializeButtonsTitle(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCadre.drawImage(window, window.getSize().x / 1.4, window.getSize().y / 1.5, window.getSize().x / 7.5, window.getSize().y / 4);
    imageTitle.drawImage(window, window.getSize().x / 1.3, window.getSize().y / 9, float(window.getSize().x / 9), float(window.getSize().y / 13));

    // ----- Bouton Play -----
    if (buttonPlay.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonPlay.setOutlineColor(sf::Color::Cyan);

        // Accès au jeu
        if (start_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            pause = false;
            start_menu = false;
            audio.playSound("click_button");
            audio.playSound("backMusic");
        }
    }
    else {
        buttonPlay.setOutlineColor(sf::Color::White);
    }

    imagePlay.drawImage(window, window.getSize().x / 9, window.getSize().x / 28, float(window.getSize().x / 2.25), float(window.getSize().y / 2.4));
    window.draw(buttonPlay);

    // ----- Bouton Options -----
    if (buttonOption.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonOption.setOutlineColor(sf::Color::Cyan);

        // Accès aux options
        if (start_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            audio.playSound("click_button");
            option_menu = true;
            since_start_menu = true;
        }
    }
    else {
        buttonOption.setOutlineColor(sf::Color::White);
    }

    imageOptions.drawImage(window, window.getSize().x / 6, window.getSize().y / 18, float(window.getSize().x / 2.39), float(window.getSize().y / 1.65));
    window.draw(buttonOption);

    // ----- Bouton Quit -----
    if (buttonQuit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonQuit.setOutlineColor(sf::Color::Cyan);

        // Quitter le jeu
        if (start_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            window.close();
        }
    }
    else {
        buttonQuit.setOutlineColor(sf::Color::White);
    }

    imageExit.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.27));
    window.draw(buttonQuit);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }
    
    window.display();
}

// ----- Menu options -----
void Menu::optionsMenu(sf::RenderWindow& window) {

    mousePos = sf::Mouse::getPosition(window);

    window.clear(sf::Color::Black);

    initializeButtonsOptions(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCadre.drawImage(window, window.getSize().x / 1.4, window.getSize().y / 1.5, window.getSize().x / 7.5, window.getSize().y / 4);
    imageOptions.drawImage(window, window.getSize().x / 3.5, window.getSize().y / 12, float(window.getSize().x / 2.9), float(window.getSize().y / 13));

    // ----- Gestion du volume global -----
    imageMusic.drawImage(window, window.getSize().x / 3, window.getSize().x / 25, float(window.getSize().x / 5.5), float(window.getSize().y / 1.9));

    // Création du slider
    float sliderWidth = window.getSize().x / 3.5;
    float sliderHeight = window.getSize().y / 25;
    float sliderX = (window.getSize().x / 1.47) - (sliderWidth / 2);
    float sliderY = window.getSize().y / 1.84;

    static VolumeSlider volumeSlider(sliderX, sliderY, sliderWidth, sliderHeight);

    // Gestion du slider
    volumeSlider.handleInput(window);
    volumeSlider.update();
    volumeSlider.draw(window);

    // ----- Bouton Back -----
    if (option_menu && since_start_menu && InputManager::instance()->handleInputKeyboard(sf::Keyboard::Escape) && !alwaysClick) {
        alwaysClick = true;
        start_menu = true;
        option_menu = false;
        since_start_menu = false;
    }
    if (option_menu && since_pause_menu && InputManager::instance()->handleInputKeyboard(sf::Keyboard::Escape) && !alwaysClick) {
        alwaysClick = true;
        pause_menu = true;
        option_menu = false;
        since_pause_menu = false;
    }

    if (buttonBack.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonBack.setOutlineColor(sf::Color::Cyan);

        // Accès au menu principal
        if (option_menu && since_start_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            start_menu = true;
            option_menu = false;
            since_start_menu = false;
            audio.playSound("click_button");
        }

        // Accès au menu de pause
        if (option_menu && since_pause_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            pause_menu = true;
            option_menu = false;
            since_pause_menu = false;
            audio.playSound("click_button");
        }
    }
    else {
        buttonBack.setOutlineColor(sf::Color::White);
    }

    imageBack.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.27));
    window.draw(buttonBack);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }

    window.display();
}

// ----- Menu pause -----
void Menu::PauseMenu(sf::RenderWindow& window) {

    mousePos = sf::Mouse::getPosition(window);

    window.clear(sf::Color::Black);

    initializeButtonsPause(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCadre.drawImage(window, window.getSize().x / 1.4, window.getSize().y / 1.5, window.getSize().x / 7.5, window.getSize().y / 4);
    imagePause.drawImage(window, window.getSize().x / 4, window.getSize().y / 11, float(window.getSize().x / 2.75), float(window.getSize().y / 13));

    // ----- Bouton Continue -----
    if (buttonContinue.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonContinue.setOutlineColor(sf::Color::Cyan);

        // Retour sur le jeu
        if (pause_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
            pause = false;
            pause_menu = false;
            audio.playSound("click_button");
            audio.resumeAllSounds();
        }
    }
    else {
        buttonContinue.setOutlineColor(sf::Color::White);
    }

    imageContinue.drawImage(window, window.getSize().x / 6, window.getSize().x / 28, float(window.getSize().x / 2.4), float(window.getSize().y / 2.4));
    window.draw(buttonContinue);

    // ----- Bouton Options -----
    if (buttonOption.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonOption.setOutlineColor(sf::Color::Cyan);

        // Accès aux options
        if (pause_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
            option_menu = true;
            since_pause_menu = true;
            audio.playSound("click_button");
        }
    }
    else {
        buttonOption.setOutlineColor(sf::Color::White);
    }

    imageOptions.drawImage(window, window.getSize().x / 6, window.getSize().y / 18, float(window.getSize().x / 2.39), float(window.getSize().y / 1.65));
    window.draw(buttonOption);

    // ----- Bouton Quit -----
    if (buttonQuit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonQuit.setOutlineColor(sf::Color::Cyan);

        // Quitter le jeu
        if (pause_menu && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            window.close();
        }
    }
    else {
        buttonQuit.setOutlineColor(sf::Color::White);
    }

    imageExit.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.27));
    window.draw(buttonQuit);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }

    window.display();

}

// ----- Menu game over -----
void Menu::gameOverMenu(sf::RenderWindow& window) {

    mousePos = sf::Mouse::getPosition(window);

    window.clear(sf::Color::Black);

    initializeButtonsGameOver(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCadre.drawImage(window, window.getSize().x / 1.4, window.getSize().y / 1.5, window.getSize().x / 7.5, window.getSize().y / 4);
    imageGameOver.drawImage(window, window.getSize().x / 3, window.getSize().y / 11, float(window.getSize().x / 3.1), float(window.getSize().y / 13));

    // ----- Bouton Restart -----
    if (buttonRestart.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonRestart.setOutlineColor(sf::Color::Cyan);

        // Restart du jeu
        if (game_over && InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
            audio.playSound("click_button");
            restart_game = true;
        }
    }
    else {
        buttonRestart.setOutlineColor(sf::Color::White);
    }

    imageRestart.drawImage(window, window.getSize().x / 6, window.getSize().x / 28, float(window.getSize().x / 2.4), float(window.getSize().y / 1.95));
    window.draw(buttonRestart);

    // ----- Bouton Quit -----
    if (buttonQuit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonQuit.setOutlineColor(sf::Color::Cyan);

        // Quitter le jeu
        if (game_over && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            window.close();
        }
    }
    else {
        buttonQuit.setOutlineColor(sf::Color::White);
    }

    imageExit.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.47));
    window.draw(buttonQuit);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }

    window.display();

}

// ----- Menu victoire -----
void Menu::VictoryMenu(sf::RenderWindow& window) {

    mousePos = sf::Mouse::getPosition(window);

    window.clear(sf::Color::Black);

    initializeButtonsVictory(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCadre.drawImage(window, window.getSize().x / 1.4, window.getSize().y / 1.5, window.getSize().x / 7.5, window.getSize().y / 4);
    imageVictory.drawImage(window, window.getSize().x / 3, window.getSize().y / 11, float(window.getSize().x / 3), float(window.getSize().y / 13));

    //----- Affichage du score -----
    auto player = Player::getInstance();
    std::string displayScore = "Score : ";
    displayScore += std::to_string(player->getScore());
    player->drawTextOnTheScren(window, displayScore, 45, (window.getSize().x / 2) -150 , 310);



    // ----- Bouton Restart -----
    if (buttonRestart.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonRestart.setOutlineColor(sf::Color::Cyan);

        // Restart du jeu
        if (victory && InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
            audio.playSound("click_button");
            restart_game = true;
        }
    }
    else {
        buttonRestart.setOutlineColor(sf::Color::White);
    }

    imageRestart.drawImage(window, window.getSize().x / 6, window.getSize().x / 28, float(window.getSize().x / 2.4), float(window.getSize().y / 2.4));
    window.draw(buttonRestart);

    // ----- Bouton Crédits -----
    if (buttonCredit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonCredit.setOutlineColor(sf::Color::Cyan);

        // Accès aux crédits
        if (victory && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            audio.playSound("click_button");
            alwaysClick = true;
            victory = false;
            credits = true;
        }
    }
    else {
        buttonCredit.setOutlineColor(sf::Color::White);
    }

    imageCredit.drawImage(window, window.getSize().x / 6, window.getSize().y / 18, float(window.getSize().x / 2.39), float(window.getSize().y / 1.65));
    window.draw(buttonCredit);

    // ----- Bouton Quit -----
    if (buttonQuit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonQuit.setOutlineColor(sf::Color::Cyan);

        // Quitter le jeu
        if (victory && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            alwaysClick = true;
            window.close();
        }
    }
    else {
        buttonQuit.setOutlineColor(sf::Color::White);
    }

    imageExit.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.27));
    window.draw(buttonQuit);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }

    window.display();

}

// ----- Menu crédits -----
void Menu::creditMenu(sf::RenderWindow& window) {

    mousePos = sf::Mouse::getPosition(window);

    window.clear(sf::Color::Black);

    initializeButtonsCredit(window);
    imageFond.drawImage(window, window.getSize().x, window.getSize().y, 0, 0);
    imageCredit.drawImage(window, window.getSize().x / 3, window.getSize().y / 11, float(window.getSize().x / 3), float(window.getSize().y / 13));

    imageArtDevelopment.drawImage(window, window.getSize().x / 2.5, window.getSize().y / 20, float(window.getSize().x / 22), float(window.getSize().y / 4));
    imageDevelopmentDepartment.drawImage(window, window.getSize().x / 2.1, window.getSize().y / 20, float(window.getSize().x / 2), float(window.getSize().y / 4));
    imageArt.drawImage(window, window.getSize().x / 2.5, window.getSize().y / 3, float(window.getSize().x / 17), float(window.getSize().y / 2.8));
    imageDev.drawImage(window, window.getSize().x / 2.5, window.getSize().y / 2.5, float(window.getSize().x / 1.8), float(window.getSize().y / 2.8));

    // ----- Bouton Back -----
    if (buttonBack.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        buttonBack.setOutlineColor(sf::Color::Cyan);

        // Accès au menu de victoire
        if (credits && InputManager::instance()->handleInputMouse(sf::Mouse::Left) && !alwaysClick) {
            audio.playSound("click_button");
            alwaysClick = true;
            credits = false;
            victory = true;
        }

    }
    else {
        buttonBack.setOutlineColor(sf::Color::White);
    }

    //DrawText(window, "Back", window.getSize().x / 32, float(window.getSize().x / 2.15), float(window.getSize().y / 1.29), sf::Color::White);
    imageBack.drawImage(window, window.getSize().x / 10, window.getSize().y / 16, float(window.getSize().x / 2.21), float(window.getSize().y / 1.18));
    window.draw(buttonBack);

    if (!InputManager::instance()->handleInputMouse(sf::Mouse::Left)) {
        alwaysClick = false;
    }

    window.display();

}

// ----- Input pour aller sur le menu de pause -----
void Menu::goToPause() {

    // Pour aller sur le menu de jeu
    if (!pause && InputManager::instance()->handleInputKeyboard(sf::Keyboard::Escape)) {
        audio.pauseAllSounds();
        pause_menu = true;
    }

}

// ----- Fonction pour définir ce qui est appelé sur chaque menu -----
void Menu::differentsMenus(sf::RenderWindow& window) {

    if (start_menu) {
        startMenu(window);
        victory = false;
        game_over = false;
    }
    if (option_menu) {
        start_menu = false;
        pause_menu = false;
        optionsMenu(window);
    }
    if (pause_menu) {
        pause = true;
        PauseMenu(window);
    }
    if (game_over) {
        pause = true;
        gameOverMenu(window);
    }
    if (victory) {
        pause = true;
        VictoryMenu(window);
    }
    if (credits) {
        creditMenu(window);
    }

}

bool Menu::getPause() {
    return pause;
}


void Menu::reset() {
    restart_game = false;
    game_over = false;
    victory = false;
    pause = true;
    start_menu = true;
    option_menu = false;
    pause_menu = false;
    credits = false;
    since_pause_menu = false;
    since_start_menu = false;
    alwaysClick = false;
    resourcesLoaded = false;
    audio.pauseAllSounds();
}