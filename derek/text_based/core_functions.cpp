// core_functions.cpp
#include "core_functions.h"
using namespace std;

// https://xoax.net/cpp/crs/console/lessons/Lesson13/

int Modulus(int iN, int iMod) {
     int iQ = (iN/iMod);
     return iN - (iQ*iMod);
}

char GetChar(int iGenerator, char cBase, int iRange) {
     return (cBase + Modulus(iGenerator, iRange));
}

void matrixArt(){
     


     char caRow[80];
     int j = 7;
     int k = 2;
     int l = 5;
     int m = 1;
     int counter = 0;
     while (counter < 800000) {
          int i = 0;
          // Output a random row of characters
          while (i < 80) {
               if (caRow[i] != ' ') {
                    caRow[i] = GetChar(j + i*i, 33, 30);
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
          while (i < 10) {
               GetChar(1, 1, 1);
                    ++i;
          }
          counter++;
     }
}

void welcomePrompt(){

     //Draw the matrix art out
     const chrono::nanoseconds varNS = 2000ms;

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

     cout << '\n' << endl;
     cout << '\n' << endl;



     cout << "ENTERING THE MATRIX" << endl;
     this_thread::sleep_for(varNS);

     matrixArt();
     cout << '\n' << endl;
     cout << '\n' << endl;

     for(int i = 0; i < 10; i++){
          cout << "DO" << endl;
     }
     this_thread::sleep_for(varNS);

     for(int i = 0; i < 10; i++){
          cout << "NOT" << endl;
     }
     this_thread::sleep_for(varNS);

     for(int i = 0; i < 10; i++){
          cout << "LOOK" << endl;
     }
     this_thread::sleep_for(varNS);

     for(int i = 0; i < 10; i++){
          cout << "BACK" << endl;
     }
     this_thread::sleep_for(varNS);

     cout << '\n' << endl;
     cout << '\n' << endl;

     this_thread::sleep_for(varNS);

     cout << "..." << endl;
     this_thread::sleep_for(varNS);
     this_thread::sleep_for(varNS);


     cout << "Wake Up..." << endl;

}
