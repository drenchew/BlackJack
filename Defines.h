#pragma once

#ifndef DEFINES_H
#define DEFINES_H

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

Symbols& operator++(Symbols& e);

enum class Suits
{
    CLUBS = 1,
    DIAMONDS,
    HEARTS,
    SPADES,

    NO_SUIT = 400
};

Suits& operator++(Suits& e);

#endif // !DEFINES_H
