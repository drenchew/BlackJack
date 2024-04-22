#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include<iostream>
#include"Defines.h"
#include <SFML/Graphics.hpp>


class Image {
public:
    sf::Vector2f _possition;

public:
    Image(const BUTTON& btn ,bool background = false);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePosition) const;

    
    BUTTON _btn = BUTTON::UNKNOWN;

    sf::Texture bg_texture;
    sf::Sprite bg_sprite;
};

#endif // !IMAGE_H