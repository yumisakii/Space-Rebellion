#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Entity.h"
#include "Game.h"
#include "Audio.h"
#include "Background.h"
#include "Menu.h"
#include "ManageEntities.h"
#include "vfx.h"
#include "playerEntity.h"

auto vfxSprite = VFXSprite::getInstance();


int Game::game() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Rebellion", sf::Style::Fullscreen); //sf::Style::Fullscreen
    
    sf::Clock clock;
    window.setFramerateLimit(60);

    InputManager* inputManager = InputManager::instance();
    Menu menu;
    Audio& audio = Audio::getInstance();

    audio.loadSound("backMusic", "Assets/Sounds/Back_music.mp3");
    audio.loadSound("bossMusic", "Assets/Sounds/Boss_music.mp3");
    audio.loadSound("click_button", "Assets/Sounds/Clic_navigation.mp3");
    audio.loadSound("shoot", "Assets/Sounds/Shoot.wav");
    audio.loadSound("boom", "Assets/Sounds/Boom.wav");
    audio.loadSound("gameOver", "Assets/Sounds/Game_over.wav");

    sf::Listener::setGlobalVolume(20.f);
    
    // Charger les textures des backgrounds
    sf::Texture bgTexture1, bgTexture2, bgTexture3;
    if (!bgTexture1.loadFromFile("Assets/Backgrounds/route+plan 1.png") ||
        !bgTexture2.loadFromFile("Assets/Backgrounds/Plan 2.png") ||
        !bgTexture3.loadFromFile("Assets/Backgrounds/Plan 3.png")) {
        std::cerr << "Erreur de chargement des textures de background." << std::endl;
        return -1;
    }

    if (!imageBackground.loadImage("Assets/Backgrounds/fond.png")) {
        std::cerr << "Impossible de charger l'image de fond de jeu." << std::endl;
    }

    // Creer les couches de fond avec des vitesses differentes
    ParallaxLayer layer1(bgTexture1, 150.f, sf::Vector2f(1.23f, 1.23f));
    ParallaxLayer layer2(bgTexture2, 100.f, sf::Vector2f(1.23f, 1.23f));
    ParallaxLayer layer3(bgTexture3, 50.f, sf::Vector2f(1.f, 1.f));


    std::vector<sf::Texture> textures(4); // Exemple avec 4 frames
    if (!textures[0].loadFromFile("Assets/Vfx/Fx_Sprite_1.png") ||
        !textures[1].loadFromFile("Assets/Vfx/Fx_Sprite_2.png") ||
        !textures[2].loadFromFile("Assets/Vfx/Fx_Sprite_3.png") ||
        !textures[3].loadFromFile("Assets/Vfx/Fx_Sprite_4.png")) {
        std::cerr << "Erreur de chargement des textures de background." << std::endl;
        return -1;
    }

    vfxSprite->setTexture(textures);
    vfxSprite->setFrameTime(0.1);

    initEntities(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (restart_game)
        {
            resetGame(window);
            menu.reset();
            game_over = false;
            restart_game = false;
        }
        float deltaTime = clock.restart().asSeconds();

        menu.differentsMenus(window);

        if (!menu.getPause()) {
            
            updateMobWave(deltaTime);
            updateBg(deltaTime, layer1, layer2, layer3);
            updateEntities(window, deltaTime);

            vfxSprite->update(deltaTime);

            window.clear(sf::Color::Black);
            imageBackground.drawImage(window, window.getSize().x, window.getSize().x, 0, 0);
            drawBg(window, layer1, layer2, layer3);
            drawEntities(window);
            vfxSprite->render(window);

            window.display();
        }
        menu.goToPause();
    }
    return 0;
}