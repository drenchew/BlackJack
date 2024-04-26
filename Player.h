#pragma once

#include "BaseGameLogic.h"
#include "Deck.h"
#include"Balance.h"

class Player final : public BaseGameLogic
{
public:
    Player(Deck* deck);
    Player(Deck* deck, float x,float y,float rotation);
    virtual State hit() override final;
    virtual State check() override;
    State double_down();

    virtual void drawHand(sf::RenderWindow& window)
    {
        int temp_x = _default_x, temp_y = _default_y;
        int temp_rot = _rotation;
        for (auto& card : my_cards)
        {
            card->setPosition(sf::Vector2f(temp_x, temp_y));
            temp_x += SHIFT_X;
            temp_y += SHIFT_Y;
            temp_rot += ROTATION_ANG;
            card->setRotation(temp_rot);
            card->draw_card(window);
        }
    }

    virtual const State get_status() const;

    DeckInterface* deck_interface;
private:
    State determine_status();

 
    State _status;
    Balance _balance;

    bool double_on_off = false;
};
