#define BT Serial1  
String command;
String device;

int time = 2000; // <== Could be necessary to adjust

/* Define Arm parameters to be used */

// MeArm 4-DOF
#define minGrip 15 
#define minBase 0 
#define minShou 60 
#define minElbw 60 

#define maxGrip 45 
#define maxBase 170
#define maxShou 180 
#define maxElbw 150 

#define midGrip 30
#define midBase 87
#define midShou 138
#define midElbw 100

/* SS 3-DOF
#define minGrip 75 
#define minBase 5 
#define minShou 5 
#define minElbw 0 

#define maxGrip 125 
#define maxBase 150
#define maxShou 155 
#define maxElbw 0 

#define midGrip 100
#define midBase 90
#define midShou 90
#define midElbw 0

/**************************************/

LiquidCrystal lcd(12, 11, 2, 4, 6, 8);

const int servoBasePin = 3;        // first servo - base
const int servoShouPin = 10;      // second servo - shouder
const int servoGripPin = 5;       // third servo - gripp
const int servoElbwPin = 9;      // forth servo (ELBOW - used at meArm)

const int recordPositionPin = 7;  // Button to record position
const int ledGreen = 13;          // LED to inform that a position was recorded

const int execTaskPin = 15;  // Button to record position
const int ledBlue =14;        // LED to inform that a recorded task is underway

const int ledYellow = 21; 
int remoteCommand = 0;

const int resetSwitchPin = 17;
int resetSwitch = 0; // 
const int ledRed = 20;        // LED to inform that a recorded task is aborted

const int joyBase = 2;      // Pot or Joystick used for Basemouth control
const int joyShou = 3;     // Pot or Joystick used for shouation control
const int potpin = 0;      // Pot used for Gripp control
const int joyElbw = 1;     // Pot used for Gripp control

const int buzzerPin = 16;   // 

int servoBaseVal;           // variables to read the value from the analog pin
int servoShouVal;           
int servoGripVal;  
int servoElbwVal;

int servoBasePastVal;       // variables to store the value from the analog pin at last loop
int servoShouPastVal;   
int servoGripPastVal;
int servoElbwPastVal;
int movement;

int recordPosition = 0;        // if HIGH, record servo position
int execTaskCmd = 0;              // if HIGH, run program

Servo myservoBase;  // create servo object to control a servo
Servo myservoShou;  // create servo object to control a servo
Servo myservoGrip;  // create servo object to control a servo
Servo myservoElbw;  // create servo object to control a servo

int gripPosition[100];
int basePosition[100];
int shouPosition[100];
int elbwPosition[100];

int positionIndex = 0;   // Index to be used at position array used for recorded tasks

