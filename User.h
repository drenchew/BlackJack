#pragma once
#ifndef USER_H
#define USER_H



#include <vector>
#include <memory>
#include "Card.h"

#include"Deck.h"


class User
{
public:

    User(Deck* d) : deck_interface(d) {}

    User(Deck* d,int x,int y, int rot) : deck_interface(d),
        _default_x(x),_default_y(y),_rotation(rot),
        _status(State::NO_STATUS)
    {}

    User():deck_interface(NULL){}

    // Pure Virtual



    virtual State hit() = 0;
    virtual State check() = 0; 

    virtual const uint16_t getScore() const { return this->_score; }
    virtual const State getStatus() const { return this->_status; }
    virtual void setStatus(const State state) { _status = state; }

    void clearHand() { my_cards.clear(); }

    void resetUser() {
        this->_aces = 0;
        this->_score = 0;
        this->_status = State::NO_STATUS;
    }

    virtual void drawHand(sf::RenderWindow& window) {
        int temp_x = _default_x,
            temp_y = _default_y,
            temp_rot = _rotation;

        for (auto& card : my_cards)
        {
            card->setPosition(sf::Vector2f(temp_x, temp_y));
            temp_x += SHIFT_CARD_X;
            temp_y += SHIFT_CARD_Y;
            temp_rot += ROTATION_ANG;
            card->setRotation(temp_rot);
            card->draw_card(window);
        }
    }

    void updare_balance(const float a) {

    }

    virtual State double_down() {
        hit();
        if (_score < 21) {
            _status = State::DOUBLE;
        }

        return State::DOUBLE;
    }


    inline virtual int totalCards() { return this->my_cards.size(); }

    virtual ~User() = default;

    DeckInterface* deck_interface;

    float _default_x = 0;
    float _default_y = 0;
    float _rotation = 0;
protected:

     State _status;
     uint16_t _score = 0;
     uint16_t _aces = 0;

    std::vector<std::shared_ptr<Card>> my_cards;
};

#endif // !USER_H