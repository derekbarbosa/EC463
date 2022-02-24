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
    constructScenarioList(scenarioList);

    welcomePrompt();
    initalizeGame();

    return 0;
}