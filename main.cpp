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



int main()
{

   // srand(time(NULL));
    sf::RenderWindow window (sf::VideoMode(1024, 720), "SFML works!");
 
    Deck d;
    std::thread deck_thread(&Deck::generate_deck2, &d);

    Image bg(BUTTON::UNKNOWN,true);
    Image check_btn(BUTTON::CHECK_BTN);
    Image hit_btn(BUTTON::HIT_BTN);
    Image double_btn(BUTTON::DOUBLE_BTN);


    Player p1(&d);

   

   
    bool isButtonClicked = false;


    deck_thread.join();
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

                    // Check if the hit button is clicked
                    if (hit_btn.isClicked(mousePosition)) {
                        std::cout << "hit clicked\n";
                        p1.hit();
                        

                    }

                    // Check if the check button is clicked
                    else if (check_btn.isClicked(mousePosition)) {
                        std::cout << "check clicked\n";
                        p1.check();

                    }

                    // Check if the double button is clicked
                    else if (double_btn.isClicked(mousePosition)) {
                        std::cout << "double clicked\n";
                        p1.double_down();

                    }

                    std::cout << (int)p1.get_status()<< "\n";

                    switch (p1.get_status())
                    {
                    case State::BUST: continue;
                    case State::CHECK: continue;
                    case State::DOUBLE: continue;
                    }

                   
                }
            }
               
        }

        window.clear();
        // Draw sprite instead of shape
        bg.draw(window);
        
       // window.draw(sprite);
        //if (d.total_cards()) { 
       //  d.get_card()->draw_card(window);
       // }
       
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds

        hit_btn.draw(window);
        check_btn.draw(window);
        double_btn.draw(window);

       //c.draw_card(window);
        window.display();
    }

 
  

    return 0;
}
