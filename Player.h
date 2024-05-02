#pragma once

#include "BaseGameLogic.h"
#include "Deck.h"
#include"Balance.h"

class Player final : public User
{
public:
    Player(Deck* deck);
    Player(Deck* deck, float x,float y,float rotation);
    virtual State hit() override final;
    virtual State check() override;
    State double_down();

    virtual void setStatus( const State state) 
    {
        _status = state;
    }


    virtual void drawHand(sf::RenderWindow& window)
    {
        int temp_x = _default_x, temp_y = _default_y;
        int temp_rot = _rotation;
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

    virtual const State getStatus() const;

    DeckInterface* deck_interface;
private:
    State determine_status();

 
    State _status;
    Balance _balance;

    bool double_on_off = false;
};
