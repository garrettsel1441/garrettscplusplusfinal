#include "pr2.interface.h"
Menu::Menu(){
Board GAME(0);
}
Menu::Menu(int numplayers){
    Board GAME(numplayers);
    bool gameisover = false;
    bool quit;
    for(int i = 0; i < numplayers; i++){
        cout<<endl;
        cout<<endl;
        cout<<"PLAYER "<<i + 1<<": "<<endl;
        GAME.startgame(i);
    }
    while(GAME.winners < numplayers){//whole game goes in here

        for (int i = 0; i < numplayers; i++){
            if (!GAME.lion[i].reachedend){
                
                displaymenu(i, GAME);

            }
        }


    }
    gameOver(GAME, numplayers);

}
void Menu::displaymenu(int whoseturn, Board& THIS){
    cout<<endl;
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    cout<<"PLAYER "<<whoseturn + 1<<"'S TURN"<<endl;
    cout<<endl;
    THIS.displayBoard();
    cout<<endl;
    cout<<THIS.message<<endl;
    cout<<endl;
    int choose = 0;
    while(choose != 1){
    cout<<"-------------------------PLAYER "<<whoseturn + 1<<"-------------------------"<<endl;
    cout<<"1- Go Forward || 2- Check Character || 3- Tile & Game Info"<<endl;
    cin>>choose;
    while(choose < 1 || choose > 3){
        if (choose != 9){
        cout<<"Invalid input. Please enter a valid option."<<endl;
        cin>>choose;
        }
    }
    int playermove = 0;
    switch(choose){
        case 1:
            playermove= goforward(whoseturn, THIS);
            cout<<"PLAYER "<<whoseturn + 1<<" ";
            if(playermove>= 0){
            cout<<"MOVED FORWARD ";
            }else{
                cout<<"MOVED BACKWARD ";
            }
            cout<<abs(playermove)<<" TILES"<<endl;
            break;
        case 2:
            checkcharacter(whoseturn, THIS);
            break;
        case 3:
            getInfo(THIS);
            break;
            
        case 9:
           
            for(int i = 0; i < 4; i++){
                THIS.lion[i].reachedend = true;
            }
            break;
    }
}
return;
}
int Menu::goforward(int playerindex, Board& THAT){
    int movementinc = 0;
     srand(time(NULL));
     movementinc = (rand() % 6) + 1;
    int originalspot = THAT.lion[playerindex].pPos;
    cout<<"Rolled a "<<movementinc<<"!"<<endl; //wanted to implement a dice- type thing, it annoyed me rolling and then just immediately seeing what happens. 1.5 seconds is like how long it takes to see dice roll too, probably
sleep_for(1.5s);
THAT.movePlayer(playerindex, movementinc);

return THAT.lion[playerindex].pPos - originalspot;

}
void Menu::checkcharacter(int playerindex, Board& SAME){
    int choice = 0;
    cout<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    SAME.lion[playerindex].printstats();
    if (SAME.lion[playerindex].getadvisor() > 0){
    cout<<"ADVISOR: "<<SAME.advisors[SAME.lion[playerindex].getadvisor()-1].name<<endl;
    }else{
        cout<<"ADVISOR: NONE"<<endl;
    }
    cout<<"[1 Advisor Description] [2 Your spot on the leaderboard] [3 Current leader] [4 Exit]"<<endl;
    cin>>choice;
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
        cout<<"Please enter a valid number"<<endl;
        cin>>choice;
    }

    switch (choice){
        case 1:{
            if (SAME.lion[playerindex].getadvisor() > 0){
            cout<<SAME.advisors[SAME.lion[playerindex].getadvisor()-1].name<<"- "<<SAME.advisors[SAME.lion[playerindex].getadvisor()-1].description<<endl;
            }else{
                cout<<"NONE- You can get choose an advisor after landing on a pink 'Advisor' tile!"<<endl;
            }
            break;
        }
        case 2:{
            int spot = 0;
            Places here[4];
            SAME.calculateleader(4,here);
            for (int i = 0; i < 4; i++){
                if(playerindex == here[i].playerindex){
                    spot = i;
                }
            }
            cout<<"You are number "<<spot + 1<<" on the leaderboard with "<<here[spot].score<<" Total Points!"<<endl;
            break;
        }
        case 3:{
            Places here[4];
            SAME.calculateleader(4,here);
            cout<<"Current Leader: PLAYER "<<here[0].playerindex + 1<<" || Total Points: "<<here[0].score<<endl;
            break;
        }
        case 4:{
            return;
        }
    }
    cout<<"------------------------------------------------------------"<<endl;
}
void Menu::getInfo(Board& HERE){
    int choice = 0;
    cout<<endl;
    cout<<endl;
    cout<<"Enter 2 to read game info, 3 to read tile info, and 1 to exit info."<<endl;
    cin>>choice;
    while(choice != 2 && choice != 3 && choice != 1){
        cout<<"Please enter a valid number."<<endl;
        cin>>choice;
    }
    if(choice == 2){
    cout<<endl;
    cout<<endl;
    cout<<"You can end the game at any time by entering 9."<<endl;
    cout<<"The game is determined by calculating final pride points from leadership traits pride points, which will change from the beginning of the game to the end."<<endl;
    cout<<"The first players to arrive at the end get a bonus multiplier onto their final pride points, so it helps to finish quickly."<<endl;
    cout<<"Upon all players reaching the end, the winner is calculated from who has the most  final pride points."<<endl;//game summary
    cout<<"Each path provides many opportunities to both gain and lose pride points, with the paths getting riskier as you go down."<<endl;
    cout<<"Each character starts with a beginning number of leadership traits and pride points, which will change as the game goes on."<<endl;
    cout<<"Advisors are chosen by the player and grant them a special immunity to certain tiles/events."<<endl;
    cout<<"Be careful when travelling on the same path as another player."<<endl;
    cout<<"When landing on the same tile as another player it will start a fight, in which the loser is sent back 5 spaces and the winner takes 2000 pride points from them."<<endl;
    cout<<"Fights are determined by the sum of Leadership Traits."<<endl;
    cout<<"There are many different paths which could win the game and to win requires both strategy and luck. Long Live the King!"<<endl;
    cout<<endl;
    }else if(choice == 3){
    for (int i  = 0; i < 10; i++){
        cout<<HERE.tileinfo[i]<<endl;
    }
    }else{
        return;
    }
    

    }

