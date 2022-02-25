#include "core_functions.hpp"

int main()
{
    bool isGradesPersistentPlus = false;
    bool isGradesPersistentMinus = false;
    bool isHealthPersistentPlus = false;
    bool isHealthPersistentMinus = false;
    bool isSocialPersistentPlus = false;
    bool isSocialPersistentMinus = false;
    bool isMoneyPersistentPlus = false;
    bool isMoneyPersistentMinus = false;

    struct scenario *scenarioList = NULL;
    struct userProfile *userProfile = NULL;

    constructScenarioList(scenarioList);
    welcomePrompt();

    initalizeGame(userProfile);
    
    //segfault
    while(userProfile->timeRemaining >= 0){
        std::cout << "Day" << 51-(userProfile->timeRemaining) << '\n';
    }


    return 0;
}