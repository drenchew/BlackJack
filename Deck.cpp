#include "Deck.h"
#include <iostream>



Deck::Deck() : finished(false) {
    // Reserve space for 52 cards
    _deck.reserve(NUM_CARDS_IN_DECK);
}

void Deck::generate_deck2() {
    // Generate all combinations of symbols and suits
    for (Symbols symbol = Symbols::ACE; symbol <= Symbols::KING; ++symbol) {
        for (Suits suit = Suits::CLUBS; suit <= Suits::SPADES; ++suit) {
            _deck.emplace_back(std::make_shared<Card>(symbol, suit));
        }
    }

    // Shuffle the deck
    std::shuffle(_deck.begin(), _deck.end(), std::mt19937{ std::random_device{}() });

    // Debug: Output the deck
    for (const auto& card : _deck) {
        std::cout << *card << std::endl;
    }
}
