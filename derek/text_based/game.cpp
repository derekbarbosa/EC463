#include "core_functions.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    int scenarioCounter = 0;

    bool isGradesPersistentPlus = false;
    bool isGradesPersistentMinus = false;
    bool isHealthPersistentPlus = false;
    bool isHealthPersistentMinus = false;
    bool isSocialPersistentPlus = false;
    bool isSocialPersistentMinus = false;
    bool isMoneyPersistentPlus = false;
    bool isMoneyPersistentMinus = false;

    struct scenario *scenarioList = nullptr;

    userProfile *userProfile = nullptr;

    constructScenarioList(&scenarioList);
    welcomePrompt();

    initalizeGame(&userProfile, argv[1]);
    int choice = 0;
    while (scenarioCounter < 50)
    {
        int update;
        // print_scenario(scenarioList);
        scenarioList = scenarioList->next;
        cout << "Loading day: " << scenarioList->id << endl;
        cout << "These are your current stats\n" <<  "Grades: " << userProfile->getGP() << "\t Health: " << userProfile->getHP() << "\t Social: " << userProfile->getSP() << "\t Money: " << userProfile->getMoney() << endl;
        cout << scenarioList->prompt << endl;
        cout << "[1] " << scenarioList->option1 << "\t[2] " << scenarioList->option2 << endl;
        grabInput(choice);
        if (choice == 1)
        {
            int grades = strlen(scenarioList->consequence1Points[0].c_str());
            if (grades)
                grades = scenarioList->consequence1Points[0][0] == '+' ? grades : -grades;
            int health = strlen(scenarioList->consequence1Points[1].c_str());
            if (health)
                health = scenarioList->consequence1Points[1][0] == '+' ? health : -health;
            int social = strlen(scenarioList->consequence1Points[2].c_str());
            if (social)
                social = scenarioList->consequence1Points[2][0] == '+' ? social : -social;
            int money = strlen(scenarioList->consequence1Points[3].c_str());
            if (money)
                money = scenarioList->consequence1Points[3][0] == '+' ? money : -money;

            if (abs(grades) > 3)
                grades > 0 ? isGradesPersistentPlus = true : isGradesPersistentMinus = true;
            if (abs(health) > 3)
                health > 0 ? isHealthPersistentPlus = true : isHealthPersistentMinus = true;
            if (abs(social) > 3)
                social > 0 ? isSocialPersistentPlus = true : isSocialPersistentMinus = true;
            if (abs(money) > 3)
                money > 0 ? isMoneyPersistentPlus = true : isMoneyPersistentMinus = true;

            cout << scenarioList->consequence1Text << endl;
            update = globalUpdate(userProfile, grades, health, social, money);
        }
        else if (choice == 2)
        {
            if (scenarioList->id == "25")
            {
                crashGame();
            }
            int grades = strlen(scenarioList->consequence2Points[0].c_str());
            if (grades)
                grades = scenarioList->consequence2Points[0][0] == '+' ? grades : -grades;
            int health = strlen(scenarioList->consequence2Points[1].c_str());
            if (health)
                health = scenarioList->consequence2Points[1][0] == '+' ? health : -health;
            int social = strlen(scenarioList->consequence2Points[2].c_str());
            if (social)
                social = scenarioList->consequence2Points[2][0] == '+' ? social : -social;
            int money = strlen(scenarioList->consequence2Points[3].c_str());
            if (money)
                money = scenarioList->consequence2Points[3][0] == '+' ? money : -money;

            if (abs(grades) > 3)
                grades > 0 ? isGradesPersistentPlus = true : isGradesPersistentMinus = true;
            if (abs(health) > 3)
                health > 0 ? isHealthPersistentPlus = true : isHealthPersistentMinus = true;
            if (abs(social) > 3)
                social > 0 ? isSocialPersistentPlus = true : isSocialPersistentMinus = true;
            if (abs(money) > 3)
                money > 0 ? isMoneyPersistentPlus = true : isMoneyPersistentMinus = true;

            cout << scenarioList->consequence2Text << endl;
            update = globalUpdate(userProfile, grades, health, social, money);
        }
        else
        {
            cout << "GET A LIFE, DO THE GAME RIGHT" << endl;
            int grades = -15;
            int health = -15;
            int social = -15;
            int money = -15;
            update = globalUpdate(userProfile, grades, health, social, money);
        }

        if(update){
            cout << "you lose, idiot" << endl;
            exit(0);
        }
        scenarioCounter++;
    }

    return 0;
}