#include <Arduino.h>
#include <string.h>
#define NAMESET 1

bool secret;
int nameToggle = 0;
int buttonPin = PUSH1;
int buttonPin2 = PUSH2;
int val = 0;
int val2 = 0;

// Function Prototypes
void mainMenu();

void setName();

int displayName();

int playGame();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUSH1, INPUT_PULLUP);
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
  Serial.print("*|                    |*\n");
  Serial.print("************************\n");

  Serial.print("Please enter input\n");
  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  int inputData = Serial.read();
  Serial.print("You entered ");
  Serial.print(inputData);
  Serial.print("\n");

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
        Serial.print("PLEASE CHOOSE ANOTHER FUNCTION\n");
        delay(1000);
      }
      goto statement;
    case '2':
      delay(1000);
      Serial.print("You Chose to Display your Device Name!\n"); // DeviceID Input
      delay(1000);
      displayName();
      goto statement;
    case '3':
      delay(1000);
      Serial.print("You Chose to Play the Game!\n"); // Game Link
      // PRINT URL HERE
      delay(1000);
      goto statement;
    default:
      Serial.print("Invalid Statement\n");
      goto statement;
    }
  }
}
int displayName()
{
  int val2 = 0;
  val = digitalRead(PUSH1);
  val2 = digitalRead(PUSH2);
  while (true)
  {
    if (val == HIGH || val2 == HIGH)
    {
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

  for (int idx = 0; idx < sizeof(welcome) / sizeof(char); idx++)
  {
    Serial.print(welcome[idx]);
    Serial.print("\n");
  }

  mainMenu();
  
}