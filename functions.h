#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "Game.h"
#include "User.h"
#include "User_DB.h"

char getRandomLetter();
void assignPlayerNames(int, User&, User&, User&, User&, User&, User&);
void printRules();
void addLetterPoints(char, Game&, User&);
void addWordPoints(string, Game&, User&);
void goAgain(string, Game&, User&);
void playLetter(string, Game&, User&);
void playRandom(string, Game&, User&);
void playBasedOnInput(string, Game&, User&);
void playNextTurn(User&, Game&);
int getMaxScore();
int getNumPlayers();

int TIME_LIMIT = 10;

//returns a random letter a-z
char getRandomLetter()
{
    srand(time(NULL)); //initialize random seed
    return ('a' + rand()%26); //adds a random number 0-25 to ascii 'a' to assign a char
}

//assigns each player a name based on user input, then assigns the player who should be next based on number of players
void assignPlayerNames(int n, User &player1, User &player2, User &player3, User &player4, User &player5, User &player6)
{
    if (n > 0)
    {
        cout << "What is the name of player 1?" << endl;
        cin >> player1.name;
        player1.nextPlayer = &player1;
    }

    if (n > 1)
    {
        cout << "What is the name of player 2?" << endl;
        cin >> player2.name;
        player1.nextPlayer = &player2;
        player2.nextPlayer = &player1;
    }

    if (n > 2)
    {
        cout << "What is the name of player 3?" << endl;
        cin >> player3.name;
        player2.nextPlayer = &player3;
        player3.nextPlayer = &player1;
    }

    if (n > 3)
    {
        cout << "What is the name of player 4?" << endl;
        cin >> player4.name;
        player3.nextPlayer = &player4;
        player4.nextPlayer = &player1;
    }

    if (n > 4)
    {
        cout << "What is the name of player 5?" << endl;
        cin >> player5.name;
        player4.nextPlayer = &player5;
        player5.nextPlayer = &player1;
    }

    if (n > 5)
    {
        cout << "What is the name of player 6?" << endl;
        cin >> player6.name;
        player5.nextPlayer = &player6;
        player6.nextPlayer = &player1;
    }
}

//outputs the game's rules to the user
void printRules()
{
    cout << "=================================================RULES=======================================================" << endl;

    cout << "In the game of Letters, a player has four options on their turn.  They have 10 seconds to:" << endl << endl;

    cout << "1.Enter a specific letter. This letter is placed into a vector that is shown to the current player each turn." << endl;
    cout << "  Points are given based on the value of that letter to other players, divided by the number of times that that" << endl;
    cout << "  letter is in the vector." <<endl << endl;

    cout << "2.Enter a word.  If a word is entered, it is checked against a file containing all of the words in Websters" << endl;
    cout << "  English Dictionary. If the word is in the list, those letters are removed from the visible vector, and the " << endl;
    cout << "  word is added to an invisible vector that contains the used words. If the word is invalid (not in the list)," << endl;
    cout << "  or previously used, the player is notified and their turn is over." << endl << endl;

    cout << "3.Enter a random letter and guess a word.  The user can enter 'rand-word' where 'word' is a word" << endl;
    cout << "  to try. A random letter is chosen for them, then the word is tried. No points are awarded for the letter," << endl;
    cout << "  but points will be awarded for a valid word." << endl << endl;

    cout << "4.Remove a letter.  The player can enter 'remove-' followed by a letter in order to remove that letter" << endl;
    cout << "  from the vector. This awards no points." << endl << endl;

    cout << "The player can see these rules again by typing 'rules', or see the current scores by typing 'scores'." << endl;

    cout << "=============================================================================================================" << endl << endl;
}

//takes valid letter and gives user points
void addLetterPoints(char c, Game &gameBoard, User &player)
{
    int letterScore = 26 - gameBoard.indexOfLetter(c); //get score value of letter played
    int letterCount = gameBoard.countOccurences(c);
    int addScore = letterScore / letterCount; //divide by number of times letter is already in vector

    if (addScore == 0)
    {
        addScore++; //player must receive at least 1 point
    }

    cout << c << " is worth " << letterScore << " point(s), and now appears " << letterCount << " time(s) in the letters in play." << endl;
    player.increaseScore(addScore);
}

