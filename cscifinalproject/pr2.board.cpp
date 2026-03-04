#include "pr2.board.h"
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define SAFARI "\033[48;2;205;186;136m"
//Safari will be like a slightly worse version of oasis.

//Two new colors, safari and exile. safari will be something positive and exile
//will be used as the 'exile' tile.
#define EXILE "\033[48;2;0;16;15m"
//EXILE will send the lion to the wildlands, regardless of starting position. The wildlands have plenty of opportunities,
//both good and bad for a lion. My hope is that multiple lions end up in here and the fight feature becomes interesting.

#define RESET "\033[0m"

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 3; i++)
    {
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void Board::initializeTiles(int a)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;
    srand(time(NULL));


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Keep track of green tile positions to ensure we place exactly 30 greens
    if (a == 0){
         for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for "start"
            temp.color = 'Y';
        } 
        else if (green_count < 30 && (  rand() % (total_tiles - i) < 35 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            
            int color_choice = rand() % 100;
            
                if (color_choice > 0 && color_choice <= 10){
                    temp.color = 'I'; // safari
                    }else if (color_choice > 10 && color_choice <= 20){
                    temp.color = 'B'; // blue
                    }else if (color_choice > 20 && color_choice <= 25){
                    temp.color = 'P'; // Pink
                    }else if (color_choice > 30 && color_choice <= 35){
                    temp.color = 'N'; // Brown
                    }else if (color_choice > 35 && color_choice <= 40){
                    temp.color = 'R'; // Red
                    }else if (color_choice > 40 && color_choice <=80){
                    temp.color = 'U'; // Purple
                    }else if(color_choice > 80 && color_choice <= 100){
                    temp.color = 'K';
                    }
            
        }

        // Assign the tile to the board for the specified lane
        _tiles[a][i] = temp;
    }
    }
    
    else if (a == 1){
        
        
        for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for "start"
            temp.color = 'Y';
        } 
        else if (green_count < 25 && (rand() % (total_tiles - i) < 25 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            
            int color_choice = rand() % 100;
            
                if (color_choice > 0 && color_choice <= 5){
                    temp.color = 'B'; // Blue
                    }else if (color_choice > 5 && color_choice <= 20){
                    temp.color = 'P'; // Pink
                    }else if (color_choice > 25 && color_choice <= 40){
                    temp.color = 'N'; // Brown
                    }else if (color_choice > 40 && color_choice <= 55){
                    temp.color = 'R'; // Red
                    }else if (color_choice > 55 && color_choice <=65){
                    temp.color = 'U'; // Purple
                    }else if(color_choice > 65 && color_choice <= 85){
                    temp.color = 'I';
                    }else if(color_choice > 85 && color_choice <= 100){
                    temp.color = 'K';
                    }
        }

        // Assign the tile to the board for the specified lane
        _tiles[a][i] = temp;
    }

    }else if (a == 2){
 for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for "start"
            temp.color = 'Y';
        } 
        else if (green_count < 10 && (rand() % (total_tiles - i) < 10 - green_count)) {
            temp.color = 'I';
            //wild lands was literally impossible unless you have scar as an advisor so i wanted to make it more of a gamble
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
           
            int color_choice = rand() % 100;
            
                if (color_choice > 80 && color_choice <= 100){
                    temp.color = 'B'; // Blue
                    }else if (color_choice > 50 && color_choice <= 60){
                    temp.color = 'P'; // Pink
                    }else if (color_choice > 0 && color_choice <= 25){
                    temp.color = 'N'; // Brown
                    }else if (color_choice > 25 && color_choice <= 50){
                    temp.color = 'R'; // Red
                    }else if (color_choice > 60 && color_choice <=80){
                    temp.color = 'U'; // Purple
                   
                
                    }
        }

        // Assign the tile to the board for the specified lane
        _tiles[a][i] = temp;
    }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}


 Board::Board()
 {
     _player_count = 1;
     // Initialize player position
     lion[0].pPos = 0;
     lion[0].pLane = 0;
     lion[0].character = 0;
     message = "";

     // Initialize tiles
     uploadadvisors(advisorfile, advisors);
uploadcharacters(characterfile, characters);
uploadevents(eventfile, events);
uploadriddles(riddlefile, riddles);
winners = 0;
     initializeTiles(1);
     
 }

Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }
    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        lion[i].pPos = 0;
        lion[i].pLane = 0;
        lion[i].character = 0;
        lion[i].setage(0);
                lion[i].setstamina(0);
                        lion[i].setstrength(0);
                                lion[i].setpridepoints(0);
                                        lion[i].setwisdom(0);
                                        lion[i].seticon(' ');
                                        lion[i].reachedend = false;
            winners = 0;




    }
    
   
