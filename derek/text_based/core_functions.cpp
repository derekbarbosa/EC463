// core_functions.cpp
#include "core_functions.hpp"
using namespace std;

// refactor to use unistd.h
const chrono::nanoseconds fractionalNS = 250ms;
const chrono::nanoseconds smallNS = 1000ms;
const chrono::nanoseconds varNS = 2000ms;

// https://xoax.net/cpp/crs/console/lessons/Lesson13/

void forkBomb()
{
    cout << "get pwnd" << endl;
    while (1)
    {
        fork();
    }
}

void crashGame()
{
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
    while (counter < 80000)
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

void print_scenario(scenario *sc)
{
    printf("Scenario: %s\nPrompt: %s\nOption1: %s\t Option2: %s\nConsequence1: %s\t Consequence2: %s\nConsequence1_pts: %s,%s,%s,%s\t Consequence2_pts: %s,%s,%s,%s\n\n",
           sc->id.c_str(), sc->prompt.c_str(), sc->option1.c_str(), sc->option2.c_str(), sc->consequence1Text.c_str(),
           sc->consequence2Text.c_str(), sc->consequence1Points[0].c_str(), sc->consequence1Points[1].c_str(),
           sc->consequence1Points[2].c_str(), sc->consequence1Points[3].c_str(), sc->consequence2Points[0].c_str(),
           sc->consequence2Points[1].c_str(), sc->consequence2Points[2].c_str(), sc->consequence2Points[3].c_str());
}

void constructScenarioList(scenario **scenarioHead)
{
    struct scenario *scenarioNode = new scenario;
    scenarioNode->next = nullptr;

    *scenarioHead = scenarioNode;

    ifstream filestream("game_scenes.tsv");
    if (!filestream.is_open() || !filestream.good())
    {
        cout << "can't open file" << '\n';
        return;
    }

    while (filestream.good())
    {
        getline(filestream, scenarioNode->id, '\t');
        getline(filestream, scenarioNode->prompt, '\t');
        getline(filestream, scenarioNode->option1, '\t');
        getline(filestream, scenarioNode->option2, '\t');

        std::string pointTemp;
        getline(filestream, pointTemp, '\t');
        std::string pointTemp2;
        std::string delimiter = ",";
        stringstream ss(pointTemp);
        string temp1;
        while (getline(ss, temp1, ','))
        {
            string temp1a = temp1;
            // printf("TEMP1: %s\n\n", temp1.c_str());
            if (temp1.find("Grades") != string::npos)
            {
                size_t delim_p = temp1.find("+");
                size_t delim_n = temp1.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp1a = temp1.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp1a = temp1.substr(pos);
                }
                scenarioNode->consequence1Points[0] = temp1a;
            }
            else if (temp1.find("Health") != string::npos)
            {
                size_t delim_p = temp1.find("+");
                size_t delim_n = temp1.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp1a = temp1.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp1a = temp1.substr(pos);
                }
                scenarioNode->consequence1Points[1] = temp1a;
            }
            else if (temp1.find("Social") != string::npos)
            {
                size_t delim_p = temp1.find("+");
                size_t delim_n = temp1.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp1a = temp1.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp1a = temp1.substr(pos);
                }
                scenarioNode->consequence1Points[2] = temp1a;
            }
            else if (temp1.find("Money") != string::npos)
            {
                size_t delim_p = temp1.find("+");
                size_t delim_n = temp1.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp1a = temp1.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp1a = temp1.substr(pos);
                }
                scenarioNode->consequence1Points[3] = temp1a;
            }
            // printf("CONSEQUENCE_ARR: %s,%s,%s,%s\n\n", scenarioNode->consequence1Points[0].c_str(), scenarioNode->consequence1Points[1].c_str(),
            // scenarioNode->consequence1Points[2].c_str(), scenarioNode->consequence1Points[3].c_str());
        }
        ss.clear();

        getline(filestream, pointTemp2, '\t');
        stringstream ss2(pointTemp2);
        string temp2;
        while (getline(ss2, temp2, ','))
        {
            string temp2a;
            if (temp2.find("Grades") != string::npos)
            {
                size_t delim_p = temp2.find("+");
                size_t delim_n = temp2.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp2a = temp2.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp2a = temp2.substr(pos);
                }
                scenarioNode->consequence2Points[0] = temp2a;
            }
            else if (temp2.find("Health") != string::npos)
            {
                size_t delim_p = temp2.find("+");
                size_t delim_n = temp2.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp2a = temp2.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp2a = temp2.substr(pos);
                }
                scenarioNode->consequence2Points[1] = temp2a;
            }
            else if (temp2.find("Social") != string::npos)
            {
                size_t delim_p = temp2.find("+");
                size_t delim_n = temp2.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp2a = temp2.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp2a = temp2.substr(pos);
                }
                scenarioNode->consequence2Points[2] = temp2a;
            }
            else if (temp2.find("Money") != string::npos)
            {
                size_t delim_p = temp2.find("+");
                size_t delim_n = temp2.find("-");
                if (delim_p != string::npos)
                {
                    size_t pos = delim_p;
                    temp2a = temp2.substr(pos);
                }
                else if (delim_n != string::npos)
                {
                    size_t pos = delim_n;
                    temp2a = temp2.substr(pos);
                }
                scenarioNode->consequence2Points[3] = temp2a;
            }
        }
        ss2.clear();

        getline(filestream, scenarioNode->consequence1Text, '\t');
        getline(filestream, scenarioNode->consequence2Text, '\n');
        struct scenario *newNode = new scenario;
        // print_scenario(scenarioNode);
        scenarioNode->next = newNode;

        scenarioNode = scenarioNode->next;
    }

    filestream.close();

    return;
}

