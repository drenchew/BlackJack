#pragma once
#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>
#include<iostream>

#include "Defines.h"

class Card {
public:
    Card() = delete;
    Card(const Symbols& symbol, const Suits& suit);

    const Suits& get_suit() const { return _suit; }
    const std::string& get_path() const { return _path; }
    const Symbols& get_symbol() const { return _symbol; }

    int get_card_val() const {
        if ((int)_symbol > 10) { return 10;}
        return (int)_symbol;
    }
    void setRotation(float ang) { _cardSprite.setRotation(ang); }
    void setPosition(const sf::Vector2f& pos) { _cardSprite.setPosition(pos); }
    void scale(int a) { _cardSprite.setScale(a,a); }

    void draw_card(sf::RenderWindow& window) ;

    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

    friend std::ostream& operator<<(std::ostream& ostr, const Card& card);

private:
    sf::Texture _cardTexture;
    sf::Sprite _cardSprite;

    Symbols _symbol;
    Suits _suit;

    std::string _path;
};

namespace std {
    template <>
    struct hash<Card> {
        size_t operator()(const Card& card) const {
            return hash<int>()(static_cast<int>(card.get_symbol())) ^
                hash<int>()(static_cast<int>(card.get_suit()));
        }
    };
}

#endif // !CARD_H