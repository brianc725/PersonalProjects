//
//  main.cpp
//  Hangman
//
//  Created by Brian Chan on 8/2/17.
//  Copyright © 2017 Brian Chan. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <cctype>
#include <vector>
#include <fstream>
using namespace std;

bool checkSolved(string disp);
bool checkGuessed(char letter, string wrong);
bool loadWords(vector <string> &words, string filename);
void lowerIt(string &word);

int main(int argc, char *argv[]) {
    int player;
    int guesses = 0;
    bool check = true;
    string wordsBackup [] = {"superhero", "rhythm", "driveway", "dictionary", "bibliography", "watermelon", "elephant"};
    vector <string> words;
    string word;
    string guess;
    string display;
    char letter;
    string guessedLetters;
    random_device rd;
    string fileName;
    
    cout << "Welcome to Hangman. Would you like to play by yourself (1) or with a friend (2)." << endl;
    cin >> player;
    while (check)
    {
        if (player == 1)    //if 1 player, choose one word from the txt file for guessing
        {
            //loads the words into the vector
            //program must be command lined so ./Hangman words.txt
            if (argc >= 2)
            {
                fileName = argv[1];
            }
            
            if (argc < 2 || loadWords(words, fileName) == false){
                cout << "An error has occurred. Using backup dataset." << endl;
                int rand = rd()%7;
                word = wordsBackup[rand];
                check = false;
             }
            else {
                int rand = rd()%words.size();
                word = words[rand];
                lowerIt(word);
                words.clear(); //clear vector to prevent memory leak
                check = false;
            }
        }
        else if (player == 2)   //if two player, one person is going to enter a word.
        {
            cout << "Enter the word that is to be guessed." << endl;
            cin.ignore(1000, '\n'); //needed because we read in a number previously so we must clear the newline char
            getline(cin, word); //read in the typed in word, can be more than one word via getline
            lowerIt(word);
            check = false;
        }
        else
        {
            cout << "Please enter a valid number. Yourself (1) or with a friend (2)." << endl;
            cin >> player;
        }
    }
    
    for (int i = 0; i < word.length(); i++)
    {
        if (isalpha(word[i]))
        {
            display += '*'; //puts * for every letter
        }
        else
        {
            display += ' '; //otherwise place a space
        }
    }
    cout << "\n\n\n\n\n\n\n" << endl; //clear the screen
    cout << "The word has been chosen. You can begin guessing now." << endl;
    
    while (guesses < 8) //user gets 8 chances
    {
        bool inString = false;
        
        cout << endl << display << endl;
        if (guessedLetters != "")   //if there are incorrectly guessed letters, show it
        {
            int chancesLeft = 8-guesses;
            cout << "You have " << chancesLeft << " chances left." << endl;
            cout << "Your incorrect guesses so far: " << guessedLetters << endl;
        }
        cout << "Enter a letter." << endl;
        cin >> letter;
        if (checkGuessed(letter, display) || checkGuessed(letter, guessedLetters))  //see if the letter was guessed already
        {
            cout << "You chose this letter already, guess again." << endl;
            continue;
        }
        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == letter)  //if the typed in char is correct, display it now
            {
                display[i] = letter;
                inString = true;
            }
        }
        
        if (!inString)  //if letter is not in the string at all, add to incorrect guesses
        {
            guesses++;
            guessedLetters += letter;
            guessedLetters += ' ';
        }
        
        if (checkSolved(display))   //if solved
        {
            cout << endl << "You got it! The word was " << word << "!" << endl;
            exit(0); //quit the program
        }
    }
    
    if (guesses >= 8)
    {
        cout << endl << "You are out of guesses. The word was " << word << ". Better luck next time!" << endl;
        exit(0);
    }
    
}

bool checkSolved(string disp)
{
    for (int i = 0; i < disp.length(); i++)
    {
        if (!isalpha(disp[i]) && disp[i] != ' ')  //if there is still a *, it is not solved yet
        {
            return false;
        }
    }
    return true;
}

bool checkGuessed(char letter, string wrong)
{
    for (int i = 0; i < wrong.length(); i++)
    {
        if (letter == wrong[i]) //check to see if the letter was guessed already by checking the string
            return true;
    }
    return false;
}

bool loadWords(vector <string> &words, string filename)
{
    ifstream infile(filename);   //loads the txt file words.txt
    if(!infile)
    {
        return false;   //if file doesn't open return false
    }
    string wordLoad;
    while(getline(infile, wordLoad))    //reads txt file until the end
    {
        words.push_back(wordLoad);  //loads each word into the vector
    }
    
    return true;
}

void lowerIt(string &word)
{
    string lower;
    for (int i = 0; i < word.length(); i++)
    {
        lower += tolower(word[i]);
    }
    word = lower;
}