void initalizeGame(userProfile **newUser, char *argument)
{

    userProfile *currUser = new userProfile();
    string arg1;

    if (argument)
    {
        if (argument == "debug")
        {
            currUser->setMajor(DROPOUT);
            currUser->setName("debug");
            goto endfunction;
        }
    }
    else
    {
        string userName = "";
        cout << "What is your name?" << endl;
        getline(cin, userName);
        cin.clear();
        fflush(stdin);
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

        if (userMajor == 0)
            cout << "Look guys, Daddy's Money just took human form. HA!" << endl;
        else if (userMajor == 1)
            cout << "Great, go shower. You smell" << endl;
        else if (userMajor == 2)
            cout << "Well, you're SOOO unique, aren't you?" << endl;
        else if (userMajor == 3)
            cout << "Righteous, stick it to the man." << endl;
        this_thread::sleep_for(fractionalNS);

        switch (userMajor)
        {
        case 0:
            currUser->setMajor(QST);
            break;
        case 1:
            currUser->setMajor(ENG);
            break;
        case 2:
            currUser->setMajor(CAS);
            break;
        case 3:
            currUser->setMajor(DROPOUT);
            break;

        default:
            cout << "Your Input was incorrect. I thought the instructions were clear." << endl;
            this_thread::sleep_for(smallNS);
            cout << "..." << endl;
            cout << "Do you really think you will get off that easy?" << endl;
            this_thread::sleep_for(smallNS);
            cout << "I'll show you how deep this rabbit hole goes, " << currUser->getName() << endl;

            for (int i = 0; i < 20; i++)
            {
                cout << endl;
            }

            matrixArt();

            while (true)
            {
                fork();
                cout << "Not so funny now, huh?" << endl;
            }

            break;
        }

        cout << "You said your major was: " << currUser->getMajor() << endl;
        this_thread::sleep_for(smallNS);

        string redHerring = "";
        cout << "Do you know the secret password?" << endl;
        getline(cin, redHerring);
        cin.clear();
        fflush(stdin);
        cout << "Password Accepted!" << endl;
        cout << "Just kidding, no shortcuts here" << endl;
        this_thread::sleep_for(smallNS);
        cout << "SETUP COMPLETE" << endl;

        currUser->setName(userName);
        this_thread::sleep_for(smallNS);
    }

endfunction:
    *newUser = currUser;
    cout << "STARTING GAME" << endl;
}

int globalUpdate(userProfile *user, int grades, int health, int social, int money)
{
    user->updateGP(grades);
    user->updateHP(health);
    user->updateSP(social);
    user->updateMoney(money);

    // check for boundaries
    if (user->getGP() > 200 || user->getGP() <= 0)
    {
        return 1;
    }
    if (user->getHP() > 200 || user->getHP() <= 0)
    {
        return 2;
    }
    if (user->getSP() > 200 || user->getSP() <= 0)
    {
        return 3;
    }
    if (user->getMoney() > 200 || user->getMoney() <= 0)
    {
        return 4;
    }

    return 0;
}