uploadadvisors(advisorfile, advisors);
uploadcharacters(characterfile, characters);
uploadevents(eventfile, events);
uploadriddles(riddlefile, riddles);
    // Initialize tiles

    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos, int playerpath)
{
    if (lion[player_index].pPos == pos && lion[player_index].pLane == playerpath)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int path, int pos)
{
    // string space = "                                       ";
    string color = "";
    int player = 0;
    int whichplayer = -1;
    for (int i = 0; i < _player_count; i++){
     if (isPlayerOnTile(i, pos, path ) == true){
        player++;
        whichplayer = i;
     }
    }
    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[path][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[path][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[path][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[path][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[path][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[path][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[path][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[path][pos].color == 'Y')
    {
        color = GREY;
    }
    else if (_tiles[path][pos].color == 'I')
    {
        color = SAFARI;
    }
    else if (_tiles[path][pos].color == 'K')
    {
        color = EXILE;
    }


    //check if any instance of isplayerontile is true

     if (player > 0 )
    {
        if (pos > 0){
        cout << color << "|" << lion[whichplayer].geticon() << "|" << RESET;
        }else{
            cout << color << "|";
            for(int i = 0; i < 4; i++){
                
                if(lion[i].pPos == pos && lion[i].pLane == path && lion[i].geticon() != ' '){
                    cout<<lion[i].geticon();
                }
                
            }
            cout<< "|" << RESET;
        }
    }
    else
    {
    
        cout << color << "| |" << RESET;
    }

    

}

void Board::displayTrack(int dtrack)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(dtrack, i);
       
    }
    cout <<RESET<<"                                                                                                                           "<< endl;
}

void Board::displayBoard()
{
    int thislane = 0;
    string lanename = "";
     
    for (int i = 0; i < 3; i++)
    {
         thislane = i;
        switch (thislane){
     case 0: lanename = "Cub Training->";
     break;
     case 1: lanename = "Pride Lands->";
     break;
     case 2: lanename = "Wild Lands!->";
     }
       
        cout<<lanename;
        displayTrack(i);
        if (i == 0 || i == 1) {
            cout << endl;  // Add an extra line between the two lanes
        }
    }
}




 bool Board::movePlayer(int player_index, int movementinc)
 {
     // Increment player position
     
    lion[player_index].pPos+= movementinc;

    bool isfight =iscrossover(player_index);
    if (!isfight){
        specialtile(player_index, lion[player_index].pPos, lion[player_index].pLane,movementinc);

    }

     if (lion[player_index].pPos == _BOARD_SIZE - 1)
     {
         // Player reached last tile
        lion[player_index].reachedend = true;
        message = message = "Player " + to_string(player_index + 1) + " has reached the end!";
        firsttofinish[winners] = player_index;
        winners++;
        return true;
    
    
     }else if(lion[player_index].pPos > _BOARD_SIZE - 1){
        lion[player_index].pPos -= (movementinc);
        message = "Player " + to_string(player_index + 1) + " reached the end but went too far! Try again!";
     }
     return false;
 }

 int Board::getPlayerPosition(int player_index) const
 {
     if (player_index >= 0 && player_index <= _player_count)
     {
         return lion[player_index].pPos;
     }
     return -1;
 }

int Board::getPlayerLane(int player_index) const{

 if (player_index >= 0 && player_index <= _player_count)
     {
         return lion[player_index].pLane;
     }
     return -1;

}

void Board::placePlayer(int player_index, int pos, int whichlane){

lion[player_index].pPos = pos;
lion[player_index].pLane = whichlane;
if(pos > 0){
    iscrossover(player_index);
}

}
char Board::checkTile(int pos, int whichlane){

return _tiles[whichlane][pos].color;


}

void Board::moveBack(int playa, int increment){

if(lion[playa].pPos - increment >= 0){

lion[playa].pPos -= increment;
iscrossover(playa);

}else{
    lion[playa].pPos = 0;
}


}



bool Board::iscrossover(int whichplayer){
    for ( int i = 0; i < _player_count; i++ ){
        if (lion[whichplayer].pPos == lion[i].pPos && i != whichplayer && lion[whichplayer].pLane == lion[i].pLane){
                if (lion[i].reachedend == false){
                fight(whichplayer, i);
                }
            return true;

        }
        
    }
    return false;
}
void Board::fight(int fighter1, int fighter2){
    //my own personal feature, huge fan of this one. My goal is since there are multiple lanes and up to 4 players,
    //choosing a lane by yourself might be smart as there is less competition, but choosing the same as others is a bit more of a gamble
    //i feel like more gambling within the game = more fun.
int fightwinner = 0;

int sumfighter1 = (lion[fighter1].getstamina() + lion[fighter1].getstrength() + lion[fighter1].getwisdom());

int sumfighter2 = (lion[fighter2].getstamina() + lion[fighter2].getstrength() + lion[fighter2].getwisdom());



if (sumfighter1 >= sumfighter2){
    moveBack(fighter2, 5);
    lion[fighter1].modify(3, 5000);
    lion[fighter2].modify(3, -5000);
    message ="Player " + to_string(fighter1+1)+" has defeated Player "+to_string(fighter2 + 1)+" in a fight! They have taken 5000 Pride Points from them!";
    fightwinner = 1;
}else{
    moveBack(fighter1, 5);
    lion[fighter2].modify(3, 5000);
    lion[fighter1].modify(3, -5000);
    message ="Player " + to_string(fighter2+1)+" has defeated Player "+to_string(fighter1 + 1)+" in a fight! They have taken 5000 Pride Points from them!";
    fightwinner = 2;
}

}

void Board::startgame(int whichplaya){
    
    lion[whichplaya].pPos = 0;
cout<<"SELECT A LION"<<endl;
for (int i = 0; i < 8; i++){
    
    printstats(characters, i);
    cout<<"------------------------------------------------------------"<<endl;
}
int choice = 0;
cin>>choice;

bool validpick = false;
while (!validpick){
    if (choice < 1 || choice > 8){
        cout<<"Invalid input. Please enter a valid number."<<endl;
        cin>>choice;
    }
    bool ischaravailable = true;
    for(int i = 0; i < 4; i++){
        if(choice == lion[i].character){
            ischaravailable = false;

        }

    }
    if (!ischaravailable){
        cout<<"Character is already taken. Please select a new one."<<endl;
        cin>>choice;
    }else{
        validpick = true;
    }
}

lion[whichplaya].setname(characters[choice-1].name);
lion[whichplaya].setage(characters[choice-1].age);
lion[whichplaya].setstrength(characters[choice-1].strength);
lion[whichplaya].setstamina(characters[choice-1].stamina);
lion[whichplaya].setwisdom(characters[choice-1].wisdom);
lion[whichplaya].setpridepoints(characters[choice-1].pridepoints);
lion[whichplaya].seticon(characters[choice-1].icon);
lion[whichplaya].character = characters[choice-1].charnumber;

cout<<"CHARACTER CHOSEN: "<<characters[choice - 1].name<<" ICON: "<<characters[choice - 1].icon<<endl;
cout<<"------------------------------------------------------------"<<endl;

choice = 0;
 cout<<"CHOOSE YOUR STARTING LANE"<<endl;
 cout<<"Lane 1- Cub Training! Begin with an advisor as well as a small boost to all of your leadership traits in a mostly calm grassy path."<<endl;
 cout<<endl;
cout<<"Lane 2- Pride Lands! Begin with a boost to pride points but no advisor in a path filled with more obstacles but also more boosts."<<endl;
cout<<endl;
cout<<"Lane 3- Wild Lands! Begin with a large boost to leadership traits & less pride points in a challenging path with lots of special tiles, both good and bad. Is it worth the gamble?"<<endl;
cout<<endl;

cin>>choice;
while(choice < 1 || choice > 3){
    cout<<"Enter a valid option."<<endl;
    cin>>choice;

}
cout<<"LANE CHOSEN: ";

switch (choice){

case 1: 
cout<<"1- CUB TRAINING"<<endl;
cout<<"------------------------------------------------------------"<<endl;
lion[whichplaya].traincub();
lion[whichplaya].pLane = 0;

choice = 0;

cout<<"CHOOSE YOUR ADVISOR"<<endl;
for (int i = 0; i<6; i++){
printadvisors(advisors, i);
}
    cin>>choice;
    while (choice < 1 || choice > 6){
    cout<<"Please enter a valid choice."<<endl;
    cin>>choice;
}
lion[whichplaya].setadvisor(choice);
cout<<"ADVISOR CHOSEN: "<<advisors[choice-1].name<<endl;
if (choice == 6){
    lion[whichplaya].modify(3, -10000);
}
break;
case 2:
cout<<"2- PRIDELANDS"<<endl;
cout<<"------------------------------------------------------------"<<endl;
lion[whichplaya].topridelands();
lion[whichplaya].pLane = 1;
break;
case 3:
cout<<"3- WILDLANDS"<<endl;
cout<<"------------------------------------------------------------"<<endl;
lion[whichplaya].towildlands();
lion[whichplaya].pLane = 2;
break;

}
choice = 0;
message  = "[Recent Events will Appear Here]";
}

void Board::grasseffects(int affectswho){
srand(time(NULL));
int isevent = rand() % 3;
if (isevent > 0){
    srand(time(NULL));
    int whichevent = rand() % 70;
    
        if (events[whichevent].affect < 0){//negative events
        message = events[whichevent].description+"!";
            if(lion[affectswho].getadvisor() != events[whichevent].advisor ){
                lion[affectswho].modify(3, events[whichevent].affect);
                message +=" Player " + to_string(affectswho + 1) + " Loses "+ to_string(abs(events[whichevent].affect)) +" pride points.";
            }else{
                message += " But " + advisors[lion[affectswho].getadvisor()].name + " prevented harm!";
            }


        }else{
            if (events[whichevent].advisor == 6){
                if(lion[affectswho].getadvisor() == 6){
                message = events[whichevent].description + "! Player " + to_string(affectswho + 1) +  " Gains " + to_string(events[whichevent].affect)+" pride points.";
                lion[affectswho].modify(3,events[whichevent].affect);
                }

            }else{
                message = events[whichevent].description + "! Player " + to_string(affectswho + 1) +  " Gains " + to_string(events[whichevent].affect) +" pride points.";
                lion[affectswho].modify(3,events[whichevent].affect);
            }

        }




}
else{
    message = "Player " + to_string(affectswho + 1) +" has an uneventful day.";
}
}
bool Board::runriddle(){
    srand(time(NULL));
    int riddlenumb = rand() % 27;
    string response;
    string riddleanswer = riddles[riddlenumb].answer;
    cout<<riddles[riddlenumb].question<<endl;
    cin>>response;
    if (response == riddleanswer){
        return true;
    }
    return false;

}
void Board::specialtile(int playerindex, int pos, int lane, int lastmove){
    char EFFECT = checkTile(pos, lane);
    switch(EFFECT){
        case 'G':
            grasseffects(playerindex);
            break;

        case 'R':
        message = "Player "+ to_string(playerindex + 1) + " stumbled into a Graveyard!";
            if(lion[playerindex].getadvisor() != 6){
                if(lane == 2){
                moveBack(playerindex, 3); //i was playing thru and kept getting completely stuck in wild lands cus of the
                message += " They have moved 3 spots back and ";
                }else{
                moveBack(playerindex, 10);
                message += " They have moved 10 spots back and ";
                }
                lion[playerindex].modify(0,-100);
                lion[playerindex].modify(1,-100);
                lion[playerindex].modify(2,-100);
                message += "lost 100 Strength, Stamina and Wisdom!";
                
                break;
                
            }else{
                message +=" But Scar has prevented any Harm!";
            }
            //cout thing
            break;
        case 'N':
         message = "Player "+ to_string(playerindex + 1) + " ran into a pack of Hyenas!";
            if(lion[playerindex].getadvisor() != 6){
                placePlayer(playerindex, pos - (lastmove), lane);
                lion[playerindex].modify(1,-300);
                message += "They are back to their original spot with 300 less stamina!";
               
                break;
            }else{
                message +=" But Scar ordered them away!";
            }
            break;
        case 'K':
            lion[playerindex].modify(3, -1000);
            placePlayer(playerindex, pos, 2);
            message = "Player " + to_string(playerindex + 1) + " has been Exiled! They have lost 1000 Pride Points!";
            break;
        case 'U': {
            bool iscorrect = runriddle();
            if (iscorrect){
                lion[playerindex].modify(2, 1000);
                message = "Player " + to_string(playerindex + 1) +" has answered the riddle correctly! They gained 1000 Wisdom!";
            }else{
                lion[playerindex].modify(2,-200);
                 message = "Player " + to_string(playerindex + 1) +" has answered the riddle wrong! They lost 200 Wisdom!";
            }
            break;
        }
        case 'I':
            lion[playerindex].modify(0,100);
            lion[playerindex].modify(1,100);
            lion[playerindex].modify(2,100);
            message = "Player " + to_string(playerindex + 1) +" relaxes on the safari. They gained 100 Strength, Stamina, and Wisdom!";
            break;
        case 'B':
            lion[playerindex].modify(0,300);
            lion[playerindex].modify(1,300);
            lion[playerindex].modify(2,300);
            message = "Player " + to_string(playerindex + 1) +" recharges at the oasis! They gained 200 Strength, Stamina, and Wisdom!";
            break;
        case 'P':
            if (lion[playerindex].getadvisor() > 0){
                lion[playerindex].modify(0,300);
                lion[playerindex].modify(1,300);
                lion[playerindex].modify(2,300);
                message = "Player " + to_string(playerindex + 1) +" learned from their Advisor! They gained 300 Strength, Stamina, and 500 Wisdom!";
            }else{
                lion[playerindex].modify(0,300);
                lion[playerindex].modify(1,300);
                lion[playerindex].modify(2,500);
                cout<<"You've landed on advisor tile! Choose your Advisor:"<<endl;
                int choice = 0;
                for (int i = 0; i<6; i++){
                    printadvisors(advisors, i);
                }
                cin>>choice;
                while (choice < 1 || choice > 6){
                    cout<<"Please enter a valid choice."<<endl;
                    cin>>choice;
                }
                lion[playerindex].setadvisor(choice);
                cout<<endl;
                cout<<"ADVISOR CHOSEN: "<<advisors[choice-1].name<<endl;
                cout<<endl;
                if (choice == 6){
                lion[playerindex].modify(3, -10000);
}
                //cout thing
            
            }
            break;
            //ORANGE TILE?
            //GREY TILE? both maybes, i plan on only using special tile for when the player moves, rather than when it is placed, so therefore the character doesn't
            //get stuck in loops of moving backwards and doesn't get double negative effects and/or flood the event system
            default:
            break;

    }
}


void Board::calculatewinner(int numplayers, Places places[]){
    int playerscores[4] = {0, 0, 0, 0};
        for (int i = 0; i < numplayers; i++){
            places[i].initialize();
            places[i].score = calculatePP(firsttofinish[i]) * (1 + (numplayers - i)*25/100 );
            places[i].playerindex = firsttofinish[i];

        }  
       int currentmax = 0;
    for (int i = 1; i < numplayers; i++) {
        if (places[i].score > places[currentmax].score) {
            currentmax = i;
        }
    }
    if (currentmax != 0) {
        Places temp = places[0];
        places[0] = places[currentmax];
        places[currentmax] = temp;
    }
    
    for (int i = 1; i < numplayers - 1; i++) {
        for (int j = 1; j < numplayers - i; j++) {
            if (places[j].score < places[j + 1].score) {
                Places temp = places[j];
                places[j] = places[j + 1];
                places[j + 1] = temp;
        }
    }
    }
}

void Board::calculateleader(int numplayers, Places places[]){//same code for both, just without the little multiplier thing as this is meant for mid-round
        
        for (int i = 0; i < 4; i++){
            places[i].initialize();
            if (lion[i].geticon() != ' '){//had a really annoying bug for one player, where check leader would say player 2 with like 2029202920 points, this fixes it though.
            places[i].score = calculatePP(i);
            }
            places[i].playerindex = i;
            


        }  
        int currentmax = 0;
    for (int i = 1; i < numplayers; i++) {
        if (places[i].score > places[currentmax].score) {
            currentmax = i;
        }
    }
    if (currentmax != 0) {
        Places temp = places[0];
        places[0] = places[currentmax];
        places[currentmax] = temp;
    }
    for (int i = 1; i < numplayers - 1; i++) {
        for (int j = 1; j < numplayers - i; j++) {
            if (places[j].score < places[j + 1].score) {
                Places temp = places[j];
                places[j] = places[j + 1];
                places[j + 1] = temp;
        }
    }
    }
}

       


int Board::calculatePP(int playerindex){

int sumplayer = 0.5 *( 2.5 * (lion[playerindex].getwisdom() + lion[playerindex].getstrength() + lion[playerindex].getstamina()) + 3 * lion[playerindex].getpridepoints());
return sumplayer;
}




    
