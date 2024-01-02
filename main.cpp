#include "HangmanGame.hpp" // Include HangmanGame.hpp
#include "Player.hpp"
#include "Room.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <stdlib.h>
#include <time.h>

const int numOfRooms = 6;
const int maxPoints = 150;

// Forward declaration
bool hangmanGame();

void movePerson(Player *myPlayer, Room *world[], int &totalPoints);
void bribing(Player *myPlayer, int &totalPoints);
void instructions();

int main() {
  bool playAgain = true;

  while (playAgain) {
    // create a pointer to player object
    // Player *myPlayer;
    bool gameOver = false;
    int totalPoints = 0; // Initialize total points

    // Dynamic pointer array with pointers to room objects
    Room *world[numOfRooms] = {new Room("Outside the old creepy building"),
                               new Room("The hallway"),
                               new Room("The library"),
                               new Room("The chapel"),
                               new Room("The dungeon"),
                               new Room("Werewolf's lair")};

    // point myPlayer to a new Player
    std::unique_ptr<Player> myPlayer =
        std::make_unique<Player>("Lancelot", numOfRooms);

    // myPlayer = new Player("Lancelot", numOfRooms);

    instructions();

    while (gameOver == false) {
      movePerson(myPlayer.get(), world, totalPoints);

      // movePerson(myPlayer, world, totalPoints);

      if (myPlayer->getHealth() <= 0) {
        gameOver = true;
      } else if (myPlayer->getLoc() >= numOfRooms) {
        std::cout << "You've won!" << std::endl;
        totalPoints += maxPoints; // Add points for completing all levels
        gameOver = true;
        break; // Exit the loop when the player wins
      } else {
        std::cout << "Level " << myPlayer->getLoc() + 1
                  << ": The location now is ";
        std::cout << world[myPlayer->getLoc()]->getDescription() << std::endl;
      }
    }

    std::cout << "Game Over!" << std::endl;
    std::cout << "TOTAL POINTS: " << totalPoints << " / "
              << "300" << std::endl;

    // Clean up allocated memory
    // delete myPlayer;
    for (int i = 0; i < numOfRooms; ++i) {
      delete world[i];
    }

    // Play again logic
    std::cout << "Do you want to play again? Enter (y)es or (n)o: ";
    char playChoice;
    std::cin >> playChoice;

    if (playChoice == 'n') {
      playAgain = false;
    } else if (playChoice != 'y') {
      std::cout << "Invalid input. Exiting the game." << std::endl;
      playAgain = false;
    }
  }

  return 0;
}

void movePerson(Player *myPlayer, Room *world[], int &totalPoints) {
  char action;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "You've come across a really nasty monster." << std::endl;
  std::cout << "Choose from one of the following options to continue."
            << std::endl;
  std::cout << "What do you want to do? (f)ight, (b)ribe, or (a)dventure?"
            << std::endl;
  std::cin >> action;

  if (action == 'b') {
    std::cout << "- You are bribing" << std::endl;
    bribing(myPlayer, totalPoints);
  } else if (action == 'f') {
    std::cout << "- You are fighting" << std::endl;
    myPlayer->fight();
    // Check if the player wins the fight before moving to the next room
    if (myPlayer->getHealth() > 0) {
      myPlayer->moveRight(); // Move the player after winning the fight
      totalPoints += 25;     // Add points for each level completed
    }
  } else if (action == 'a') {
    std::cout << "- You chose to embark on an adventure to escape the monster, "
                 "you must complete this challenge to continue your journey"
              << std::endl;

    while (true) {
      if (hangmanGame()) { // Call the hangman game function and check if the
                           // player guessed the word
        // Update points if the player successfully guesses the word
        totalPoints += 25;
        std::cout
            << "Congratulations! You successfully guessed the word and earned "
               "25 points!"
            << std::endl;
        myPlayer->moveRight(); // Move the player to the next room after Hangman
        break;                 // Exit the loop after successful Hangman game
      } else {
        std::cout << "You didn't guess the word. Try again." << std::endl;
      }
    }
  } else {
    std::cout
        << "Invalid input. Please enter 'f' for fight, 'b' for bribe, or 'a' "
           "for adventure."
        << std::endl;
  }
}

void bribing(Player *myPlayer, int &totalPoints) {
  int amount;
  std::cout << "How much would you like to bribe?" << std::endl;
  std::cin >> amount;

  // Error handling for non-integer input
  while (std::cin.fail()) {
    std::cout << "Invalid input. Please enter a valid number." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> amount;
  }

  myPlayer->bribe(amount);
  myPlayer->moveRight(); // Move the player to the next room after bribing
}

void instructions() {
  std::cout << "WELCOME" << std::endl;
  std::cout << "\n"; // blank line
  string text =
      "Your mission is to rescue the maiden from the werewolf by successfully "
      "completing the 6 levels.You'll start with 30 gold coins and your health "
      "at 100%, try to remember these numbers to make wise decisions....Good "
      "Luck!";         // A string variable
  string *ptr = &text; // A pointer variable that stores the address of 'text'

  // Output the value text
  cout << text << "\n";

  std::cout << "\n";
}