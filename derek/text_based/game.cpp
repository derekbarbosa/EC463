#include "core_functions.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    int scenarioCounter = 0;
    /*
    bool isGradesPersistentPlus = false;
    bool isGradesPersistentMinus = false;
    bool isHealthPersistentPlus = false;
    bool isHealthPersistentMinus = false;
    bool isSocialPersistentPlus = false;
    bool isSocialPersistentMinus = false;
    bool isMoneyPersistentPlus = false;
    bool isMoneyPersistentMinus = false;
    */

    struct scenario *scenarioList = nullptr;

    userProfile *userProfile = nullptr;

    constructScenarioList(scenarioList);
    // welcomePrompt();

    initalizeGame(userProfile, argv[1]);

    while(scenarioCounter <= 50){

        scenarioList = scenarioList->next;
    }


    return 0;
}