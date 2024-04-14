#pragma once

#ifndef DECK_H
#define DECK_H


#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>

#include "Card.h"

class DeckInterface
{
public:
    virtual  std::shared_ptr<Card> get_card() = 0;
    virtual ~DeckInterface() = default;
};


class Deck : public DeckInterface {
public:
    Deck();
    void generate_deck2();

    virtual  std::shared_ptr<Card> get_card() override {
       std::shared_ptr<Card> card = this->_deck.back();
       _deck.pop_back();
       return card;
    }

    bool finished;

private:
    std::vector<std::shared_ptr<Card>> _deck;

    template<typename T>
    T random_int(int range);
};



#endif // !DECK_H
