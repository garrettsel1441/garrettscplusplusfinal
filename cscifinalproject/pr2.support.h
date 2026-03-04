#ifndef support_h
#define support_h
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Advisors{
public:

int number;

string name;

string description;




};
inline void uploadadvisors(string& filename, Advisors advisors[]){

ifstream file(filename);
string line;
    int count = 0;

    while (getline(file, line) && count < 6) {
        istringstream thisline(line);
        //split each instance of line into stringstream in order to track where in the file to pick up from for the next instance
        string name, numberStr, description;

        if (getline(thisline, name, '|') &&
            getline(thisline, numberStr, '|') &&
            getline(thisline, description)) {

            
            advisors[count].name = name;//populate advisors array
            advisors[count].number = stoi(numberStr);
            advisors[count].description = description;

            count++;
        }
    }

    file.close();


}
struct Characters{
public:

int strength;
int stamina;
int wisdom;
int pridepoints;
int age;
char icon;
int charnumber;

string name;





};

inline void uploadcharacters(string& filename, Characters characters[]){ //copy pretty much the whole function

ifstream file(filename);
string line;
    int count = 0;

    while (getline(file, line) && count < 8) {
        istringstream thisline(line);
        //split each instance of line into stringstream in order to track where in the file to pick up from for the next instance
        string charnmbrstr,name, agestr, strengthstr,staminastr,wisdomstr,iconstr,pridepointstr;

        if (getline(thisline, charnmbrstr, '|')&&
            getline(thisline, name, '|') &&
            getline(thisline, agestr, '|') &&
            getline(thisline, strengthstr, '|') &&
            getline(thisline, staminastr, '|') &&
            getline(thisline, wisdomstr, '|') &&
            getline(thisline, iconstr, '|') &&
            getline(thisline, pridepointstr)) {

            
            characters[count].charnumber = stoi(charnmbrstr);
            characters[count].name = name;//populate advisors array
            characters[count].age = stoi(agestr);
            characters[count].strength = stoi(strengthstr);
            characters[count].stamina = stoi(staminastr);
            characters[count].wisdom = stoi(wisdomstr);
            characters[count].icon = iconstr[0];
            characters[count].pridepoints = stoi(pridepointstr);

            count++;
        }
    }

    file.close();


}
struct Event{
public:

int advisor;

string name;

string description;

int affect;




};
inline void uploadevents(string& filename, Event events[]){

ifstream file(filename);
string line;
    int count = 0;

    while (getline(file, line) && count < 70) {
        istringstream thisline(line);
        //split each instance of line into stringstream in order to track where in the file to pick up from for the next instance
        string affectstr, advisorstr, descriptionstr;

        if (getline(thisline, descriptionstr, '|') &&
            getline(thisline, advisorstr, '|') &&
            getline(thisline, affectstr)) {

            
            events[count].description = descriptionstr;//populate advisors array
            events[count].advisor = stoi(advisorstr);
            events[count].affect = stoi(affectstr);

            count++;
        }
    }

    file.close();


}
struct Riddle{

string question;

string answer;

};
inline void uploadriddles(string& filename, Riddle riddles[]){

ifstream file(filename);
string line;
    int count = 0;

    while (getline(file, line) && count < 27) {
        istringstream thisline(line);
        //split each instance of line into stringstream in order to track where in the file to pick up from for the next instance
        string questionstr, answerstr;

        if (getline(thisline, questionstr, '|') &&
            getline(thisline, answerstr) 
            ) {

            
            riddles[count].question = questionstr;//populate advisors array
            riddles[count].answer = answerstr;
            
            count++;
        }
    }

    file.close();
}
inline void printstats(Characters characters[], int i){
    cout<<characters[i].charnumber<<": "<<characters[i].name<<", age "<<characters[i].age<<"        ICON: "<<characters[i].icon<<endl;
    cout<<characters[i].strength<<" strength||"<<characters[i].wisdom<<" wisdom||"<<characters[i].stamina<<" stamina||"<<characters[i].pridepoints<<" pride points."<<endl;


}
inline void printadvisors(Advisors advisors[], int i){
    cout<<advisors[i].number<<":"<<advisors[i].name<<"- "<<advisors[i].description<<endl;
}

#endif