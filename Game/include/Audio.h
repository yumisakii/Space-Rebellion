#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

class Audio {

public:

    static Audio& getInstance() {
        static Audio instance;
        return instance;
    }

    Audio() = default;
    ~Audio() = default;

    void loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);

    void pauseAllSounds();
    void resumeAllSounds();

    void cleanupFinishedSounds();

private:

    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
    std::vector<std::unique_ptr<sf::Sound>> activeSounds;

    // Map pour suivre la position de chaque son
    std::unordered_map<sf::Sound*, sf::Time> soundPositions;
};


class VolumeSlider {

public:

	VolumeSlider(float x, float y, float width, float height);

	void handleInput(sf::RenderWindow& window);
	void update();
	void draw(sf::RenderWindow& window);

	float getVolume() const;

private:

	float volume;
	bool isDragging;

	sf::RectangleShape barBackground;
	sf::RectangleShape barFill;
	sf::CircleShape slider;

	float barWidth;
	float sliderRadius;
};