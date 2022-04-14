// core_functions.h
#ifndef CORE_FUNCTIONS
#define CORE_FUNCTIONS

#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>

// Game duration -- 50 day
#define GLOBAL_ACTION_LIMIT 50;

/* 4 CORE 'VALUES'
    GRADES
    HEALTH
    SOCIAL
    MONEY
*/

/* MODIFIERS
    +/- --> 5 POINTS
    ++/-- --> 10 POINTS
    +++/--- --> 20 POINTS
    ++++/---- --> Persistent PLUS or MINUS five
*/

/* BOUNDARIES
    ANY VALUE AT 0 --> LOSE
    ANY VALUE AT 200 --> LOSE
    IN BETWEEN IS FINE
*/

enum majors
{
    QST,
    ENG,
    CAS,
    DROPOUT,
    UNDEFINED
};

// node for text scenarios
struct scenario
{
    std::string id;
    std::string prompt;
    std::string option1;
    std::string option2;

    /*
        0 GRADES
        1 HEALTH
        2 SOCIAL
        3 MONEY
    */

    std::string consequence1Points[4] = {"", "", "", ""};
    std::string consequence2Points[4] = {"", "", "", ""};
    std::string consequence1Text;
    std::string consequence2Text; // delimiter of 'n'

    scenario *next;
};

void constructScenarioList(scenario **scenarioHead);

class userProfile
{
private:
    std::string name;
    majors major;
    int socialPoints;
    int healthPoints;
    int gradePoints;
    int money;

public:
    /* Constructor */
    userProfile()
    {
        this->socialPoints = 100;
        this->healthPoints = 100;
        this->gradePoints = 100;
        this->money = 100;
    }

    /*Update Functions*/
    void updateSP(int param)
    {
        if(param > 3){
            param = 1;
        }
        this->socialPoints = this->socialPoints + (param*10);
    }

    void updateHP(int param)
    {
         if(param > 3){
            param = 1;
        }
        this->healthPoints = this->healthPoints + (param*10);
    }

    void updateGP(int param)
    {
         if(param > 3){
            param = 1;
        }
        this->gradePoints = this->gradePoints + (param*10);
    }

    void updateMoney(int param)
    {
         if(param > 3){
            param = 1;
        }
        this->money = this->money + (param*10);
    }

    /* Get Functions */

    int getSP()
    {
        return this->socialPoints;
    }

    int getHP()
    {
        return this->healthPoints;
    }

    int getGP()
    {
        return this->gradePoints;
    }

    int getMoney()
    {
        return this->money;
    }

    majors getMajor()
    {
        return this->major;
    }

    std::string getName()
    {
        return this->name;
    }

    /* Set Functions */

    void setMajor(majors param)
    {
        this->major = param;
    }

    void setName(std::string param)
    {
        this->name = param;
    }
};

// HELPER FUNCTION FOR MATRIX ART
int Modulus(int iN, int iN2);

// HELPER FUNCTION FOR MATRIX ART
char GetChar(int iGenerator, char cBase, int iRange);

// PRINT MATRIX ART
void matrixArt();

// welcome prompt to the game, present some options -- finished
void welcomePrompt();

// Setup phase of the game, user should be able to enter their major and etc --finished
void initalizeGame(userProfile **user, char *argument);

// grab integer input specifically --finished
void grabInput(int &x);

// Background thread attached to a fork() bomb function
void crashGame();

// Global Update Function
int globalUpdate(userProfile *user, int grades, int health, int social, int money);

void print_scenario(scenario *sc);

#endif /*CORE_FUNCTIONS.HPP*/
