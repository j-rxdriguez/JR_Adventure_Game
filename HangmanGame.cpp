#include "HangmanGame.hpp"
#include <cctype>
#include <iostream>
#include <random>
#include <set> // Include for set
#include <string>

using namespace std;

bool hangmanGame() {
  const int maxIncorrectGuesses = 6;
  int numGuesses = maxIncorrectGuesses;
  string words[] = {"treasure", "magic",    "goblin",
                    "cave",     "artifact", "wizard"};
  string word = words[rand() % 6];
  string dashes(word.length(), '-');
  set<char> guessedLetters; // Keep track of guessed letters

  while (numGuesses > 0 && dashes != word) {
    cout << dashes << endl;
    cout << numGuesses << " incorrect guesses left. " << endl;
    cout << "Guess: ";
    string guess;
    cin >> guess;

    // Convert the guess to lowercase
    char lowercaseGuess = tolower(guess[0]);

    if (guess.length() != 1 || !islower(lowercaseGuess)) {
      cout << "Invalid guess. Please enter a letter." << endl;
    } else {
      if (guessedLetters.count(lowercaseGuess) > 0) {
        cout << "You already guessed that letter. Try again." << endl;
      } else {
        guessedLetters.insert(lowercaseGuess);

        size_t indexFound = word.find(lowercaseGuess);
        if (indexFound != string::npos) {
          for (int i = 0; i < word.length(); i++) {
            if (word[i] == lowercaseGuess) {
              dashes[i] = lowercaseGuess;
            }
          }
          cout << "Correct!" << endl;
          cout << "----------------------------------------" << endl;
        } else {
          cout << "Incorrect!" << endl;
          cout << "----------------------------------------" << endl;
          numGuesses--;
        }
      }
    }
  }

  if (dashes == word) {
    cout << "You win!" << endl;
    return true;
  } else {
    cout << "You lose." << endl;
    cout << "The word was: " << word << endl;
    return false;
  }
}
