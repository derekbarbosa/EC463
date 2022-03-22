#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <Button.h>
#include <HardwareSerial.h>
#include <LiquidCrystal.h>



#define NAMESET 1
#define NAMELEN 128

//2.5 & 2.6 TX & RX
// 1.2, 1.3, 2.7, 2.4, 1.7, 1.6, 5v Ground.
//Chage LEDs to other digital


// Set Up LiquidCrystal Object
LiquidCrystal lcd = LiquidCrystal(10,9,8,7,6,5);

// Set Up PushButtons using Button.h
Button push1(PUSH1);
Button push2(PUSH2);


// Establish Flags to place in FRAM
int startFlag PLACE_IN_FRAM;
int secretFlag PLACE_IN_FRAM;
int nameToggle PLACE_IN_FRAM;
int secretFlag2 PLACE_IN_FRAM;
int secretFlag3 PLACE_IN_FRAM;
int secretFlag4 PLACE_IN_FRAM;
int wrongFlag PLACE_IN_FRAM;

char name[NAMELEN] PLACE_IN_FRAM;
char secret_word[NAMELEN] PLACE_IN_FRAM;

// Booleans for BT Setup
bool bleSetup1 = false;
bool bleSetup2 = false;

String yes = "yes";

//
byte Skull[8] = {
0b00000,
0b01110,
0b10101,
0b11011,
0b01110,
0b01110,
0b00000,
0b00000
};

// Function Prototypes
void clearStr();

void setName();

void mainMenu();

void setStr();

void displayName();

void secret();

void resetBadge();

void secretCode2();

void secretCode();

void secretCode3();

void wipeBoard();

void bluetooth();

void bleName();

void blePassword();

void writeString(String s);

void clearStr(char* str){
  for(int i = 0; i < NAMELEN; i++)
    str[i] = '\0';
}

void setStr(String x, char* str){
  char new_name[NAMELEN];
  x.toCharArray(new_name, NAMELEN);
  for(int i = 0; i < NAMELEN; i++)
    str[i] = new_name[i];
}

void setup()
{
  // put your setup code here, to run once:

  push1.begin();
  push2.begin();
  lcd.begin(16,2);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.setTimeout(2000);



  pinMode(P3_1, OUTPUT);
  pinMode(P2_1, OUTPUT);
  pinMode(P2_0, OUTPUT);

  
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < 15; i++)
  {
    Serial1.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}// end writeString

