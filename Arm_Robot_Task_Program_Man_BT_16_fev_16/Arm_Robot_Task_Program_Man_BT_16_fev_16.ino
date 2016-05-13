/*****************************************************************************************************************************
*  3 or 4-DOF Arm  Programming to perform a specific repetitive task

*  Programing local or remote using Android/BT
*  ==> In mode "Local" the servos are controled only by Potenciometers.
*  ==> In mode "Remote" the servos are controled only by Sliders at Android.
*  ==> Physical Switchs (Buttons) work in paralell with Android.
*  ==> Arm Robot Starts as "Local" mode control. Pressing "Alarm" or "Remote/Local" button at Android, will put in mode "Remote"
*  ==> Press button PROGRAM localy or at Android to Record a step (LED Grenn will light up)
*  ==> Press button RUN localy or at Android to execute sequencially the recorded steps, the "program" (LED blue will light up)
*  ==> Press button RESTART at Android to abort program (LED red will light up) - Note that should be at end of a completre pgm. 
*  ==> Servos Ranges can be defined at ArmDefines.h or at by Android app

Develop by Marcelo Jose Rovai
Please visit http://MJRoBot.org for more information
The Android app can be dowload free at Google Play Store: https://play.google.com/store/apps/details?id=appinventor.ai_mjrovai.MJRoBot_BT_ARM_CTRL_V2_1&hl=en
16Fev16
********************************************************************************************************************************/

#include <Servo.h>
#include <LiquidCrystal.h>
#include "ArmDefines.h"

void setup() 
{
  Serial.begin(9600);
  BT.begin(9600);
  
  lcdMessage("Arm Robot prog.", "   MJRoBot.org"); // Display message at LCD
  
  myservoBase.attach(servoBasePin);  // attaches the servo
  myservoShou.attach(servoShouPin);  // attaches the servo
  myservoGrip.attach(servoGripPin);  // attaches the servo
  myservoElbw.attach(servoElbwPin);  // attaches the servo
 
  pinMode (ledYellow, OUTPUT);
  pinMode (ledGreen, OUTPUT);
  pinMode (ledRed, OUTPUT);
  pinMode (buzzerPin, OUTPUT);
  pinMode (recordPositionPin, INPUT);
  pinMode (execTaskPin, INPUT);
  pinMode (resetSwitchPin, INPUT);
  
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, HIGH);
  
  armPositionZero(); //Put Arm at "position zero" that is define as "mid<servo>" position

  delay (time);  
  lcdArmPosition(); // Display Servo Positions at LCD
  outputPosition(); // Display Servo Positions at Serial Monitor
  
  warningStartTask();
  digitalWrite(ledGreen, HIGH);
}

void loop()
{ 
  checkBTcmd();
  defineLocalRemote();
  
  execTaskCmd = digitalRead (execTaskPin);
  if(execTaskCmd == HIGH || command == "runon")
  {
    runProgram();
  }
  else recArmPosition(); 
  command = "";
}


/***************************************************
* Defime mode Local / Remote
***************************************************/
void defineLocalRemote()
{
  if (command == "alarmon")
  {
    alarmRemoteCommand();
  }
  if (command == "remote")
  {
    remoteCommand = !remoteCommand;
    digitalWrite(ledYellow, !remoteCommand);
    BT.print("change command"); 
  }
}

/***************************************************
* Run Program
***************************************************/
void runProgram()
{ 
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledGreen, LOW);   
  executeTask();
  lcdArmPosition();
  outputPosition();
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, HIGH);   
}

/***************************************************
* Record Arm Positon
***************************************************/
void recArmPosition()
{
  recordPosition = debounce (recordPositionPin);
  if(recordPosition == HIGH || command == "pgmon")
  {
    positionIndex++;     
    gripPosition[positionIndex] = servoGripVal;
    basePosition[positionIndex] = servoBaseVal;
    shouPosition[positionIndex] = servoShouVal;
    elbwPosition[positionIndex] = servoElbwVal;
    digitalWrite(ledGreen, HIGH); 
    beep(buzzerPin, 1000, 100);
    serialMonitorArmPosition();
    lcdArmPgmPosition(positionIndex); 
    delay(1000);  
  }
  
  if (!remoteCommand && readPotenciometers())
  {
    lcdArmPosition();
    outputPosition();
    digitalWrite(ledGreen, LOW);
    armPosition(servoGripVal, servoBaseVal, servoShouVal, servoElbwVal);
    servoGripPastVal = servoGripVal;
    servoBasePastVal = servoBaseVal;
    servoShouPastVal = servoShouVal;
    servoElbwPastVal = servoElbwVal;
  }
  
  if (remoteCommand && readSliders())
  {
    lcdArmPosition();
    outputPosition();
    digitalWrite(ledGreen, LOW);
    armPosition(servoGripVal, servoBaseVal, servoShouVal, servoElbwVal);
    servoGripPastVal = servoGripVal;
    servoBasePastVal = servoBaseVal;
    servoShouPastVal = servoShouVal;
    servoElbwPastVal = servoElbwVal;
  }
}

/***************************************************
* Executed recorded task program
***************************************************/
void executeTask()
{
  int i;
  warningStartTask();
  resetSwitch = digitalRead(resetSwitchPin);
  while (resetSwitch == LOW)
  {
    for (i=1; i<=positionIndex; i++)
    {
      lcdArmPgmPosition(i); 
      armPosition(gripPosition[i], basePosition[i], shouPosition[i], elbwPosition[i]);
      delay (time);
    }
    i=0;
    checkBTcmd();
    Serial.println (command);
    if (command == "rston") {resetSwitch = HIGH;}
    else {resetSwitch = digitalRead(resetSwitchPin);}
  }
  digitalWrite(ledRed, HIGH);
  positionIndex = 0;
  BT.print("reset");
  warningFinishTask();
  armPositionZero();
} 

