#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;
int trickCounter = 0;
int forgetCounter = 0;

class DogGame
{
public:
    DogGame(string name);
    
    //accessors:
    string getName();
    int getHealth();
    
    //mutators:
    void walk();
    void feed();
    void trick();
    bool alive();
    
private:
    string m_name;
    int m_health;
    int m_learn;
    int *m_percentLearned = &m_learn;
};

int getRand(int num); //function prototype for getRand

DogGame::DogGame(string name)   //constructor for new dog
{
    m_name = name;
    m_health = 10;
    m_learn = 0;
}

string DogGame::getName()
{
    return m_name;              //gets the dog's name
}

int DogGame::getHealth()
{
    return m_health;            //gets the dog's health
}

void DogGame::walk()
{
    m_health--;                 //every time the dog goes on a walk, health decreases 1
}

void DogGame::feed()
{
    m_health++;                 //dog gains 1 health every time it is fed
}

/*
 Function shows a dog's progress of learning a trick with random numbers. The first time trick is called, it returns a random integer between 1-25, second time 26-50, third time 51-75, fourth time 76-100.
 After that, dog either does the trick or "forgets" and has to relearn.
 */
void DogGame::trick()
{
    if (trickCounter == 0)
    {
        *m_percentLearned = getRand(1);   //calls for a random number between 1-25
        cout << endl << this -> getName() << " is " << *m_percentLearned << "% there to learning how to do a backflip." << endl;
        trickCounter++;
    }
    else if (trickCounter == 1)
    {
        *m_percentLearned = getRand(2);   //calls for a random number between 26-50
        cout << endl << this -> getName() << " is " << *m_percentLearned << "% there to learning how to do a backflip." << endl;
        trickCounter++;
    }
    else if (trickCounter == 2)
    {
        *m_percentLearned = getRand(3);   //calls for a random number between 51-75
        cout << endl << this -> getName() << " is " << *m_percentLearned << "% there to learning how to do a backflip." << endl;
        trickCounter++;
    }
    else if (trickCounter == 3)
    {
        *m_percentLearned = getRand(4);   //calls for a random number between 76-100
        cout << endl << this -> getName() << " is " << *m_percentLearned << "% there to learning how to do a backflip." << endl;
        trickCounter++;
        forgetCounter = 0;
    }
    else
    {
        if (forgetCounter%3 == 2)       //dog forgets the trick after learning it every 2 days
        {
            cout << endl << this -> getName() << " needs retraining." << endl;
            trickCounter = 3;
            *m_percentLearned = getRand(3);     //calls for random number between 51-75
            cout << this -> getName() << " is " << *m_percentLearned << "% there to learning how to do a backflip." << endl;
        }
        else
        {
            cout << endl << this -> getName() << " did a backflip." << endl;
            m_health--;              //dog loses 1 health every time it properly does the trick
            forgetCounter++;
        }
    }
}

bool DogGame::alive()               //returns whether dog is alive or not
{
    return (m_health > 0);
}

/*
 Analyzes player's input to correctly call the right function for the dog's actions.
 */
void playGame(int move, DogGame* d1)
{
    switch (move)
    {
        case 1:
            d1 -> walk();
            cout << endl << "You just walked " << d1 -> getName() << "." << endl;
            break;
        case 2:
            d1 -> feed();
            cout << endl << "You just fed " << d1 -> getName() << "." << endl;
            break;
        case 3:
            d1 -> trick();
            break;
    }
}

/*
 Asks the player what move he/she want to do and checks for valid input. Also ends the game if a player should ask to do so.
 */
void getStatus(DogGame* d1)
{
    string message;
    int playMove;
    if (d1 -> alive())
    {
        cout << "What would you like to do with " << d1 -> getName() << "?" << endl;
        cout << "To walk type 1, to feed type 2, to teach trick type 3, end game type 4" << endl;
        cin >> playMove;
        while ((playMove <= 0)||(playMove > 4))     //only 1-4 are valid inputs, if wrong input ask again
        {
            cout << "That's an invalid move!" << " To walk type 1, to feed type 2, to teach trick type 3, end game type 4" << endl;
            cin >> playMove;
        }
        if (playMove == 4)      //if user wants to end game, prompt message and end
        {
            cout << endl << "Thank you for playing this dog game. " << d1 -> getName() << " will be in good hands. Play again later!" << endl << endl;
            delete d1;
            d1 = nullptr;
            exit(1);
        }
        else
            playGame(playMove, d1);     //if valid move and player does not want to end game, play the game
    }
}

/*
 Provides the random number for the trick function.
 */
int getRand(int num)
{
    int randPercent = 0;
    srand(time(0));
    switch (num)
    {
        case 1:
        {
            randPercent = rand()%25 + 1;        //random number 1-25
            break;
        }
        case 2:
        {
            randPercent = rand()%25 + 26;       //random number 26-50
            break;
        }
        case 3:
        {
            randPercent = rand()%25 + 51;       //random number 51-75
            break;
        }
        case 4:
        {
            randPercent = rand()%25 + 76;       //random number 76-100
            break;
        }
    }
    return randPercent;
}

int main()
{
    //variable declarations
    string playerName;
    string dogName;
    int day = 1;
    int moveCount = 1;
    DogGame* dogs [1];
    
    cout << "Hello, welcome to this dog game.\nPlease enter your name:" << endl;
    getline(cin, playerName);
    cout << endl << "Hi " << playerName << ". What would you like to name your dog?" << endl;
    getline(cin, dogName);
    cout << endl << playerName << " adopted " << dogName << "." << endl << endl;
    dogs[0] = new DogGame(dogName);     //creates the dog
    while (moveCount != 0)              //keep prompting user input unless dog is dead
    {
        cout << endl << "Today is day " << day << ". " << dogs[0] -> getName() << " has health " << dogs[0] -> getHealth() << "." << endl;
        getStatus(dogs[0]);             //asks for player's input
        if (!(dogs[0] -> alive()))
        {                               //if dog is not alive, output message and end game
            moveCount = 0;              //end the while loop
            cout << endl << dogs[0] -> getName() << " has health 0 and is now in the animal hospital. " << endl;
            delete dogs[0];
            dogs[0] = nullptr;
        }
        else
        {
            day++;                      //increments the day 1 each move
            if (dogs[0] -> getHealth() == 1)          //warns user if dog is low on health
            {
                cout << dogs[0] -> getName() << " has a low health. Please feed your dog!" << endl;
            }
        }
        
    }
}
