#include "Player.h"
#include <iostream>

Player::Player(Deck* deck) : deck_interface(deck), _status(State::NO_STATUS) {
    //lock_actions = false;
}

State Player::hit() {
    // Implement hit logic
    this->_score +=
    this->deck_interface->view_card()->get_card_val();
   // this->deck_interface->get_card()->draw_card();

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

    return determine_status();
}

const State Player::get_status() const {
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
