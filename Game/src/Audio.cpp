#include "Audio.h"

void Audio::loadSound(const std::string& name, const std::string& filepath) {
    std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filepath)) {
        std::cerr << "Erreur : Impossible de charger le fichier audio : " + filepath << std::endl;
    }
    soundBuffers[name] = std::move(buffer);
}

void Audio::playSound(const std::string& name) {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        std::cerr << "Erreur : Le son n'existe pas : " + name << std::endl;
        return;
    }

    // Créez une nouvelle instance de son dans un pointeur intelligent
    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(*it->second);
    sound->play();

    // Ajoutez le son à la liste active
    activeSounds.push_back(std::move(sound));

    // Nettoyez les sons terminés
    cleanupFinishedSounds();
}

void Audio::pauseAllSounds() {
    for (auto& sound : activeSounds) {
        if (sound->getStatus() == sf::Sound::Playing) {
            // Sauvegarder la position avant la mise en pause
            soundPositions[sound.get()] = sound->getPlayingOffset();
            sound->pause();
        }
    }
}

void Audio::resumeAllSounds() {
    for (auto& sound : activeSounds) {
        if (soundPositions.find(sound.get()) != soundPositions.end()) {
            // Reprendre la lecture à partir de la position sauvegardée
            sound->play();
            sound->setPlayingOffset(soundPositions[sound.get()]);
            soundPositions.erase(sound.get());
        }
    }
}

void Audio::cleanupFinishedSounds() {
    // Supprimez les sons qui ont terminé de jouer
    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(), [](const std::unique_ptr<sf::Sound>& sound) {
            return sound->getStatus() == sf::Sound::Stopped;
            }),
        activeSounds.end());
}

// ----- Slider -----
VolumeSlider::VolumeSlider(float x, float y, float width, float height)
    : volume(20.0f), isDragging(false), barWidth(width), sliderRadius(height / 2.0f) {

    // Barre de fond
    barBackground.setSize(sf::Vector2f(barWidth, height));
    barBackground.setFillColor(sf::Color(80, 80, 80)); // Gris
    barBackground.setPosition(x, y);

    // Barre remplie
    barFill.setSize(sf::Vector2f(volume / 100.0f * barWidth, height));
    barFill.setFillColor(sf::Color(60, 220, 70)); // Vert
    barFill.setPosition(x, y);

    // Curseur
    slider.setRadius(sliderRadius);
    slider.setOrigin(sliderRadius, sliderRadius); // Centre le cercle
    slider.setFillColor(sf::Color::White);
    slider.setPosition(x + (volume / 100.0f) * barWidth, y + height / 2.0f);
}

void VolumeSlider::handleInput(sf::RenderWindow& window) {

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    // Vérifie si on clique sur le slider
    if (slider.getGlobalBounds().contains(worldMousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            isDragging = true;
        }
    }

    // Si on déplace la souris avec le clic
    if (isDragging) {
        float newX = worldMousePos.x;
        float minX = barBackground.getPosition().x;
        float maxX = minX + barWidth;

        // Bloque le curseur dans les limites de la barre
        if (newX < minX) newX = minX;
        if (newX > maxX) newX = maxX;

        // Met à jour le volume en fonction de la position du curseur
        volume = ((newX - minX) / barWidth) * 100.0f;
        slider.setPosition(newX, slider.getPosition().y);

        // Met à jour la barre remplie
        barFill.setSize(sf::Vector2f(volume / 100.0f * barWidth, barFill.getSize().y));
    }

    // Relâchement de la souris
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        isDragging = false;
    }
}

void VolumeSlider::update() {
    // Ici, on pourrait synchroniser avec le son (SFML::Listener)
    sf::Listener::setGlobalVolume(volume);
}

void VolumeSlider::draw(sf::RenderWindow& window) {
    window.draw(barBackground);
    window.draw(barFill);
    window.draw(slider);
}

float VolumeSlider::getVolume() const {
    return volume;
}