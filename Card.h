#pragma once
#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>
#include<iostream>

#include "Defines.h"

class Card : public std::enable_shared_from_this<Card> {
public:
 
    Card(const Symbols& symbol, const Suits& suit);
    ~Card() { 
        static int cardnum = 0;
    }

    const Suits& get_suit() const { return _suit; }
    const std::string& get_path() const { return _path; }
    const Symbols& get_symbol() const { return _symbol; }

    std::shared_ptr<Card> flipCard(bool face=false) {
        if (face) {
            this->_cardTexture.loadFromFile(this->_path);
            return shared_from_this();
        }
        this->_cardTexture.loadFromFile(".\\assets\\cards\\back_black.png");
        return shared_from_this();
    }

    int get_card_val() const {
        if ((int)_symbol == 1 ) { return 11;}
        else if ((int)_symbol >= 10) { return 10; }
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


#endif // !CARD_H