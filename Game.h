#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

using namespace std;

class Game
{
    public:

        Game();
        bool wordIsUsed(string);
        bool wordIsInDictionary(string);
        bool wordIsInPlay(string);
        bool tryWord(string);
        void removeLetter(char);
        int indexOfLetter(char);
        int countOccurences(char);
        int countOccurencesInString(string, char);
        void displayLettersInPlay();

        int winningScore;
        vector<char> lettersInPlay;
        vector<string> usedWords;
        char letter_value_in_word[26];
};

//constructor
Game::Game()
{
    letter_value_in_word[0] = 'e';
    letter_value_in_word[1] = 't';
    letter_value_in_word[2] = 'a';
    letter_value_in_word[3] = 'o';
    letter_value_in_word[4] = 'i';
    letter_value_in_word[5] = 'n';
    letter_value_in_word[6] = 's';
    letter_value_in_word[7] = 'h';
    letter_value_in_word[8] = 'r';

    letter_value_in_word[9] = 'd';
    letter_value_in_word[10] = 'l';
    letter_value_in_word[11] = 'c';
    letter_value_in_word[12] = 'u';
    letter_value_in_word[13] = 'm';
    letter_value_in_word[14] = 'w';
    letter_value_in_word[15] = 'f';
    letter_value_in_word[16] = 'g';
    letter_value_in_word[17] = 'y';

    letter_value_in_word[18] = 'p';
    letter_value_in_word[19] = 'b';
    letter_value_in_word[20] = 'v';
    letter_value_in_word[21] = 'k';
    letter_value_in_word[22] = 'j';
    letter_value_in_word[23] = 'x';
    letter_value_in_word[24] = 'q';
    letter_value_in_word[25] = 'z';    //the value of the letter in a word is its index + 1
}

//returns true if the word has already been used for points
bool Game::wordIsUsed(string s)
{
    return (find(Game::usedWords.begin(), Game::usedWords.end(), s) != Game::usedWords.end());
}

//returns true if the word is in dictionary.txt
bool Game::wordIsInDictionary(string s)
{
    char aWord[50];
    ifstream file("dictionary.txt");

    while (file.good())
    {
        file>>aWord;
        if (file.good() && strcmp(aWord, s.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

//returns true if all of the letters in the string are in play
bool Game::wordIsInPlay(string str)
{
    int vecLen = Game::lettersInPlay.size();
    int strLen = str.length();
    bool wordIsValid = true;

    for (int i = 0; i < strLen; i++)
    {
        bool letterIsInPlay = false;

        for (int j = 0; j < vecLen; j++)
        {
            if (str[i] == lettersInPlay[j])
            {
                letterIsInPlay = true; //becomes true if that letter is in play
            }
        }
        //if any letter is not in play, or if there are less instances of a letter in play than in the string, the whole word is invalid
        if (!letterIsInPlay || Game::countOccurences(str[i]) < Game::countOccurencesInString(str, str[i]))
        {
            wordIsValid = false;
        }
    }
    return wordIsValid;
}

//returns true if a word is unused, exists in the dictionary, and is made of letters in play
bool Game::tryWord(string str)
{
   bool isValidWord = (!Game::wordIsUsed(str) && Game::wordIsInDictionary(str) && Game::wordIsInPlay(str));

   if (isValidWord)
   {
       Game::usedWords.push_back(str);
   }
   return isValidWord;
}

//remove a letter from the vector of letters in play
void Game::removeLetter(char c)
{
    int len = Game::lettersInPlay.size();
    bool letterExists = false;

    for (int i = 0; i < len; i++)
    {
        if (Game::lettersInPlay[i] == c)
        {
            Game::lettersInPlay.erase(Game::lettersInPlay.begin()+i); //erase the i+1 element from the vector
            letterExists = true;
            break; //break to avoid removing multiple letters
        }
    }
    if (!letterExists)
    {
        cout << c << " is not a letter currently in play." << endl;
    }
}

//find the index of a letter in the values vector
int Game::indexOfLetter(char c)
{
    int index = 0;

    for (int i = 0; i < 26; i++)
    {
        if (Game::letter_value_in_word[i] == c)
        {
            index = i;
        }
    }
    return index;
}

//returns the number of times a letter is in the letterInPlay vector
int Game::countOccurences(char c)
{
    int len = Game::lettersInPlay.size();
    int myCount = 0;

    for (int i = 0; i < len; i++)
    {
        if (Game::lettersInPlay[i] == c)
        {
            myCount++;
        }
    }
    return myCount;
}

//returns the number of times a character appears in the given string
int Game::countOccurencesInString(string str, char c)
{
    int len = str.length();
    int myCount = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i] == c)
        {
            myCount++;
        }
    }
    return myCount;
}

//shows the user the letters currently in play
void Game::displayLettersInPlay()
{
    int len = Game::lettersInPlay.size();

    cout << "Letters in play:" << endl;
    cout << "=======================================================" << endl << endl;
    for (int i = 0; i < len; i++)
    {
        cout << " " << Game::lettersInPlay[i];
    }
    cout << endl << endl;
    cout << "=======================================================" << endl << endl;
}

#endif // GAME_H_INCLUDED
