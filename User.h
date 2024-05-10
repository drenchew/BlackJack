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
    User():deck_interface(NULL){}

    virtual State hit() = 0;
    virtual State check() = 0;
    virtual const State getStatus() const = 0;
    virtual void setStatus(const State state)  = 0;
    virtual void drawHand(sf::RenderWindow& window) = 0;

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