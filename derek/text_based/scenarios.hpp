#include "core_functions.hpp"


using namespace std;
//node
struct scenario{
    int id;
    string prompt;
    string option1;
    string option2;
    string consequence1;
    string consequence2;
    string consequence1Text;
    string consequence2Text; //delimiter of 'n'


    scenario *next;
};