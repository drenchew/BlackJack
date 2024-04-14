#include "Deck.h"


Deck::Deck() {
    _deck.reserve(52);
    finished = false;
}

void Deck::generate_deck2() {
    for (Symbols symbol = Symbols::ACE; symbol <= Symbols::KING; ++symbol) {
        for (Suits suit = Suits::CLUBS; suit <= Suits::SPADES; ++suit) {
            _deck.emplace_back(std::make_shared<Card>(symbol, suit));
        }
    }
    std::shuffle(_deck.begin(), _deck.end(), std::mt19937{ std::random_device{}() });

    for (const auto& card : _deck) {
        std::cout << *card << std::endl;
    }
}

template<typename T>
T Deck::random_int(int range) {
    std::vector<int> v1(range);
    std::iota(v1.begin(), v1.end(), 1);
    std::shuffle(v1.begin(), v1.end(), std::mt19937{ std::random_device{}() });

    return static_cast<T>(v1[0]);
}
