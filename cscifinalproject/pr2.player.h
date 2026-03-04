#ifndef player_h
#define player_h

#include <iostream>
#include <string>
using namespace std;

class player{
private:
string name;
int strength, stamina, wisdom, pridepoints, age;
char icon = ' ';
int advisor = 0;


public:
player();
player(string nam, int strengt, int stamin, int wisdo, int pridepoint, int ag, char ico, int advisor);
int pPos;
int pLane;
int character;
string getname();
int getstrength();
int getstamina();
int getwisdom();
int getpridepoints();
int getage();
void setname(string nam);
void setstrength(int strengt);
void setstamina(int stamin);
void setwisdom(int wisdo);
void setpridepoints(int pridepoint);
void setage(int ag);
void traincub();
void topridelands();
void towildlands();
void printstats();
void seticon(char);
char geticon();
void setadvisor(int which);
int getadvisor();

void modify(int what, int howmuch);

bool reachedend;
void initializelionz();



};
#endif