#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

class User
{
    public:
        User();
        void increaseScore(int n);
        void printScores();

        int score;
        string name;
        User* nextPlayer;
};

//constructor
User::User()
{
    score = 0;
    name = "";
}

//adds n to the user's score
void User::increaseScore(int n)
{
    User::score += n; //add new value to player's score
    cout << User::name << " receives " << n << " points for a total of " << User::score << " points." << endl << endl;
}

//outputs the game's rules to the user
void User::printScores()
{
    User* nextUser = User::nextPlayer;
    User* thisUser = nextUser->nextPlayer;

    cout << endl << nextUser->name << " has " << nextUser->score << " points." << endl;

    while (thisUser != nextUser)
    {
        cout << thisUser->name << " has " << thisUser->score << " points." << endl;
        thisUser = thisUser->nextPlayer;
    }
    cout << endl;
}

#endif // USER_H_INCLUDED
