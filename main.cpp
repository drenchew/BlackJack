#include <SFML/Graphics.hpp>

#include<thread>
#include<mutex>
#include<chrono>
#include <exception>

#include "Defines.h"
#include "Card.h"
#include"Deck.h"
#include"Image.h"

#include"Player.h"
#include"Balance.h"


typedef std::vector< std::shared_ptr<Player>> PLAYERS;



static volatile int playerNum = 0;

void initPlayers(std::vector< std::shared_ptr<Player>>& players,Deck& d) {
    players.push_back(std::make_shared<Player>(&d, 320, 66, 50));
    players.push_back(std::make_shared<Player>(&d, 490, 210, -10));
    players.emplace_back(std::make_shared<Player>(&d, 707, 137, -70)); 
}

void initImages(std::vector<std::shared_ptr<Image>>& images)
{
    images.push_back(std::make_shared<Image>(BUTTON::UNKNOWN, true)); // background
    images.push_back(std::make_shared<Image>(BUTTON::CHECK_BTN));  
    images.push_back(std::make_shared<Image>(BUTTON::HIT_BTN));
    images.push_back(std::make_shared<Image>(BUTTON::DOUBLE_BTN));
}


void drawScreen(sf::RenderWindow& window, std::vector<std::shared_ptr<Image>>& imgs,
    std::vector< std::shared_ptr<Player>>& players)
{
    for (auto& img : imgs)
    {
        img->draw(window);
    }
    for (auto& player : players)
    {
        player->drawHand(window);
    }
}

void takeAction(BUTTON btn, std::vector<std::shared_ptr<Player>>& players)
{
  //  static volatile int playerNum = 0;
    
    if (playerNum >= players.size()) { return; }
    
    
    switch (btn)
    {
    case BUTTON::HIT_BTN:
        if ((players[playerNum]->getStatus() == State::DOUBLE)  ||  
           players[playerNum]->getStatus() == State::CHECK)
        {return;}
        players[playerNum]->hit();
        break;
    case BUTTON::CHECK_BTN: players[playerNum]->check(); playerNum++;
        break;
    case BUTTON::DOUBLE_BTN: 
        if (players[playerNum]->getStatus() != State::NO_STATUS) { return; }
        players[playerNum]->double_down(); playerNum++;
        break;
    case BUTTON::UNKNOWN: throw std::runtime_error("Something went wrong!");;
        break;
    }
    if (playerNum >= players.size()) { playerNum--; }
}


int main()
{
    sf::RenderWindow window (sf::VideoMode(1024, 720), "SFML works!");
 
    Deck d;
    std::thread deck_thread(&Deck::generate_deck2, &d);


    std::vector<std::shared_ptr<Image>> images;
    initImages(images);


    std::vector< std::shared_ptr<Player>> players;
    initPlayers(players,d);
   

    deck_thread.join();
   // d.test_deck();

    for (size_t i = 0; i < 2; i++)
    {
        for (auto& player : players)
        {
            drawScreen(window, images, players);

            player->hit();
            player->drawHand(window);
            window.display();

          //  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for 2 seconds

            player->deck_interface->pop_card();
        }
       
      

    }
    //print(p1.totalCards());
    std::cout << "AFTER FOR\n";
    
    for (auto& p : players)
    {
        p->setStatus(State::NO_STATUS);
    }


   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if (d.finished) { window.close();}
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));


                        // Check if the check button is clicked
                        if (images[1]->isClicked(mousePosition)) {
                            std::cout << "check clicked\n";
                            takeAction(BUTTON::CHECK_BTN, players);
                        }
                        else if (images[2]->isClicked(mousePosition)) {
                        std::cout << "hit clicked\n";
                        takeAction(BUTTON::HIT_BTN, players);
                        }

                        // Check if the double button is clicked
                        else if (images[3]->isClicked(mousePosition)) {
                            std::cout << "double clicked\n";
                            takeAction(BUTTON::DOUBLE_BTN, players);
                        }
                   
                        if (playerNum < players.size()) {
                            switch (players[playerNum]->getStatus()) // incrementing playerNum and then using it
                            {
                            case State::BUST: playerNum++; break;
                                // case State::CHECK: std::this_thread::sleep_for(std::chrono::milliseconds(3000)); break;
                                // case State::DOUBLE:  std::this_thread::sleep_for(std::chrono::milliseconds(3000)); break;
                            }
                            d.pop_card();
                        }


                    
                }
            }
               
        }


       // window.clear();

       // std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds


        drawScreen(window, images,players);
       // players[0]->drawHand(window);


        window.display();
    }

Busted:
    window.clear();
    std::cout << "BUSTED\n";

    //delete p1;

 
   

    return 0;
}
