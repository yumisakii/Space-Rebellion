#include "Image.h"


bool Image::loadImage(const std::string& filePath) {

    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Erreur de chargement de l'image ! " << std::endl;
        return false;
    }
    sprite.setTexture(texture);
    return true;
}

void Image::drawImage(sf::RenderWindow& window, float targetWidth, float targetHeight, float x, float y) {

    if (texture.getSize().x == 0 || texture.getSize().y == 0) {
        std::cerr << "Erreur : La texture ne charge pas correctement." << std::endl;
        return;
    }

    // Calcul de l'échelle à partir de la taille cible
    float scaleX = targetWidth / texture.getSize().x;
    float scaleY = targetHeight / texture.getSize().y;

    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(x, y);
    window.draw(sprite);

}