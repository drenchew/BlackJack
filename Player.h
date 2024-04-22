#pragma once

#include "BaseGameLogic.h"
#include "Deck.h"
#include"Balance.h"

class Player final : public BaseGameLogic
{
public:
    Player(Deck* deck);
    virtual void hit() override final;
    virtual void check() override;
    void double_down();
    const State get_status() const;

private:
    void determine_status();

    DeckInterface* deck_interface;
    State _status;
    Balance _balance;

    bool double_on_off = false;
};
