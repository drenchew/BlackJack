#pragma once

#ifndef DEFINES_H
#define DEFINES_H

constexpr short NUM_CARDS_IN_DECK = 52;

enum class Symbols
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,

    NO_SYMBOL = 400
};

enum class Suits
{
    CLUBS = 1,
    DIAMONDS,
    HEARTS,
    SPADES,

    NO_SUIT = 400
};

enum class BUTTON
{
    HIT_BTN,
    CHECK_BTN,
    DOUBLE_BTN,

    UNKNOWN = 404,
};

enum class State
{
    HIT,
    CHECK,
    DOUBLE,
    SPLIT,

    BUST,
    SUCCESS,
    BLACKJACK,

    NO_STATUS = 400,
};

template<typename T>
T& operator++(T& e) {
    int temp = static_cast<int>(e);
    temp++;
    e = static_cast<T>(temp);
    return e;
}

#endif // DEFINES_H
