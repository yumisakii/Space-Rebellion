#include "vfx.h"

std::shared_ptr<VFXSprite> VFXSprite::instance = nullptr;

// Constructeur
VFXSprite::VFXSprite(){}

// Ajoute un effet à une position
void VFXSprite::addEffect(const sf::Vector2f& position) {
    Effect effect;
    effect.sprite.setTexture(textures[0]); // Commence avec la première frame
    effect.sprite.setPosition(position);
    effect.currentTime = 0.0f;
    effect.currentFrame = 0;
    effect.finished = false;

    effects.push_back(effect);
}

// Met à jour les animations des effets
void VFXSprite::update(float deltaTime) {
    for (auto& effect : effects) {
        if (effect.finished) continue;

        effect.currentTime += deltaTime;

        // Passe à la frame suivante si nécessaire
        if (effect.currentTime >= frameTime) {
            effect.currentTime -= frameTime;
            effect.currentFrame++;

            if (effect.currentFrame < textures.size()) {
                int frameWidth = textures[effect.currentFrame].getSize().x;
                int frameHeight = textures[effect.currentFrame].getSize().y;
                effect.sprite.setTexture(textures[effect.currentFrame]);
                effect.sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
            }
            else {
                effect.finished = true; // Animation terminée
            }
        }
    }

    // Supprime les effets terminés
    effects.erase(
        std::remove_if(effects.begin(), effects.end(),
            [](const Effect& e) { return e.finished; }),
        effects.end());
}

// Dessine les effets actifs
void VFXSprite::render(sf::RenderWindow& window) {
    for (auto& effect : effects) {
        if (!effect.finished) {
            effect.sprite.setScale(0.3, 0.3);
            window.draw(effect.sprite);
        }
    }
}