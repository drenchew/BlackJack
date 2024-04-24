#pragma once

#include "BaseGameLogic.h"
#include "Deck.h"
#include"Balance.h"

class Player final : public BaseGameLogic
{
public:
    Player(Deck* deck);
    virtual State hit() override final;
    virtual State check() override;
    State double_down();
    const State get_status() const;

private:
    State determine_status();

    DeckInterface* deck_interface;
    State _status;
    Balance _balance;

    bool double_on_off = false;
};
