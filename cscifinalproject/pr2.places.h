#ifndef places_h
#define places_h

struct Places{
    int playerindex;//made this whole struct for the sole purpose of the calculatewinner function in board, was originally going to use an array but it just did not work.
    int score;
    void initialize(){//I was having a lot of issues with making places work, i was getting super high numbers so i just made this function as a shot in the dark and it fixed everything
            playerindex = 0;
            score = 0;
    }
};

#endif