void Menu::gameOver(Board &GAME, int numplayers){
    ofstream log("gamelog.txt");

    Places places[4];

    for(int i = 0; i < 4; i++){
        places[i].initialize();
    }
    GAME.calculatewinner(numplayers, places);
    string rank = "";
    if (places[0].score > 100000){
        rank = "LION KING!";
    }else if (places[0].score > 75000){
        rank = "MUFASA";
    }else if (places[0].score > 50000){
        rank = "SIMBA";
    }else if (places[0].score > 30000){
        rank ="SCAR";
    }else{
        rank = "PUMBA";
    }
    cout<<endl;
    cout<<endl;
    cout<<"PLAYER "<<(places[0].playerindex)+1<<" WINS!"<<endl;
    cout<<endl;
    for (int i = 0; i < numplayers; i++){
        cout<<"NUMBER "<<(i+1)<<": PLAYER "<<(places[i].playerindex)+1<<endl;
        cout<<"FINAL PRIDE POINTS: "<<places[i].score<<endl;
        if(i == 0){
        cout<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<"RANK ACHEIVED: "<<rank<<endl;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout<<endl;
        }
        cout<<endl;
    }

////////////////////////////////////////////////////log into game file
    log<<endl;
    log<<endl;
    log<<"PLAYER "<<(places[0].playerindex)+1<<" WINS!"<<endl;
    log<<endl;
    for (int i = 0; i < numplayers; i++){
        log<<"NUMBER "<<(i+1)<<": PLAYER "<<(places[i].playerindex)+1<<endl;
        log<<"FINAL PRIDE POINTS: "<<places[i].score<<endl;
        if(i == 0){
        log<<endl;
        log<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        log<<"RANK ACHEIVED: "<<rank<<endl;
        log<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        log<<endl;
        }
        log<<endl;
    }
    log.close();

}


    

