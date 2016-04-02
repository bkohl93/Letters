#ifndef USER_DB_H_INCLUDED
#define USER_DB_H_INCLUDED

class User_DB
{
    public:
        User_DB();
        void addNewUser(int);
        void removeUser();
        int indexOfGreatestLowerScore();
        void writeHighScoresToFile();

        int highestScore;
        string winner;
        vector<int> scores;
        vector<string> names;
};

//constructor
User_DB::User_DB()
{
    highestScore = 0;

    ifstream scoreFile("highScores.txt");

    if (scoreFile)
    {
        string name;

        while (scoreFile >> name)
        {
            User_DB::names.push_back(name);
        }
    }

    int len = User_DB::names.size();

    //remove numbers from names vector, push them to scores vector
    for (int i = 0; i < len/2; i++)
    {
        User_DB::scores.push_back(atoi(User_DB::names[i+1].c_str())); //give score to scores vector
        User_DB::names.erase(User_DB::names.begin()+i+1); //erase the i+1 element from the vector
    }
}

void User_DB::addNewUser(int index)
{
    int len = User_DB::names.size();
    vector<int> tempScores;
    vector<string> tempNames;

    for (int i = 0; i < len-index; i++)
    {
        tempScores.push_back(User_DB::scores.back());
        User_DB::scores.pop_back();
        tempNames.push_back(User_DB::names.back());
        User_DB::names.pop_back();
    }

    User_DB::scores.push_back(User_DB::highestScore);
    User_DB::names.push_back(User_DB::winner);

    for (int i = 0; i < len-index; i++)
    {
        User_DB::scores.push_back(tempScores.back());
        tempScores.pop_back();
        User_DB::names.push_back(tempNames.back());
        tempNames.pop_back();
    }
}

void User_DB::removeUser()
{
    User_DB::names.pop_back();
    User_DB::scores.pop_back();
}

int User_DB::indexOfGreatestLowerScore()
{
    int len = User_DB::scores.size();
    int index = len;

    for (int i = 0; i < len; i++)
    {
        if (User_DB::scores[len-1-i] < User_DB::highestScore) //if a higher index is available, use it
        {
            index = len-1-i;
        }
    }
    return index;
}

void User_DB::writeHighScoresToFile()
{
    int len = User_DB::scores.size();


    ofstream scoreFile;
    scoreFile.open("highScores.txt");

    cout << endl;
    for (int i = 0; i < len; i++)
    {
        cout << User_DB::names.front() << " " << User_DB::scores.front() << endl;
        scoreFile << User_DB::names.front() << " " << User_DB::scores.front() << endl;
        User_DB::names.erase(User_DB::names.begin()); //erase the 1st element
        User_DB::scores.erase(User_DB::scores.begin());
    }
    cout << endl;
}

#endif // USER_DB_H_INCLUDED