void ledCheck(){
  if(secretFlag2 == 1){
    digitalWrite(P3_1, secretFlag2);
  }
  else if(secretFlag2 == 0){
    digitalWrite(P3_1, secretFlag2);
  }
  if(secretFlag3 == 1){
    digitalWrite(P2_1, secretFlag3);
  }
  else if(secretFlag3 == 0){
    digitalWrite(P2_1, secretFlag3);
  }
  if(secretFlag4 == 1){
    digitalWrite(P2_0, secretFlag4);
  }
  else if(secretFlag4 == 0){
    digitalWrite(P2_0, secretFlag4);
  }
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
  Serial.print("*| 5: Game Link 2     |*\n");
  if(secretFlag == 1 && secretFlag2 == 1){
    Serial.print("*| 6: Secret Token 2  |*\n");
  }
  if(secretFlag == 1 && secretFlag2 == 1 && secretFlag3 == 1){
    Serial.print("*| 7: Secret Token 3  |*\n");
  }
  Serial.print("*| 8: Start Bluetooth |*\n");
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
      Serial.print("You Chose to Set your Device Name!\n");// DeviceID Input
      delay(1000);
      if (nameToggle == 0)
      {
        Serial.print("Jumping to setName...\n");
        delay(1000);
        setName();
      }
      else if (nameToggle == NAMESET)
      {
        Serial.print("YOU ALREADY SET YOUR NAME\n");
        Serial.print("Name: ");
        Serial.print(name);
        Serial.print("\n");
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
      Serial.print(name);
      Serial.print("\n");
      //displayName();
      goto statement;
    case '3':
      delay(1000);
      Serial.print("You Chose to Play the Game!\n"); // Game Link
      delay(1000);
      Serial.print("URL:\n");
      Serial.print("shorturl.at/advFT\n");
      delay(1000);
      goto statement;
    case '4':
      delay(1000);
      if(secretFlag == 0){
        Serial.print("Access Denied\n");
        goto statement;
      }
      else{
        if(secretFlag2 == 1){
          Serial.print("Secret already unlocked\n");
          goto statement;
        }
        secretCode();
        goto statement;
      }
    case '5':
      delay(1000);
      Serial.print("You Chose to Play the Game!\n"); // Game Link
      delay(1000);
      Serial.print("URL:\n");
      Serial.print("shorturl.at/lxIL6\n");
      delay(1000);
      goto statement;
    case '6':
      delay(1000);
        if(secretFlag == 0 || secretFlag2 == 0){
          Serial.print("Access Denied\n");
          goto statement;
        }
        else{
          if(secretFlag3 == 1){
            Serial.print("Secret already unlocked\n");
            goto statement;
          }
          secretCode2();
          goto statement;
        }

    case '7':
      delay(1000);
      if(secretFlag == 0 || secretFlag2 == 0 || secretFlag3 == 0){
          Serial.print("Access Denied\n");
          goto statement;
      }
      else{
          if(secretFlag4 == 1){
            Serial.print("Secret already unlocked\n");
            goto statement;
          }
          secretCode3();
          goto statement;
      }

    case '8':
      delay(1000);
      Serial.print("Bluetooth Entered\n");
      Serial.print("Exit Bluetooth Menu to Return\n\n\n");
      bluetooth();
      goto statement;
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


void bluetooth(){
  
    
  statement:
      Serial.print("Welcome to Bluetooth\n");
      Serial.print("Your Device Should Automatically Connect to the Closest VETCON BADGE\n");
      Serial.print("Type 1 to Start Communication: \n");
      Serial.print("Type 0 to Exit: \n");
      while(Serial.available() == 0)
      {
        // THIS BLOCK STAYS EMPTY!
      }
      char inputData = (char)Serial.read();
      Serial.print("You entered ");
      Serial.print(inputData);
      Serial.print("\n\n");
      // char badgePassowrd[] = "AT+PSWD=";
      // strcat(badgePassowrd,inputData.c_str());

      for(;;){
        switch (inputData)
        {
        case '1':
        {
          delay(1000);
          Serial.print("Type to send to other badge\n");
          while(Serial.available() == 0)
          {
        // THIS BLOCK STAYS EMPTY!
          }
          String toSend = Serial.readString();

          //Serial.print("got inside case 1\n");
          writeString(toSend);
          if(Serial1.available()){
            //Serial.print("got inside Serial1\n");
            //String incomingData = Serial1.readString();
            String dataIn = Serial1.readString();

            //Serial.print(incomingData);
            Serial.print("Data Received: ");
            Serial.print(dataIn);
            Serial.print("\n");
          }
          break;
        }
        case '0':
          delay(1000);
          return;
        default:
          Serial.print("Invalid Menu Item\n");
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
      SYSCFG0 = FRWPPW | DFWP;
      startFlag = 0;
      secretFlag = 0;
      nameToggle = 0;
      secretFlag2 = 0;
      secretFlag3 = 0;
      secretFlag4 = 0;
      clearStr(name);
      SYSCFG0 = FRWPPW | PFWP | DFWP;
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
  SYSCFG0 = FRWPPW | DFWP;
  secretFlag = 1;
  SYSCFG0 = FRWPPW | PFWP | DFWP;
  return;
}

void secretCode3(){
  char answer[] = "ilovevetcon";
  Serial.print("Please Enter the Secret Code:\n");

  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  String inputData = Serial.readStringUntil('\n');
  if(inputData == answer){
    Serial.print("CONGRATS! SECRET 3 SOLVED\n");
    
    SYSCFG0 = FRWPPW | DFWP;
    secretFlag4 = 1;
    SYSCFG0 = FRWPPW | PFWP | DFWP;
    digitalWrite(P2_0, secretFlag4);
  }
  else{
    Serial.print("INCORRECT CODE\n");
  }
  return;
}

void secretCode(){
  
  char answer[] = "1016";
  Serial.print("Please Enter The Secret Code:\n");
  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  String inputData = Serial.readStringUntil('\n');
  if(inputData == answer){
    Serial.print("CONGRATS! SECRET 1 SOLVED\n");
    
    SYSCFG0 = FRWPPW | DFWP;
    secretFlag2 = 1;
    SYSCFG0 = FRWPPW | PFWP | DFWP;
    digitalWrite(P3_1, secretFlag2);
  }
  else{
    Serial.print("INCORRECT CODE\n");
  }
  return;

}

void secretCode2(){
  char answer[] = "semperdisco";
  char wrong[] = "3411323115333443242344234424521532244442453454141544431152543131111542453454";
  Serial.print("Please Enter The Secret Code:\n");
  while (Serial.available() == 0)
  {
    // THIS BLOCK STAYS EMPTY!
  }
  String inputData = Serial.readStringUntil('\n');
  if(inputData == answer){
    Serial.print("CONGRATS! SECRET 2 SOLVED\n");
    
    SYSCFG0 = FRWPPW | DFWP;
    secretFlag3 = 1;
    SYSCFG0 = FRWPPW | PFWP | DFWP;
    digitalWrite(P2_1, secretFlag3);
  }
  else if(inputData == wrong){
    for(int i = 0; i < 50; i++){
      Serial.print("THIS IS NOT A GAME\n");
    }
    SYSCFG0 = FRWPPW | DFWP;
    clearStr(secret_word);
    //setStr(x, secret_word);
    wrongFlag = 1;
    SYSCFG0 = FRWPPW | PFWP | DFWP;
    wipeBoard();
  }
  else{
    Serial.print("INCORRECT CODE\n");
  }
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
  String inputData = Serial.readStringUntil('\n');
  //Serial.print(inputData);
  //Serial.print("\n");
  char secretString1[] = "Pepe";
  
  char secretAnswer1[] = 
"\n⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠟⠛⠻⠿⣿⣿⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⣿⣿⠟⠉⠄⠄⠄⠄⠄⠄⠄⠉⢟⠉⠄⠄⠄⠄⠄⠈⢻⣿⣿⣿⣿⣿\n⣿⣿⣿⣿⡿⠃⠄⠄⠤⠐⠉⠉⠉⠉⠉⠒⠬⡣⠤⠤⠄⠄⠄⠤⠤⠿⣿⣿⣿⣿\n⣿⣿⣿⣿⠁⠄⠄⠄⠄⠄⠄⠠⢀⡒⠤⠭⠅⠚⣓⡆⡆⣔⡙⠓⠚⠛⠄⣹⠿⣿\n⣿⠟⠁⡌⠄⠄⠄⢀⠤⠬⠐⣈⠠⡤⠤⠤⣤⠤⢄⡉⢁⣀⣠⣤⣤⣀⣐⡖⢦⣽\n⠏⠄⠄⠄⠄⠄⠄⠄⠐⠄⡿⠛⠯⠍⠭⣉⣉⠉⠍⢀⢀⡀⠉⠉⠉⠒⠒⠂⠄⣻\n⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠩⠵⠒⠒⠲⢒⡢⡉⠁⢐⡀⠬⠍⠁⢉⣉⣴⣿⣿\n⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⢉⣒⡉⠁⠁⠄⠄⠉⠂⠙⣉⣁⣀⣙⡿⣿⣿\n⠄⠄⠄⠄⠄⠄⠄⠄⢠⠄⡖⢉⠥⢤⠐⢲⠒⢲⠒⢲⠒⠲⡒⠒⡖⢲⠂⠄⢀⣿\n⠄⠄⠄⠄⠄⠄⠄⠄⠈⢆⡑⢄⠳⢾⠒⢺⠒⢺⠒⠚⡖⠄⡏⠉⣞⠞⠁⣠⣾⣿\n⠄⠄⠄⠄⠄⠄⢆⠄⠄⠄⠈⠢⠉⠢⠍⣘⣒⣚⣒⣚⣒⣒⣉⠡⠤⣔⣾⣿⣿⣿\n⠷⣤⠄⣀⠄⠄⠄⠈⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣤⣾⣿⣿⣿⣿⣿\n⠄⠄⠉⠐⠢⠭⠄⢀⣒⣒⡒⠄⠄⠄⠄⠄⠄⣀⡠⠶⢶⣿⣿⣿⣿⣿⣿⣿⣿⣿\n⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠁⠈⠄⠄⠄⠄⠄⠄⠈⠻⣿⣿⣿⣿⣿⣿⣿\n";
  char secretString2[] = "Senior Design";
  char secretAnswer2[] = "\n   _____            _               ____            _           \n  / ___/___  ____  (_)___  _____   / __ \\___  _____(_)___ _____ \n  \\__ \\/ _ \\/ __ \\/ / __ \\/ ___/  / / / / _ \\/ ___/ / __ `/ __ \\ \n ___/ /  __/ / / / / /_/ / /     / /_/ /  __(__  ) / /_/ / / / /\n/____/\\___/_/ /_/_/\\____/_/     /_____/\\___/____/_/\\__, /_/ /_/ \n                                                  /____/        \n";
  if(inputData == secretString1){
    Serial.print(secretAnswer1);
  }
  if(inputData == secretString2){
    Serial.print(secretAnswer2);
  }
  
  Serial.print("You entered ");
  Serial.print(inputData);
  SYSCFG0 = FRWPPW | DFWP;
  setStr(inputData, name);
  nameToggle = NAMESET;
  SYSCFG0 = FRWPPW | PFWP | DFWP;
  Serial.print("\n");
  Serial.flush();
  return;
}

void wipeBoard(){
  SYSCFG0 = FRWPPW | DFWP;
  startFlag = 0;
  secretFlag = 0;
  nameToggle = 0;
  secretFlag2 = 0;
  secretFlag3 = 0;
  wrongFlag = 0;
  clearStr(name);
  SYSCFG0 = FRWPPW | PFWP | DFWP;

  return;
}

void loop()
{
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);

  ledCheck();
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
    SYSCFG0 = FRWPPW | DFWP;
    startFlag = 1;
    SYSCFG0 = FRWPPW | PFWP | DFWP;
  }
  
  mainMenu();
}