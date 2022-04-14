#include "core_functions.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    string debug = "debug";

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

    if (argc == 0)
    {
        if (debug.compare(argv[1]) == 0 )
            goto skip;
    }
    welcomePrompt();
skip:
    initalizeGame(&userProfile, argv[1]);
    int choice = 0;
    while (scenarioCounter < 50)
    {
        int update;
        // print_scenario(scenarioList);
        scenarioList = scenarioList->next;
        cout << "Loading day: " << scenarioList->id << endl;
        cout << endl;
        cout << "These are your current stats\n"
             << "Grades: " << userProfile->getGP() << "\t Health: " << userProfile->getHP() << "\t Social: " << userProfile->getSP() << "\t Money: " << userProfile->getMoney() << endl;
        cout << scenarioList->prompt << "\n"
             << endl;
        cout << "[1] " << scenarioList->option1 << "\t[2] " << scenarioList->option2 << endl;
        cout << endl;
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
            globalUpdate(userProfile, grades, health, social, money);
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
            globalUpdate(userProfile, grades, health, social, money);
        }
        else
        {
            cout << "GET A LIFE, DO THE GAME RIGHT" << endl;
            int grades = -5;
            int health = -5;
            int social = -5;
            int money = -5;
            update = globalUpdate(userProfile, grades, health, social, money);
        }
        int grades = 0, health = 0, social = 0, money = 0;

        if (isGradesPersistentPlus)
        {
            grades += 1;
        }
        if (isGradesPersistentMinus)
        {
            grades += -1;
        }
        if (isHealthPersistentPlus)
        {
            health += 1;
        }
        if (isHealthPersistentMinus)
        {
            health += -1;
        }
        if (isSocialPersistentPlus)
        {
            social += 1;
        }
        if (isSocialPersistentMinus)
        {
            social += -1;
        }
        if (isMoneyPersistentPlus)
        {
            money += 1;
        }
        if (isMoneyPersistentMinus)
        {
            money += -1;
        }
        update = globalUpdate(userProfile, grades, health, social, money);
        switch (update)
        {
        case 1:
            cout << "\n Your abnormally high grades draw a great deal of attention. Your friends are horribly envious, but that pales in comparison to the wrath you've just brought upon yourself." << endl;
            cout << "Your record-breaking GPA lands you a meeting with the Dean. Turns out you're getting expelled because you've been accused of cheating. \n Guilty until proven innocent, and you have nothing to defend yourself. (Maybe don't hold a higher average GPA than Einstein next time?)" << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 2:
            cout << "\n Your lack of academic drive gets you a one-stop shop to Downtown FlunkVille. Congrats, you failed college and are now priced out of the housing market forever." << endl;
            cout << "Oh, and everyone is disappointed in you." << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 3:
            cout << "\n Your amazing health has grown your confidence by levels unrivaled by egocentric frat boys. \n Your overconfidence in your youth, health, and strength prompts to you to take a bet on your immune system. You drank expired milk and died." << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 4:
            cout << "\n Your lack of health has weakened your immune system. You caught the Flu Virus and died." << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 5:
            cout << "\n Your frequent partying and attendance in large social gatherings has exposed you to a variety of characters in the past few days." << endl;
            cout << "You notice that you feel a little strange, yet decide to go out again tonight anyway. After all, it is Margarita Monday!" << endl;
            cout << "Turns out, you've caught COVID. You died." << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 6:
            cout << "\n Your wallet has been a little heavier recently. You decide to splurge on some designer clothing and bling -- 'cause everyone needs some DRIP" << endl;
            cout << "Well, your 'DRIP' got you mugget. Oh, and you were stabbed. You died behind TiTS" << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        case 7:
            cout << "\n We all know the age-old trope of the broke college student. But man, you took it to a whole new extreme, didn't you?" << endl;
            cout << "I mean, you're so broke, you're washing PAPER PLATES for God's sake." << endl;
            cout << "You were so poor, you had to drop out to go find a job and work. Manage your cash a little better next time" << endl;
            cout << " YOU LOST." << endl;
            exit(0);
            break;
        default:
            break;
        }
        scenarioCounter++;
    }

    cout << "\n Congratulations, you win. I hope you're happy with yourself. Take a look at the clock, how much time did you waste?" << endl;
    cout << "Well, here's your 'secret surprise' you wanted this whole time. I guess i'll just be here... alone.... forever." << endl;
    cout << "SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED \t SECRET UNLOCKED" << endl;
    cout << "696c6f7665766574636f6e" << endl;
    return 0;
}