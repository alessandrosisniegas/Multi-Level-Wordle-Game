// Alessandro Sisniegas
// 04-21-22
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
using namespace std;

int main () {
    ifstream file;
    string words = "words2.txt";
    string wordle;
    string guess;
    char userPlay = 'y';
    int wins = 0;
    int loss = 0;
    int wordleNum;
    int round = 1;
    file.open(words);

    // where word list will be stored
    vector<string> wordList;
    vector<int> wordleMatch(5);
    vector<int> guessMatch(5);

    // extracts file data and stored in vector wordlist
    while (!file.eof()) {
        getline(file, wordle);
        wordList.push_back(wordle);
    }

    // sorting data for binary search
    sort(wordList.begin(), wordList.end());

    // rand generator using dynamic mode for more unique sequences
    srand(time(0));

    // display intro & game rules
    cout << endl;
    cout << "welcome to ale's wordle" << endl;
    cout << "letter will be\x1b[32;40m green \x1b[0mif exact match" << endl;
    cout << "letter will be\x1b[33;40m yellow \x1b[0mif letter is in wrong spot" << endl;
    cout << "letter will be\x1b[31;40m red \x1b[0mif non existent in word" << endl;
    cout << endl;

    while (userPlay == 'y') {
        wordleNum = rand() % wordList.size();
        wordle = wordList.at(wordleNum);

        for (int j = 1; j < 7; ++j) {
            cout << "Round " << round << " -- Attempt " << j << "/6" << endl;
            cout << "Enter 5 letter word:" << endl;
            cin >> guess;

            // setting match vectors to default
            for (int i = 0; i < 5; ++i) {
                wordleMatch.at(i) = 0;
                guessMatch.at(i) = 0;
            }

            // binary search to see if guess is valid word and 5 letters
            if (!binary_search(wordList.begin(), wordList.end(), guess)) {
                cout << "word not valid. try again\n" << endl;
                --j;
                continue;
            }

            if (guess == wordle) {
                break;
            }

            // checks perfect matches
            // exact match = 1
            for (int i = 0; i < 5; ++i) {
	            guess.at(i) = tolower(guess.at(i));
                if (guess.at(i) == wordle.at(i)) {
                    wordleMatch.at(i) = 1;
	                guessMatch.at(i) = 1;
                } 
            }

            // checks for partial matches
            // partial match = 2
            for (int i = 0; i < 5; ++i) {
                if (guessMatch.at(i) == 1 || guessMatch.at(i) == 2) {
                    continue;
                }
                for (int j = 0; j < 5; ++j) {
                    if (wordleMatch.at(j) == 1 || wordleMatch.at(j) == 2) {
                        continue;
                    }
                    if (guess.at(i) == wordle.at(j)) {
                        wordleMatch.at(j) = 2;
	                    guessMatch.at(i) = 2;
                    }
                }
            }

            // displays player feedback on guess
            for (int i = 0; i < 5; ++i) {
                if (guessMatch.at(i) == 1) {
                    cout << "\x1b[32;40m" << guess.at(i) << "\x1b[0m";
                } else if (guessMatch.at(i) == 2) {
                    cout << "\x1b[33;40m" << guess.at(i) << "\x1b[0m";
                } else {
                    cout << "\x1b[31;40m" << guess.at(i) << "\x1b[0m";
                }
            }
            cout << endl;
            cout << endl;
        }
        cout << endl;
        
        if (guess == wordle) {
            cout << "winner!" << endl;
            cout << "the word was " << wordle << endl;
            ++wins;
        } else {
            cout << "loser" << endl;
            cout << "the word was " << wordle << endl;
            ++loss;
        }
        ++round;
        cout << "play again? enter 'y' for yes or any other key for no:" << endl;
        cin >> userPlay;
        userPlay = tolower(userPlay);
        cout << endl;
    }

    // end of game give's user stats
    cout << "thank you for playing!" << endl;
    cout << "you played " << round - 1 << " round(s)" << endl; 
    cout << "your stats are: " << wins << " win(s) - " << loss << " loss(es)" << endl;
    cout << endl;

    return 0;
}