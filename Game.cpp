#include "Game.h"
#include "Balance.h"

volatile int Game::playerNum = 0;

Game::Game() : window(sf::VideoMode(1024, 720), "SFML works!") {}

void Game::initPlayers() {
    if (!players.empty()) { return; }
    players.push_back(std::make_shared<Player>(&deck, 320, 66, 50));
    players.push_back(std::make_shared<Player>(&deck, 490, 210, -10));
    players.emplace_back(std::make_shared<Player>(&deck, 707, 137, -70));
    players.emplace_back(std::make_shared<Dealer>(&deck, 490, 10, -10));  // The Dealer
}

void Game::initImages() {
    if (!images.empty()) { return; }
    images.push_back(std::make_shared<Image>(BUTTON::UNKNOWN, true)); // background
    images.push_back(std::make_shared<Image>(BUTTON::CHECK_BTN));
    images.push_back(std::make_shared<Image>(BUTTON::HIT_BTN));
    images.push_back(std::make_shared<Image>(BUTTON::DOUBLE_BTN));
}

bool Game::delearsTurn() {
    const std::shared_ptr<Dealer>& dealer = std::static_pointer_cast<Dealer>(players.back());
    dealer->takeDecision(players);
    //deck.pop_card();
    return true;
}

void Game::drawScreen() {
    for (auto& img : images) {
        img->draw(window);
    }
    for (auto& player : players) {
        player->drawHand(window);
    }
}

bool Game::takeAction(BUTTON btn) {
    if (playerNum >= players.size()) { return false; }

    switch (btn) {
    case BUTTON::HIT_BTN:
        if ((players[playerNum]->getStatus() == State::DOUBLE) ||
            players[playerNum]->getStatus() == State::CHECK) {
            return false;
        }
        players[playerNum]->hit();
        return true;
        break;
    case BUTTON::CHECK_BTN: players[playerNum]->check(); playerNum++; return true;;
        break;
    case BUTTON::DOUBLE_BTN:
        if (players[playerNum]->getStatus() != State::NO_STATUS) { return false; }
        players[playerNum]->double_down(); playerNum++;
        return true;
        break;
    case BUTTON::UNKNOWN: throw std::runtime_error("Something went wrong!");;
        break;
    }
    if (playerNum >= players.size()) { playerNum--; }
    return false;
}

void Game::restartGame()
{
   // Player* ptr = (Player*)players[0].get();

    for (auto& user : players)
    {
        user->clearHand();
        user->resetUser();
    }
    
    this->deck.reset_deck();
   //deck.generate_deck2();
    window.clear();
    start();
}


void Game::start() {
  //  window.clear();
    std::thread deck_thread(&Deck::generate_deck2, &deck);
    initImages();
    initPlayers();
    deck_thread.join();

    for (size_t i = 0; i < 2; i++) {
        for (auto& player : players) {
            drawScreen();
            player->hit();
            player->drawHand(window);
            window.display();
            player->deck_interface->pop_card();
        }
    }

    for (auto& p : players) {
        p->setStatus(State::NO_STATUS);
    }

    bool actionReturn = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                if (deck.finished) { window.close(); }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if (images[1]->isClicked(mousePosition)) {
                        takeAction(BUTTON::CHECK_BTN);
                       // deck.pop_card();
                    }
                    else if (images[2]->isClicked(mousePosition)) {
                        actionReturn = takeAction(BUTTON::HIT_BTN);
                       
                    }
                    else if (images[3]->isClicked(mousePosition)) {
                        actionReturn = takeAction(BUTTON::DOUBLE_BTN);
                       
                    }

                    if(actionReturn)
                        deck.pop_card();

                    actionReturn = false;
                    if (playerNum < players.size()) {
                        

                        if (players.size() - 1 == playerNum) {
                            delearsTurn();
                            drawScreen();
                            window.display();
                            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                           // restartGame();
                           // throw;
                            return ;
                        }

                        if (players[playerNum]->getStatus() == State::BUST) { playerNum++; }
                        
                    }
                }
            }
        }

        drawScreen();
        window.display();
    }

    window.clear();
    std::cout << "BUSTED\n";
}
