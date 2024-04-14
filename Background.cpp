#include "Background.h"

Background::Background() {
    this->bg_texture.loadFromFile(".\\assets\\bgtable.jpg");
    bg_sprite.setTexture(bg_texture);
}

void Background::draw_background(sf::RenderWindow& window) {
    window.draw(bg_sprite);
}
