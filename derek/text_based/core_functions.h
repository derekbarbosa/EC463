// core_functions.h
#ifndef CORE_FUNCTIONS
#define CORE_FUNCTIONS

#include <string>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <string>

// HELPER FUNCTION FOR MATRIX ART
int Modulus(int iN, int iN2);

// HELPER FUNCTION FOR MATRIX ART
char GetChar(int iGenerator, char cBase, int iRange);

// PRINT MATRIX ART
void matrixArt();

// welcome prompt to the game, present some options -- finished
void welcomePrompt();

// Setup phase of the game, user should be able to enter their major and etc --finished
void initalizeGame();

// grab integer input specifically --finished
void grabInput(int &x);

void actionPenalty();

void crashGame();

enum majors
{
    QST, // INCREASED SPEECH -- BAD AT HOMEWORK
    ENG, // BETTER AT HOMEWORK -- CAN'T SHOWER
    CAS, // NO HOMEWORK WHATSOEVER
    DROPOUT
};

struct scenariosList
{
    bool task1Complete = false;
    bool task2Complete = false;
    bool task3Complete = false;
};

struct userProfile
{
    std::string name;
    majors major;
    int timeRemaining;

    int socialPoints = 100;
    int healthPoints = 100;
    int gradePoints = 100;
    int money = 100;

    struct scenariosList *tasksRemaining;


    /* member functions */
    void decreaseTime(){
        this->timeRemaining--;
    }

    /* Get Functions */
    int getTimeRemaining(){
        return this->timeRemaining;
    }
    
    int getSP(){
        return this->socialPoints;
    }

    int getHP(){
        return this->healthPoints;
    }

    int getGP(){
        return this->gradePoints;
    }

    int getMoney(){
        return this->money;
    }

    majors getMajor(){
        return this->major;
    }

    std::string getName(){
        return this->name;
    }

    void getTaskStatus(){
        std::cout << "Status of task 1:" << this->tasksRemaining->task1Complete << '\n';
        std::cout << "Status of task 2:" << this->tasksRemaining->task1Complete << '\n';
        std::cout << "Status of task 3:" << this->tasksRemaining->task1Complete << '\n';
    }

    /* Update Functions */

};

#endif /*CORE_FUNCTIONS.H*/
