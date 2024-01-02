#include<iostream>
#include<string>
using namespace std;
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Player
{
  private:
    int location;
    int health;
    int money;
    string name;
    int numRooms;
  public:
    Player(string name, int numRooms);
    string getName();
    int getHealth();
    void moveLeft();
    void moveRight();
    int getLoc();
    void bribe(int amount);
    void fight();
    
};

Player::Player(string name, int numRooms){
    this->name = name;
    this->numRooms = numRooms;
    money = 30;
    health = 100;
    location = 0;
}

string Player::getName(){
  return this->name;
}

int Player::getHealth(){
  return this->health;
}

//this is not used in this game
void Player::moveLeft(){
  if(location > 0){
    location--;
  }  
}

void Player::moveRight(){
  location++; 
}

int Player::getLoc(){
  return location;
}

void Player::bribe(int amount){
  money -= amount;
  if(money > 0 && amount >= 10){
    cout << "Your bribe was accepted" << endl;
    cout << "MONEY:  " << money << " gold coins left" <<endl;
  }
  else{
    cout << "Your bribe was rejected now you're dead" << endl;
    health = 0;
  }
}

void Player::fight(){
  srand (time(NULL));
  int damage = rand() % 30 + 1;
  health -= damage;
  if(health > 0){
    cout << "You've won the fight" << endl;
    cout << "CURRENT HEALTH: " << health << endl;
  }
  else{
    cout << "- You've lost the fight now you're dead" << endl;
  }
}

