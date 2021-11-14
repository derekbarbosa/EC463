#include <Arduino.h>
#include <string.h>
#define NAMESET 1

int startFlag = 0;
int secretFlag = 0;
int firstMenu = 0;
int nameToggle = 0;
int buttonPin = PUSH1;
int buttonPin2 = PUSH2;
int val = 0;
int val2 = 0;
String name = "";
String yes = "yes";

// Function Prototypes
void mainMenu();

void setName();

int displayName();

int playGame();

void secret();

void resetBadge();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  //pinMode(PUSH2,INPUT_PULLUP);
  //delay(500);
  
}

int playGame()
{
}

void mainMenu()
{
  // Serial.write(12);


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
      //displayName();
      goto statement;
    case '3':
      delay(1000);
      Serial.print("You Chose to Play the Game!\n"); // Game Link
      // PRINT URL HERE
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
      //goto statement;
      return;
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
  Serial.print("Please Enter: 'yes' for reset\n");
  Serial.print("Otherwise, press any key\n");

  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  Serial.flush();
  String inputData = Serial.readString();
  Serial.print("You entered \n");
  Serial.print(inputData);
  Serial.print(yes);
  Serial.print("\n");
  if(inputData == yes){
    Serial.print("RESETTING.....\n");
    delay(3000);
    startFlag = 0;
    secretFlag = 0;
    firstMenu = 0;
    nameToggle = 0;
    name = "";
    Serial.print("BADGE RESET\n");
    return;
  }
  else{
    return;
  }
}

void secret(){
  Serial.print("Secret Unlocked\n");
  secretFlag = 1;
  return;
}

int displayName()
{
  
  val = digitalRead(PUSH1);
  val2 = digitalRead(PUSH2);
  Serial.print(val);
  Serial.print("\n");
  Serial.print(val2);
  Serial.print("\n");
  
  while (true)
  {
    if (val == HIGH || val2 == HIGH)
    {
      Serial.print("Nothing Pushed");
    }
    else{
      Serial.print("Button Pushed\n");
      Serial.print(val);
      Serial.print(val2);
      Serial.print("\n");
      Serial.flush();
      break;
    }
  }
  return 0;
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
  val = digitalRead(PUSH1);
  val2 = digitalRead(PUSH2);

  
  if(firstMenu == 0){
    firstMenu = 1;
    mainMenu();
  }
  else{
    Serial.print("Hold Both Buttons to Return to Menu\n");
    if (val == LOW && val2 == LOW)
    {
      mainMenu();
    }
  }
  
}