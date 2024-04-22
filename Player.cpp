#include "Player.h"
#include <iostream>

Player::Player(Deck* deck) : deck_interface(deck), _status(State::NO_STATUS) {
    //lock_actions = false;
}

void Player::hit() {
    // Implement hit logic
}

void Player::check() {
    if (_score == 0) {
        return;
    }
    determine_status();
}

void Player::double_down() {
    hit();
    if (_score < 21) {
        _status = State::DOUBLE;
    }
}

const State Player::get_status() const {
    return _status;
}

void Player::determine_status() {
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
}
