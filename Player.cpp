#include "Player.h"
#include <iostream>
#include"Deck.h"

Player::Player(Deck* deck) : User(deck) {
   _status = State::NO_STATUS;
}

Player::Player(Deck* deck, float x, float y,float rotation) : User(deck,x,y, rotation) {}


State Player::hit() {

    this->my_cards.emplace_back(deck_interface->view_card());
    if (deck_interface->view_card()->get_symbol() == Symbols::ACE){
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

   return determine_status();
}

State Player::check() {
    if (_score == 0) {
        return State::NO_STATUS;
    }
    
    return _status = State::CHECK;
}




State Player::determine_status() {
    std::cout << "current score: " << _score << "\n";
    if (_score == 21) {
        _status = State::BLACKJACK;
    }
    else if (_score < 21) {
        _status = State::HIT;
    }
    else {
        _status = State::BUST;
    }
    return _status;
}
