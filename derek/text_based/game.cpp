#include "core_functions.hpp"
using namespace std;

int main(int argc, char *argv[])
{
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
    userProfile *testProfile = new userProfile();

    testProfile->setName("test");
    userProfile *userProfile = nullptr;

    constructScenarioList(scenarioList);
    // welcomePrompt();

    //initalizeGame(userProfile, argv[1]);

    cout << testProfile->getGP() << endl;

    return 0;
}