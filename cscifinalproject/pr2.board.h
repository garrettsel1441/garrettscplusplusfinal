#ifndef BOARD_H
#define BOARD_H
#include "pr2.tile.h"
#include "pr2.player.h"
#include "pr2.support.h"
#include "pr2.places.h"


class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[3][_BOARD_SIZE];
    static const int _MAX_PLAYERS = 4;
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    int playerlane[4];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index);
    bool isPlayerOnTile(int player_index, int pos, int path);
    string display[3];
    


public:
    Board();
    Board(int player_count);
    string advisorfile = "advisorlist.txt";
    string characterfile = "characterlist.txt";
    string eventfile = "eventlist.txt";
    string riddlefile = "riddlelist.txt";
    string lastaction = "";
    player lion[4];
    Event events[70];
    Characters characters[8];
    Advisors advisors[6];
    Riddle riddles[27];
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index, int movementinc); //changed this function last minute, really because I want it to
    //say how much you had rolled so it feels more like a board game
    //also this is the only function which can trigger a negative tile affect, so if you get sent back for like a graveyard tile you dont just get screwed.
    int getPlayerPosition(int player_index) const;
    int playeradvisor[4];
    int playercharacter[4];
   //I'm gonna have 3 paths. pridelands, cub training, and then the wild lands. Players will be able to end up in the wild lands, but you can't get out once you're there.
   // players will also have the choice of starting in the
   //wildlands, except they will start with minimum pride points. Bonuses in the wild lands are larger though, and
   //other starting attributes.
   //wildlands will be 10 safaris and 39 special tiles, I was test-running and with green tiles with like a 50% chance of something negative, it was literally impossible 
   //other special functions, iscrossover will trigger a fight. In a fight, the lion with higher leadership will take the spot
   //and the lion with less leadership traits will move back 5 spaces, as well as lose 5000 pride points.

    void placePlayer(int player_index, int pos, int whichlane);//places player without any negative tile affect, used for exile.
    int getPlayerLane(int player_index) const;
    int winners = 0;
    char checkTile(int pos, int lane);//checks tile from position and lane
    bool iscrossover(int whichplayer);//checks if two players are overlapping for  fight
    void moveBack(int playa, int increment);//used in fights, hyenas and graveyards, same as moveplayer except does not check tile
    //but it does check for a fight
    void fight(int fighter1, int fighter2);//big fan of this function, already explained it somewhere else.
    void tileaffect(int whichplayer);
    //below functions are going to read the text files to populate events, characters, advisors, and riddles.
   void populateevents();
   void populatecharacters();//not sure i ever ended up using these, defined a seperate function in support.h
   void populateadvisors();
   void populateriddles();
   void startgame(int whichplaya);//menu for character selection, initialization
   void grasseffects(int affectswho);//random effect on the player from eventlist, i added some new ones for scar too, implements it onto the player
   void specialtile(int playerindex, int pos, int lane, int lastmove);// worked out tile effects, special cases for scar as an advisor and for wildlands
    //as a lane as graveyards made it literally impossible to move.
   bool runriddle();//generates and pressents a riddle, handles modifying player wisdom too.
   string message = "";
   const string tileinfo[10] = {
    "RED- Graveyard. Moves your lion back 10 spaces, unless in the Wild Lands where it is 3, and decreases leadership traits by 100.", 
    "GREEN- Grass. Has a 50% chance to trigger a special event, either positive or negative.", 
    "BLUE- Oasis. +200 to all of your lion's leadership traits.",
    "PURPLE- Riddle. Answer the riddle correctly and your lion will gain 1000 wisdom. Answer Wrong and they lose 200",
    "BROWN- Hyenas. Moves your lion back to their original position and lose 300 stamina.",
    "PINK- Counseling. Gives your lion +300 to strength & stamina, +500 to wisdom, and if you do not have an advisor, you can choose one.",
    "LIGHT YELLOW- Safari. Gives your lion +100 to all leadership traits. Does not appear in the Wild Lands.",
    "BLACK- Exile. Your lion is exiled and placed into the Wild Lands. Your lion also loses 1000 pride points.",
    "GREY- Starting Tiles. Only spot on the map other than the end where you are completely safe and cannot fight other players.",
    "ORANGE- Ending Tiles. Calculates final pride points from leadership traits, with the first players to arrive getting a bonus multiplier to their final pride points. Upon all players reaching the end, the winner is calculated from who has the most pride points.",};
    //^needed this for info in interface
    
    void calculatewinner(int numplayers, Places places[]);//calculates a places array going from best score at 0 to worst score at 3, with a multiplier to the first people to finish
    void calculateleader(int numplayers, Places places[]);//does the same, except no multiplier and is seeded originally just from the players' lanes
    int firsttofinish[4];//self explanatory, stows the playerindex for each iteration
    int calculatePP(int playerindex);//helper function for calculatewinner. Decided to have final pridepoints based 



    


};


#endif