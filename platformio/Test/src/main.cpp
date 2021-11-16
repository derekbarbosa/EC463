#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <Button.h>

#define NAMESET 1



  
Button push1(PUSH1);
Button push2(PUSH2);

int startFlag = 0;
int secretFlag = 0;
int firstMenu = 0;
int nameToggle = 0;


String name = "";
String yes = "yes";


// Function Prototypes
void mainMenu();

void setName();

void displayName();

int playGame();

void secret();

void resetBadge();

void setup()
{
  // put your setup code here, to run once:

  push1.begin();
  push2.begin();

  Serial.begin(9600);
}

int playGame()
{
  //print game URL and accept HASHED input
}

void mainMenu()
{

statement:
  Serial.print("************************\n");
  Serial.print("*|        MENU        |*\n");
  Serial.print("*|                    |*\n");
  Serial.print("*| 1: Set Name Tag    |*\n");
  Serial.print("*| 2: Display Name Tag|*\n");
  Serial.print("*| 3: Game Link       |*\n");
  if(secretFlag == 1){
    Serial.print("*| 4: Secret Token    |*\n");
  }
  Serial.print("*| 0: Reset Badge     |*\n");
  Serial.print("*|                    |*\n");
  Serial.print("************************\n");

  Serial.print("Please enter input\n");
  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  char inputData = (char)Serial.read();
  Serial.print("Input: ");
  Serial.print(inputData);
  Serial.print("\n\n");

  for (;;)
  {
    switch (inputData)
    {
    case '1':
      delay(1000);
      Serial.print("You Chose to Set your Device Name!\n"); // DeviceID Input
      delay(1000);
      if (nameToggle == 0)
      {
        Serial.print("Jumping to setName...\n");
        delay(1000);
        setName();
      }
      else if (nameToggle = NAMESET)
      {
        Serial.print("YOU ALREADY SET YOUR NAME\n");
        Serial.print("Name: ");
        Serial.print(name);
        Serial.print("PLEASE CHOOSE ANOTHER FUNCTION\n");
        delay(1000);
      }
      goto statement;
    case '2':
      delay(1000);
      Serial.print("You Chose to Display your Device Name!\n"); // DeviceID Input
      delay(1000);
      Serial.print("Displaying Device Name on Badge\n");
      delay(1000);
      //displayName();
      goto statement;
    case '3':
      delay(1000);
      Serial.print("You Chose to Play the Game!\n"); // Game Link
      delay(1000);
      Serial.print("URL: ___________\n");
      delay(1000);
      goto statement;
    case '4':
      delay(1000);
      if(secretFlag == 0){
        Serial.print("Access Denied\n");
        goto statement;
      }
      else{
        Serial.print("Enter Secret Token:\n");
        //secret function
        goto statement;
      }
    case '9':
      delay(1000);
      secret();
      goto statement;
      
    case '0':
      delay(1000);
      resetBadge();
      if(startFlag == 1){
        goto statement;
      }
      else{
        return;
      }
      
    default:
      Serial.print("Invalid Statement\n");
      goto statement;
    }
  }
}

void resetBadge(){
  Serial.print("Reset Badge:\n");
  delay(1000);
  Serial.print("ARE YOU SURE YOU WANT TO RESET?\n");
  Serial.print("ALL SECRET PROGRESS WILL BE LOST\n\n");
  Serial.print("Please Press Button 1 for reset\n");
  Serial.print("Otherwise, Press Button 2\n");

  delay(200);
  while(true){
    if(push1.pressed()){
      Serial.print("RESETTING.....\n");
      delay(3000);
      startFlag = 0;
      secretFlag = 0;
      firstMenu = 0;
      nameToggle = 0;
      name = "";
      Serial.print("BADGE RESET\n");
      break;
    }
    else if(push2.pressed()){
      Serial.print("Badge Reset Aborted...\n");
      break;
    }
    else
    {
    }
  }
}

void secret(){
  Serial.print("Secret Unlocked\n");
  secretFlag = 1;
  return;
}

void displayName()
{
  return;
}

void setName()
{
  Serial.print("Please Enter A Name:\n");
  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  String inputData = Serial.readString();
  Serial.print("You entered ");
  Serial.print(inputData);
  name = inputData;
  nameToggle = NAMESET;
  Serial.print("\n");
  Serial.flush();
  return;
}

void loop()
{
  // put your main code here, to run repeatedly:

  delay(2000);
  const char *welcome[] = {
      "*****************BEWARE*******************",
      "*****************THERE********************",
      "******************IS**********************",
      "***************NO*ESCAPE******************",
      "╭╮╭╮╭┳━━━┳╮╱╱╭━━━┳━━━┳━╮╭━┳━━━╮╭━━━━┳━━━╮",
      "┃┃┃┃┃┃╭━━┫┃╱╱┃╭━╮┃╭━╮┃┃╰╯┃┃╭━━╯┃╭╮╭╮┃╭━╮┃",
      "┃┃┃┃┃┃╰━━┫┃╱╱┃┃╱╰┫┃╱┃┃╭╮╭╮┃╰━━╮╰╯┃┃╰┫┃╱┃┃",
      "┃╰╯╰╯┃╭━━┫┃╱╭┫┃╱╭┫┃╱┃┃┃┃┃┃┃╭━━╯╱╱┃┃╱┃┃╱┃┃",
      "╰╮╭╮╭┫╰━━┫╰━╯┃╰━╯┃╰━╯┃┃┃┃┃┃╰━━╮╱╱┃┃╱┃╰━╯┃",
      "╱╰╯╰╯╰━━━┻━━━┻━━━┻━━━┻╯╰╯╰┻━━━╯╱╱╰╯╱╰━━━╯",
      "╭╮╱╱╭┳━━━┳━━━━┳━━━┳━━━┳━╮╱╭╮",
      "┃╰╮╭╯┃╭━━┫╭╮╭╮┃╭━╮┃╭━╮┃┃╰╮┃┃",
      "╰╮┃┃╭┫╰━━╋╯┃┃╰┫┃╱╰┫┃╱┃┃╭╮╰╯┃",
      "╱┃╰╯┃┃╭━━╯╱┃┃╱┃┃╱╭┫┃╱┃┃┃╰╮┃┃",
      "╱╰╮╭╯┃╰━━╮╱┃┃╱┃╰━╯┃╰━╯┃┃╱┃┃┃",
      "╱╱╰╯╱╰━━━╯╱╰╯╱╰━━━┻━━━┻╯╱╰━╯",
      "******************************************",
      "******************************************",
      "******************************************",
      "******************************************",
  };
  
  if(startFlag == 0){ //On display welcome on startup, never again.
    for (int idx = 0; idx < sizeof(welcome) / sizeof(char); idx++)
    {
      Serial.print(welcome[idx]);
      Serial.print("\n");
    }
    startFlag = 1;
  }
  
  mainMenu();
}