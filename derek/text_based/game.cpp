#include "core_functions.hpp"

int main()
{
    struct scenario *scenarioList;
    constructScenarioList(scenarioList);
    
    welcomePrompt();
    initalizeGame();

    return 0;
}