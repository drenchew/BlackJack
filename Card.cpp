#include "Card.h"

Card::Card(const Symbols& symbol, const Suits& suit) {
    _path = ".\\assets\\cards\\";

    _suit = suit;
    _symbol = symbol;

    switch (_symbol) {
    case Symbols::ACE:
        _path += "ace_of_";
        break;
    case Symbols::TWO:
        _path += "2_of_";
        break;
    case Symbols::THREE:
        _path += "3_of_";
        break;
    case Symbols::FOUR:
        _path += "4_of_";
        break;
    case Symbols::FIVE:
        _path += "5_of_";
        break;
    case Symbols::SIX:
        _path += "6_of_";
        break;
    case Symbols::SEVEN:
        _path += "7_of_";
        break;
    case Symbols::EIGHT:
        _path += "8_of_";
        break;
    case Symbols::NINE:
        _path += "9_of_";
        break;
    case Symbols::TEN:
        _path += "10_of_";
        break;
    case Symbols::JACK:
        _path += "jack_of_";
        break;
    case Symbols::QUEEN:
        _path += "queen_of_";
        break;
    case Symbols::KING:
        _path += "king_of_";
        break;
    default:
        _path = "";
    }

    switch (suit) {
    case Suits::CLUBS:
        _path += "clubs";
        break;
    case Suits::DIAMONDS:
        _path += "diamonds";
        break;
    case Suits::HEARTS:
        _path += "hearts";
        break;
    case Suits::SPADES:
        _path += "spades";
        break;
    default:
        _path = "";
    }

    if (_path == "") {
        std::cerr << "ERROR NO IMAGE\n";
        return;
    }
    _path += ".png";

    try
    {
        _cardTexture.loadFromFile(_path);
        this->_cardSprite.setScale(0.18, 0.18);
        _cardTexture.setSmooth(true);
        _cardSprite.setTexture(_cardTexture);
        
    }
    catch (const std::exception& e)
    {
        std::cerr << "PROBLEM LOADING: " << e.what() << std::endl;
    }

   
}

void Card::draw_card(sf::RenderWindow& window)  {
    window.draw(_cardSprite);

   
}

bool Card::operator==(const Card& other) const {
    return (other.get_path() == this->get_path());
}

bool Card::operator!=(const Card& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& ostr, const Card& card) {
    ostr << card.get_path() << std::endl;
    return ostr;
}
