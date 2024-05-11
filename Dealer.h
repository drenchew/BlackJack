#pragma once
#ifndef DEALER_H
#define DEALER_H

#include"User.h"

class Dealer: public User   {
public:

	Dealer(Deck* deck,int x,int y,int rot): User(deck,x,y,rot) {

	}
    virtual State hit() override
    {
        printf("in delaer hit\n"); 

        if (my_cards.empty()) {
            this->my_cards.emplace_back(deck_interface->view_card());
        }
        else {
            this->my_cards.emplace_back(deck_interface->view_card()->flipCard());
        }

        
        if (deck_interface->view_card()->get_symbol() == Symbols::ACE)
        {
            ++_aces;
            _score += 11;
        }
        else {
            _score += deck_interface->view_card()->get_card_val();
        }


        while (_score > 21 && _aces > 0) {
            _score -= 10; // Convert ace from 11 to 1
            _aces--;
        }

        

        return (State)0;
    }
    virtual State check() override
    {
        return (State)0;
    }

    virtual State double_down() override { return (State)404; }
    
};


#endif // !DEALER_H
