#include<iostream>
#include<string>
using namespace std;
 

class Room
{
  private:
    string description;
  public:
    Room(string description);

    //void getLocation();
    string getDescription();
};

Room::Room(string description){
    this->description = description;
}

string Room::getDescription(){
  return this->description;
}

