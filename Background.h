#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background {
public:
    Background();
    void draw_background(sf::RenderWindow& window);

private:
    sf::Texture bg_texture;
    sf::Sprite bg_sprite;
};

#endif // !BACKGROUND_H