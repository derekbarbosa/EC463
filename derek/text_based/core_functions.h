// core_functions.h
#ifndef CORE_FUNCTIONS
#define CORE_FUNCTIONS

#include <string> 
#include <iostream>
#include <chrono>
#include <thread>

//HELPER FUNCTION FOR MATRIX ART
int Modulus(int iN, int iN2);

//HELPER FUNCTION FOR MATRIX ART
char GetChar(int iGenerator, char cBase, int iRange);

//PRINT MATRIX ART
void matrixArt();

// welcome prompt to the game, present some options
void welcomePrompt();

// Setup phase of the game, user should be able to enter their major and etc
void initalizeGame();

void grabInput();

void actionPenalty();

//debating whether or not i should keep this stuff below this line
void initalizeInventory();

#endif /*CORE_FUNCTIONS.H*/
