#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <limits>

#include "functions.h"

int main()
{
    //initialize game, user database, users
    User_DB data;
    Game gameBoard;
    User p1;
    User p2;
    User p3;
    User p4;
    User p5;
    User p6;

    printRules();

    int n = getNumPlayers();

    assignPlayerNames(n, p1, p2, p3, p4, p5, p6);

    gameBoard.winningScore = getMaxScore();

    User* currentPlayer = &p1; //need to know who is playing
    User* lastPlayer = &p1; //need to know who played last

    while (data.highestScore < gameBoard.winningScore)
    {
        playNextTurn(*currentPlayer, gameBoard);    //play a turn with the current player
        lastPlayer = currentPlayer;                 //player's turn is over, they become the last player
        currentPlayer = lastPlayer->nextPlayer;     //after turn is over, it's the next player's turn

        if (lastPlayer->score > data.highestScore)  //only the current player's score can change
        {
            data.highestScore = lastPlayer->score;
        }
    }
    data.winner = lastPlayer->name;

    cout << "Congratulations " << data.winner << "!"  << endl; //the winner has to be the person who played last
    cout << "You won with a score of " << data.highestScore << "!" << endl; //the winner must have the highest score

    int index = data.indexOfGreatestLowerScore();

    if (index < 10)
    {
        cout << "NEW HIGH SCORE!" << endl;
        data.removeUser();
        data.addNewUser(index);
        data.writeHighScoresToFile();
        cout << data.winner << " is now rank " << index+1 << " on the list of high scores!" << endl;
    }
    return 0;
}