int main(){
    cout<<endl;
    cout<<endl;
    cout<<"Welcome to the Lion King: the Circle of Life!"<<endl;
    cout<<endl;
    cout << "                               ccc  c  c  ccc                                " << endl;
    sleep_for(50ms);
    cout << "                               $   $cc$  $==                                " << endl;
    sleep_for(50ms);
    cout << "                               $   $  $  $cc                                " << endl;
    sleep_for(50ms);
    cout << "=ccr=    ========================================================  _,r====c, " << endl;
    sleep_for(50ms);
    cout << " )$F     =cc= ,z=\"\"?b, `$c.     3$\"    \"$P\" \"$P\" \"3$\" \"$c,    \"$\" cP\"     `$ " << endl;
    sleep_for(50ms);
    cout << " )$F      $$ zP      ?b $F?b,   3$      $$,\"     3$   $\"?c,   $ z$         " << endl;
    sleep_for(50ms);
    cout << " )$F      $$<$F       $>$F  ?b, 3$      $$C       3$   $  \"?c  $ $$     ,,,, " << endl;
    sleep_for(50ms);
    cout << " )$F      $$ ?b      z$'$F   `?bJ$      $$`\"c,    3$   $    \"?c$ `$L      $$ " << endl;
    sleep_for(50ms);
    cout << ",J$L,,,c\" $$  \"b,..,cP' $L     `?P      $$   ?b,  3$   $      \"$  `?c,,.,,P\" " << endl;
    sleep_for(50ms);
    cout << "`\"\"\"\"\"\"' `\"\"'   \"\"\"\"   `\"\"      `'     \"\"\"\"  \"\"\" `\"\"' \"\"\"      \"    `\"\"\"\"\"\" " << endl;
    sleep_for(50ms);
    cout << "                               . , ,                                         " << endl;
    sleep_for(50ms);
    cout << "                            \\,c$$P??i?=,                                     " << endl;
    sleep_for(50ms);
    cout << "                    ,d$$\"zd$$PF?i<$$$i$$$$c                                  " << endl;
    sleep_for(50ms);
    cout << "                    $$$\"d$$$Lh$?CJ$$$$$$$$$$c                                " << endl;
    sleep_for(50ms);
    cout << "                    `$'cc`$$$$$$$$$$$$$$$$$$$r.,                             " << endl;
    sleep_for(50ms);
    cout << "                     F`,,\"?$$$$$$$P\",ccc\"$$$$$ $$$$c                         " << endl;
    sleep_for(50ms);
    cout << "                    ,'=\"`\"J$$$$$$\",;,,\"$L?$$$$`$$$$$                         " << endl;
    sleep_for(50ms);
    cout << "                   .$b,_,c$$$$$$'/\"`?$c $ $$$FJ$$$$\"                         " << endl;
    sleep_for(50ms);
    cout << "                   )$$P:-`?????'.    ?\".\" \",,\"\"?\"                           " << endl;
    sleep_for(50ms);
    cout << "                .,.\"$$$$c,,,,,c$$$bcc-,z$$$$$$$$,                            " << endl;
    sleep_for(50ms);
    cout << "            ,c$$$$$$c`?$$????$$$$$$\",$$$$$$$$$P\",                            " << endl;
    sleep_for(50ms);
    cout << "          ,$$$$$$$$$$$,\";chhcJ$F\"`\"$$$$>P\"                              " << endl;
    sleep_for(50ms);
    cout << "          4,\"?$$$$$$P\"\"d ,,\"\"\"\".\"'''\"-3$$L<$$F,;!                            " << endl;
    sleep_for(50ms);
    cout << "          `$$`cccc,<$$$'J$$$$ !!!!!!!'---->;;!!                              " << endl;
    sleep_for(50ms);
    cout << "            \"-$$$$P`??\",$$$$$P';;;;!!!!!!!!!!!                               " << endl;
    sleep_for(50ms);
    cout << "            <>;;;;                                                           " << endl;
    sleep_for(50ms);
    cout << "             ::!!!! $$$$$$\",cchhhcF\"J$$$$$ !!!!;                             " << endl;
    sleep_for(50ms);
    cout << " z4$ $e   ,ccc,\"',d,c cb-,\"?$$$$$$c`$$$$$                                  " << endl;
    sleep_for(50ms);
    cout << "$$4$L\"??, 4$$$$$.$P $$'$P,$$,?$$$$$$$$$$$F  `!!!!!                           " << endl;
    sleep_for(50ms);
    cout << ")P.,c$$$c4c\"$$$FJ$,b`P-?,$$P\" $$$$$$$$$$$     ``'!!!,                        " << endl;
    sleep_for(50ms);
    cout << ".$$$$$$$,\"c3$$F<$$ cd$$$c c$>$$$$$$$$$$P        `                            " << endl;
    sleep_for(50ms);
    cout << "    \"$ $$$ $$$.?$$,?$$$$F<$$<$$$$$$$$F             `!!!!!;,                " << endl;
    sleep_for(50ms);
    cout << "     `$$$$,$ $$$>,\"?? $$$$F<$$<$$$$$$F                `!!!!!!>;,            " << endl;
    sleep_for(50ms);
    cout << "      ?$$$ $P\"  `!!!!>?$$$>d$P<$$P\"                     ;,             " << endl;
    sleep_for(50ms);
    cout << "       \"$\".\"     `!!!>`$$$,$$-,ccr\"                      `!!!!!!!!!!!>,     " << endl;
    sleep_for(50ms);
    cout << "                  !!!;<$$'dF  $$F                              $                              `` " << endl;
    sleep_for(50ms);
    cout << "                   ,!!!!!!!!!!>         nMMMMM'?``))\"$\"``))`?>!!!!!!!!!!!'  < " << endl;
    sleep_for(50ms);
    cout << "                   ,,!!!!!!!!!!,       \"\"\"MMMP:-=<))<.,,J;): !!!!!!!!!!     " << endl;
    sleep_for(50ms);
    cout << "                    ``'!!!!!!!!!! .     ,r\"',c$c=:::,,`\"\"=: ;!!!!!!!!',     " << endl;
    sleep_for(50ms);
    cout << "                        ` \"MMMMf<$$P\"\"--,c$$$$$$$$F!!!!!!!!!;MMn,          " << endl;
    sleep_for(50ms);
    cout << "                          `'!!!!`.MMMMMP .:,cF:: $$$$$$$$$$\"!!!!!!!! MMMMM, " << endl;
    sleep_for(50ms);
    cout << "                            ``!  .MMMM c.::':::: $$$$??$$P' !!!!!!!'4MMMML\" " << endl;
    sleep_for(50ms);
    cout << "                              `'JMMM\",c'`:','c`:',$$$\",dr\"xP,!!!!!!!,MMMMMM> " << endl;
    sleep_for(50ms);
    cout << "                               .MMM\"c$F,d$$$bc$$P\",c$$\"dMM !!!!!!! dMMMM4Mb " << endl;
    sleep_for(50ms);
    cout << "                                M>.\"\"\" $$$$$$P\",c$$$$F,MMP'!!!!!!!,MMMMM  \" " << endl;
    sleep_for(50ms);
    cout << "                                \"M,?$$$ccccccP??\",nnnMMMM !!!!!!!>dMMMMM>   " << endl;
    sleep_for(50ms);
    cout << "                                 )Mn`???????,dMMMMMMMMMP MMMMMMM           " << endl;
    sleep_for(50ms);
    cout << "                                 MMMMbbnMMMMMMMMMMMMMMM !!!!!!!!! MMMMMMM   " << endl;
    sleep_for(50ms);
    cout << "                               dMMMMMMMMMMMMMMMMMMMMMM 4                       " << endl;
    sleep_for(50ms);
    cout << "                              4MMMMMMMMMMMMMMMMMMMMMMM,!!!!!!!!! MMMMMMf      " << endl;
    sleep_for(50ms);
    cout << "                              `MMM\"MMMMMMMMMMMMMMMMM\"'!!!!!!!!!!,MMMMM'       " << endl;
    sleep_for(50ms);
    cout << "                               MM' MMMMMMMMMMMMMMP,u;';!!!!!!!',MMMP)\\        " << endl;
    int amtplyrs;
    cout<<endl;
    cout<<"Please enter how many players there are. MAXIMUM: 4"<<endl;
    cin>>amtplyrs;
    if(amtplyrs > 0 && amtplyrs < 5){
    Menu PLAY(amtplyrs);
    }
    while (amtplyrs < 1 || amtplyrs > 4){
        cout<<"Please enter a valid number of players. (1-4)"<<endl;
        cin>>amtplyrs;
        if(amtplyrs > 0 && amtplyrs < 5){
            Menu PLAY(amtplyrs);
        }
    }



    cout<<"Thank you for playing!"<<endl;
    return 0;
}

//play game by entering g++ pr2.interface.cpp pr2.board.cpp pr2.player.cpp -o game
