SFML Blackjack Game
This is a simple Blackjack game built using C++ and SFML (Simple and Fast Multimedia Library). The game simulates a traditional blackjack game between players and a dealer, featuring actions like hitting, standing, and doubling down.

Features
Multiple Players: Simulates multiple players and a dealer.
Dealer AI: Dealer plays according to the rules of Blackjack.
Interactive Buttons: Players can click buttons to interact with the game (hit, stand, double down).
Visual Cards: Cards and actions are rendered using SFML.
Table of Contents
Features
Requirements
Installation
How to Play
License
Requirements
C++ Compiler (g++, MSVC, etc.)
SFML Library (version 2.5.1 or higher)
Windows, Linux, or macOS
Installation
Clone the Repository
bash
Copy code

cd sfml-blackjack
Build the Game
Windows
Install SFML:

Download the SFML library from https://www.sfml-dev.org/download.php.
Extract SFML to a directory on your system (e.g., C:/SFML).
Set Up in Visual Studio (or other IDE):

Open your Visual Studio project (or create a new one).
Configure include directories: Go to Project Settings > C/C++ > General > Additional Include Directories and add the SFML include path (e.g., C:/SFML/include).
Configure library directories: Go to Project Settings > Linker > General > Additional Library Directories and add the SFML lib path (e.g., C:/SFML/lib).
Link the necessary libraries:
Go to Linker > Input > Additional Dependencies and add sfml-graphics.lib, sfml-window.lib, and sfml-system.lib.
Build and Run:

Build the project in Release mode for optimized performance.
Run the executable in your IDE or directly from the output folder.
Linux/macOS
Install SFML:

bash
Copy code
sudo apt-get install libsfml-dev  # On Ubuntu
brew install sfml  # On macOS with Homebrew
Build the Game:

bash
Copy code
g++ -o blackjack Game.cpp Player.cpp Dealer.cpp -lsfml-graphics -lsfml-window -lsfml-system
Run the Game:

bash
Copy code
./blackjack  # For Linux/macOS
blackjack.exe  # For Windows (if using MinGW or similar)
Running the Game
After compiling, you can run the game directly from your terminal or command line:
Windows: Run the .exe file from your build folder.
Linux/macOS: Run the generated binary with ./blackjack.
How to Play
Objective: Beat the dealer by having a hand value closer to 21 without going over.
Controls:
Hit: Click the button to draw a card.
Check: Click the button to stand with your current hand.
Double: Double your bet and draw one more card.
Dealer's Turn: After all players act, the dealer plays based on Blackjack rules.
Winning: The winner is determined based on who has the closest hand to 21 without busting.
License
This project is licensed under the MIT License - see the LICENSE file for details.

Contributing
Fork the repository.
Create your feature branch (git checkout -b feature/AmazingFeature).
Commit your changes (git commit -m 'Add some AmazingFeature').
Push to the branch (git push origin feature/AmazingFeature).
Open a pull request.
