#ifndef interface_h
#define interface_h
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "pr2.player.h"
#include "pr2.board.h"
#include "pr2.places.h"
using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals; 


class Menu{

    public:
    int turn;
    void displaymenu(int whoseturn, Board& GAME); //going to be the main overlay, displayed below the game.
    Board GAME(int numplayers);


    //displaymenu displayed as:
    //Player whose turn it is
    //|||||||||||||||||||||||||||||||||||||||||||||||||| (game)
    //last event
    //menu, all in one line
    Menu();
    Menu(int numplayers); // this is the function where the whole game is run
    int goforward(int playerindex, Board& GAME);//needed a movement function in interface regardless, decided to seed the random number here as it made it more aesthetically pleasing to have access to the number generated
    void checkcharacter(int playerindex, Board& GAME); //show stats and advisor. player will not be able to change advisors, so they have to choose carefully.
    void getInfo(Board& GAME); //was originally going to print it all at once, but decided to make it user choice what they really wanted to see.
    void gameOver(Board& GAME, int numplayers); //function to end the game, prints the final messages and stats both to the terminal and to gamelog.


    //Note: I was about to turn it in and I was just thinking like wow it'd be really easy to put one of those pixel
    //art things and I was like damn that'd be pretty easy to put in so i did, and i didn't want it to just place it right there, so I 
    //gave it a little 50 ms debuffer and it came out even better than i was looking for

    



};
#endif