//takes valid word and gives user points, as well as removes used letters
void addWordPoints(string str, Game &gameBoard, User &player)
{
    int len = str.length();
    int wordValue = 0;

    for (int i = 0; i < len; i++)
    {
        wordValue += gameBoard.indexOfLetter(str[i]) + 1;
        gameBoard.removeLetter(str[i]);
    }
    cout << str << " is worth " << wordValue << " points." << endl;
    player.increaseScore(wordValue);
}

//gives the player a chance to complete their turn
void goAgain(string input, Game &gameBoard, User &currentPlayer)
{
    cout << "It's still your turn " << currentPlayer.name << ". Enter your input:" << endl;
    cin >> input;
    playBasedOnInput(input, gameBoard, currentPlayer);
}

//plays as though the input was a letter
void playLetter(string input, Game &gameBoard, User &currentPlayer)
{
    gameBoard.lettersInPlay.push_back(input[0]);
    addLetterPoints(input[0], gameBoard, currentPlayer);
}

//plays as though the input was "rand-word"
void playRandom(string input, Game &gameBoard, User &currentPlayer)
{
    string word = input.substr(5); //get substring after rand-
    gameBoard.lettersInPlay.push_back(getRandomLetter()); //put random letter in play

    if (gameBoard.tryWord(word))
    {
        addWordPoints(word, gameBoard, currentPlayer);
    }
    else
    {
        cout << word << " is not a valid word." << endl;
    }
}

//plays as though the input is a word
void playWord(string input, Game &gameBoard, User &currentPlayer)
{
    if (gameBoard.tryWord(input))
    {
        addWordPoints(input, gameBoard, currentPlayer);
    }
    else
    {
        cout << input << " is not a valid word." << endl << endl;
    }
}

//takes the input and decides what the player is trying to do
void playBasedOnInput(string input, Game &gameBoard, User &currentPlayer)
{
    int len = input.length();

    if (len == 1 && input[0] >= 'a' && input[0] <='z') //if input is a single letter
    {
        playLetter(input, gameBoard, currentPlayer);
    }
    else if (len > 5 && input.substr(0,5) == "rand-") //if input is "random"
    {
        playRandom(input, gameBoard, currentPlayer);
    }
    else if (input == "rules") //if input is "rules"
    {
        printRules();
        goAgain(input, gameBoard, currentPlayer);
    }
    else if (input == "scores") //if input is "scores"
    {
        currentPlayer.printScores();
        goAgain(input, gameBoard, currentPlayer);
    }
    else if (len == 8 && input.substr(0,7) == "remove-") //if input is "remove " followed by a character
    {
        gameBoard.removeLetter(input[7]);
    }
    else if (len > 1) //if input is a word
    {
        playWord(input, gameBoard, currentPlayer);
    }
    else
    {
        cout << "Invalid input, try again. Time's ticking!" << endl;
        goAgain(input, gameBoard, currentPlayer);
    }
}

//gets user input and decides how to proceed
void playNextTurn(User &player, Game &gameBoard)
{
    gameBoard.displayLettersInPlay();

    time_t start = time(0); //start timer

    string input;
    cout << "It's your turn " << player.name << ". Enter your input:" << endl;
    cin >> input;

    if (difftime( time(0), start) > TIME_LIMIT) //check how long the input took
    {
        cout << "Sorry " << player.name << ". You took too long." << endl;
    }
    else
    {
        playBasedOnInput(input, gameBoard, player);
    }
}

//takes user input and makes sure it is a valid integer
int getMaxScore()
{
    double n = 0;

    cout << "What will the winning score be? " << endl;
    cin >> n;

    while (cin.fail() || n < 0 || n > numeric_limits<int>::max()) // user didn't input a valid number
    {
        cin.clear(); // reset failbit
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input

        cout << "Invalid input. Try again." << endl;
        cout << "What will the winning score be? " << endl;
        cin >> n;
    }
    return (int)n; //cast valid number back to integer
}

//takes user input and makes sure it is a valid integer between 2 and 6 inclusive
int getNumPlayers()
{
    double n = 0;

    cout << "How many players?" << endl;
    cin >> n;

    while (cin.fail() || n < 2 || n > 6) // user didn't input a valid number
    {
        cin.clear(); // reset failbit
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input

        cout << "Invalid number of players.  Two to six players needed to play. Try again." << endl;
        cout << "How many players?" << endl;
        cin >> n;
    }
    return (int)n; //cast valid number back to integer
}

#endif // FUNCTIONS_H_INCLUDED
