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
    virtual int total_cards() const = 0;
    virtual std::shared_ptr<Card> get_card() = 0;
    virtual std::shared_ptr<Card> view_card() const = 0;
    inline virtual void pop_card() = 0;
    virtual ~DeckInterface() = default;
};

class Deck : public DeckInterface {
public:
    Deck();
    void generate_deck2();

    //TEST CASES
     
    void test_deck() {
        for (size_t i = 0; i < 20; i++)
        {
            this->_deck.push_back(std::make_shared<Card>(Symbols::THREE, Suits::DIAMONDS));
        }
       // this->_deck.push_back(std::make_shared<Card>(Symbols::THREE,Suits::DIAMONDS));
    }

    //!TEST CASES

    virtual int total_cards() const override {
        return _deck.size();
    }

    inline virtual void pop_card() override{
        this->_deck.pop_back();
    }

    virtual std::shared_ptr<Card> get_card() override {
        if (_deck.empty()) {
            return nullptr; // or throw std::out_of_range
        }
        std::shared_ptr<Card> card = _deck.back();
        _deck.pop_back();
        return card;
    }

    virtual std::shared_ptr<Card> view_card() const override final {
        if (_deck.empty()) {
            return nullptr; // or throw std::out_of_range
        }
        return _deck.back();
    }

private:
    std::vector<std::shared_ptr<Card>> _deck;
public: bool finished;
};

#endif // DECK_H
