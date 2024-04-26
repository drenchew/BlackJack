#include "Player.h"
#include <iostream>

Player::Player(Deck* deck) : deck_interface(deck), _status(State::NO_STATUS) {
    //lock_actions = false;
}

Player::Player(Deck* deck, float x, float y,float rotation) : Player(deck) {
    _default_x = x;
    _default_y = y;
    _rotation = rotation;
}


State Player::hit() {
    // Implement hit logic
    if (this->my_cards.emplace_back(
        this->deck_interface->view_card())->get_symbol() == Symbols::ACE)
    {   ++_aces;
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
    return determine_status();
}

State Player::double_down() {
    hit();
    if (_score < 21) {
        _status = State::DOUBLE;
    }

    return State::DOUBLE;
}

 const State Player::get_status() const  {
     return _status;
}

State Player::determine_status() {
    std::cout << "current score: " << _score << "\n";
    if (_score == 21) {
        _status = State::BLACKJACK;
    }
    else if (_score < 21) {
        _status = State::SUCCESS;
    }
    else {
        _status = State::BUST;
    }
    return _status;
}
