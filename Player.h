#pragma once

#include "BaseGameLogic.h"
#include "Deck.h"
#include"Balance.h"

class Player final : public BaseGameLogic
{
public:
    Player(Deck* deck);
    Player(Deck* deck, float x,float y);
    virtual State hit() override final;
    virtual State check() override;
    State double_down();

    virtual const State get_status() const;

    DeckInterface* deck_interface;
private:
    State determine_status();

 
    State _status;
    Balance _balance;

    bool double_on_off = false;
};
