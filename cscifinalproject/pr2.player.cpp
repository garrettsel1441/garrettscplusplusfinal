#include "pr2.player.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

player::player(){

    name = "";
    strength, stamina, wisdom, pridepoints, age, advisor = 0;
    icon = ' ';
    reachedend = false;
}

player::player(string nam, int strengt, int stamin, int wisdo, int pridepoint, int ag, char ico, int adviso){

    name = nam;
    strength = strengt;
    stamina = stamin;
    wisdom = wisdo;
    pridepoints = pridepoint;
    age = ag;
    icon = ico;
    advisor = adviso;
    reachedend = false;



}
string player::getname(){
    return name;
}
int player::getstrength(){
    return strength;
}
int player::getstamina(){
    return stamina;
}
int player::getwisdom(){
    return wisdom;
}
int player::getpridepoints(){
    return pridepoints;
}
int player::getage(){
    return age;
}
void player::setname(string nam){
    name = nam;
}
void player::setstrength(int strengt){
    strength = strengt;
}
void player::setstamina(int stamin){
    stamina = stamin;
}
void player::setwisdom(int wisdo){
    wisdom = wisdo;
}
void player::setpridepoints(int pridepoint){
    pridepoints = pridepoint;
}
void player::setage(int ag){
    age = ag;
}
void player::traincub(){
    strength += 2000;
    stamina += 2000;
    wisdom += 2000;
    pridepoints -= 5000;
}
void player::topridelands(){
    pridepoints += 5000;
    strength += 200;
    wisdom += 200;
    stamina += 200;
}
void player::towildlands(){
    pridepoints = sqrt(pridepoints);
    strength += 4000;
    wisdom += 4000;
    stamina += 4000;


}
void player::printstats(){
    cout<<name<<", age "<<age<<endl;
    cout<<strength<<" strength."<<endl;
    cout<<wisdom<<" wisdom."<<endl;
    cout<<pridepoints<<" pride points."<<endl;
    cout<<stamina<<" stamina."<<endl;
    cout<<endl;

}

void player::modify(int which, int value){

switch (which){

case 0: //strength
strength += value;
if (strength <= 100){
    strength = 100;
}
break;

case 1: //stamina
stamina += value;
if (stamina <= 100){
    stamina = 100;
}
break;

case 2: //wisdom
wisdom += value;
if (wisdom <= 100){
    wisdom = 100;
}
break;

case 3: //pridepoints
pridepoints += value;
if (pridepoints <= 100){
    pridepoints = 100;
}
break;

case 4: //age
age += value;
break;
}





}

void player::seticon(char towhat){
    icon = towhat;
}
char player::geticon(){
    return icon;
}
int player::getadvisor(){
return advisor;
}
void player::setadvisor(int which){
    advisor = which;
}
void player::initializelionz(){
    name = "";
    strength = 0;
    stamina = 0;
    wisdom = 0;
    pridepoints = 0;
    age = 0;
    icon = ' ';
    advisor = 0;
    reachedend = false;
}