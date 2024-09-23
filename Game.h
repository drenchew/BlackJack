#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <exception>
#include "Defines.h"
#include "Deck.h"
#include "Image.h"
#include "Player.h"
#include "Dealer.h"


class Game {
private:
    sf::RenderWindow window;
    Deck deck;
    std::vector<std::shared_ptr<Image>> images;
    std::vector<std::shared_ptr<User>> players;
     volatile int playerNum =0;

    void initPlayers();
    void initImages();
    bool delearsTurn();
    void drawScreen();
    bool takeAction(BUTTON btn);

    void loadGame() {
        initImages();
        initPlayers();
    }
    void restartGame();

public:
    Game();
    void start();
};

#endif // GAME_H
