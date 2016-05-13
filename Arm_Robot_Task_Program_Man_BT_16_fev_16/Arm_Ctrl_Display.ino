/***************************************************
* Read and Map sliders at Android for Servos positioning
***************************************************/
bool readSliders()
{
  char armServo = command[0];  
     byte value = command[2];  
     //Serial.print(armServo);  
    // Serial.println(value);  
     
     if ( armServo == 'g')  
     {  
       servoGripVal = value;
       servoGripVal = map(servoGripVal, 0, 255, minGrip, maxGrip); // scale it to use it with the servo 
     }  
     if ( armServo == 'b')  
     {  
       servoBaseVal = value;  
       servoBaseVal = map(servoBaseVal, 0, 255, minBase, maxBase);     // scale it to use it with the servo 
     } 
     if ( armServo == 's')  
     {  
       servoShouVal = value; 
       servoShouVal = map(servoShouVal, 0, 255, minShou, maxShou);     // scale it to use it with the servo 
     } 
     if ( armServo == 'e')  
     {  
       servoElbwVal = value; 
       servoElbwVal = map(servoElbwVal, 0, 255, minElbw, maxElbw);     // scale it to use it with the servo  
     }
     
  if (servoGripVal != servoGripPastVal || servoBaseVal != servoBasePastVal || servoShouVal != servoShouPastVal || servoElbwVal != servoElbwPastVal)
  {
    movement = true;
  }else movement = false;
  return movement;
}

/***************************************************
* Read and Map Potenciometers for Servos positioning
***************************************************/
bool readPotenciometers()
{
  servoGripVal = analogRead(potpin);  
  servoGripVal = map(servoGripVal, 0, 1023, minGrip, maxGrip); // scale it to use it with the servo 

  // Read the Basemouth value  (value between 0 and 1023)
  servoBaseVal = analogRead(joyBase);        
  servoBaseVal = map(servoBaseVal, 0, 1023, minBase, maxBase);     // scale it to use it with the servo 
  // Read the shouation value  (value between 0 and 1023)
  servoShouVal = analogRead(joyShou);         
  servoShouVal = map(servoShouVal, 0, 1023, minShou, maxShou);     // scale it to use it with the servo 
 
 // Read the elbow value  (value between 0 and 1023)
  servoElbwVal = analogRead(joyElbw);         
  servoElbwVal = map(servoElbwVal, 0, 1023, minElbw, maxElbw);     // scale it to use it with the servo  
  
  if (servoGripVal != servoGripPastVal || servoBaseVal != servoBasePastVal || servoShouVal != servoShouPastVal || servoElbwVal != servoElbwPastVal)
  {
    movement = true;
  }else movement = false;
  return movement;
}

/***************************************************
* Read and Map Potenciometers at begginging 
***************************************************/
void readPotenciometersInitial()
{
  servoGripVal = analogRead(potpin);  
  servoGripVal = map(servoGripVal, 0, 1023, minGrip, maxGrip); // scale it to use it with the servo 

  // Read the Basemouth value  (value between 0 and 1023)
  servoBaseVal = analogRead(joyBase);        
  servoBaseVal = map(servoBaseVal, 0, 1023, minBase, maxBase);     // scale it to use it with the servo 
  // Read the shouation value  (value between 0 and 1023)
  servoShouVal = analogRead(joyShou);         
  servoShouVal = map(servoShouVal, 0, 1023, minShou, maxShou);     // scale it to use it with the servo 
 
 // Read the elbow value  (value between 0 and 1023)
  servoElbwVal = analogRead(joyElbw);         
  servoElbwVal = map(servoElbwVal, 0, 1023, minElbw, maxElbw);     // scale it to use it with the servo 
  
  servoBasePastVal = servoBaseVal;
  servoShouPastVal = servoShouVal;
  servoGripPastVal = servoGripVal;
  servoElbwPastVal = servoElbwVal;
  
  outputPosition();
}

/***************************************************
* Put Arm at given position
***************************************************/
void armPosition(int gripp, int basee, int shouder, int elbow )
{
  myservoGrip.write(gripp);   
  delay(15);  
  myservoBase.write(basee);   
  delay(15);    
  myservoShou.write(shouder);   
  delay(15);  
  myservoElbw.write(elbow);   
  
  delay(15);  
}

/***************************************************
* Put Arm at "position zero"
***************************************************/
void armPositionZero()
{
  servoBaseVal = midBase;
  servoShouVal = midShou;
  servoGripVal = midGrip;
  servoElbwVal = midElbw;
  
  myservoBase.write(servoBaseVal);   
  delay(15);   
  myservoShou.write(servoShouVal);   
  delay(15);  
  myservoGrip.write(servoGripVal);   
  delay(15);  
  myservoElbw.write(servoElbwVal);   
  delay(15);  
  
  servoBasePastVal = servoBaseVal;
  servoShouPastVal = servoShouVal;
  servoGripPastVal = servoGripVal;
  servoElbwPastVal = servoElbwVal;
}

/*************************************************
* Display Servo Positions at Serial Monitor
**************************************************/
void outputPosition()
{
    Serial.print("   Gripp: ");
    Serial.print (servoGripVal);  
    Serial.print("   Base: ");
    Serial.print(servoBaseVal);
    Serial.print("   Shoulder: ");
    Serial.print(servoShouVal);
    Serial.print("   Elbow: ");
    Serial.println (servoElbwVal);   
}

/**************************************************
* Print at Serial Monotor the actual Arm Position
***************************************************/
void serialMonitorArmPosition()
{  
   
   Serial.print("Position ==>");
   Serial.print(positionIndex);
   Serial.print("   Gripp: ");
   Serial.println(gripPosition[positionIndex]);
   Serial.print("   Base: ");
   Serial.print(basePosition[positionIndex]);
   Serial.print("   Shoulder: ");
   Serial.print(shouPosition[positionIndex]);
   Serial.print("   Elbow: ");
   Serial.println(elbwPosition[positionIndex]);
}

/***************************************************
* Display Arm Position ar LCD
****************************************************/
void lcdArmPosition()
{
    lcd.begin(16, 2);
    lcd.print("Grp Bas Sho Elw ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print(servoGripVal);
    
    lcd.setCursor(4, 1);
    lcd.print("   ");
    lcd.setCursor(4, 1);
    lcd.print(servoBaseVal);
    
    lcd.setCursor(8, 1);
    lcd.print("   ");
    lcd.setCursor(8, 1);
    lcd.print(servoShouVal);   
    
    lcd.setCursor(12, 1);
    lcd.print("   ");
    lcd.setCursor(12, 1);
    lcd.print(servoElbwVal);
}


/***************************************************
* Display Arm proggramed Position (steps) at LCD
****************************************************/
void lcdArmPgmPosition(int pos)
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);  
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("Position # ");
    lcd.setCursor(12, 0);
    lcd.print("   ");
    lcd.setCursor(12, 0);
    lcd.print(pos);
    
    lcd.setCursor(0, 1);
    lcd.print("                ");
 
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print(servoGripVal);
    
    lcd.setCursor(4, 1);
    lcd.print("   ");
    lcd.setCursor(4, 1);
    lcd.print(servoBaseVal);
    
    lcd.setCursor(8, 1);
    lcd.print("   ");
    lcd.setCursor(8, 1);
    lcd.print(servoShouVal);   
    
    lcd.setCursor(12, 1);
    lcd.print("   ");
    lcd.setCursor(12, 1);
    lcd.print(servoElbwVal);
}

/***********************************************************
* Warning with sound start of a programed task
************************************************************/
void warningStartTask()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("WARNING PGM INIT");
  lcd.setCursor(0, 1);  
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("<<<<<<<<>>>>>>>>");
  
  for (int cont=30; cont<100; cont++)
  { // Play Music
    beep(buzzerPin, 10*cont, 10);
  }
  for (int cont=100; cont>30; cont--)
  {
    beep(buzzerPin, 10*cont, 10);
  }  
  for (int cont=30; cont<100; cont++)
  { // Play Music
    beep(buzzerPin, 10*cont, 10);
  }
  for (int cont=100; cont>30; cont--)
  {
    beep(buzzerPin, 10*cont, 10);
  }
  
  for(int cont = 0; cont < 3; cont++){   //Bip 2 times
    beep(buzzerPin, 1000, 100);
    delay(100);
  }
  
}

/***********************************************************
* Warning with sound  the start programming a new task
************************************************************/
void warningFinishTask()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(" Start New PGM ");
  lcd.setCursor(0, 1);  
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(">>>>>>><<<<<<<<<");
  
  for (int cont=30; cont<100; cont++)
  { // Play Music
    beep(buzzerPin, 5*cont, 10);
  }
  for (int cont=100; cont>30; cont--)
  {
    beep(buzzerPin, 5*cont, 10);
  }  
  for (int cont=30; cont<100; cont++)
  { // Play Music
    beep(buzzerPin, 10*cont, 10);
  }
  for (int cont=100; cont>30; cont--)
  {
    beep(buzzerPin, 10*cont, 10);
  }
  
  for(int cont = 0; cont < 3; cont++){   //Bip 2 times
    beep(buzzerPin, 1000, 300);
    delay(100);
  }  
}

/***********************************************************
* Alarm command received
************************************************************/
void alarmRemoteCommand()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("REMOTE - CONTROL");
  lcd.setCursor(0, 1);  
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("<<<<<<<<>>>>>>>>");
  
  for (int cont=30; cont<100; cont++){ // Play Music
    beep(buzzerPin, 10*cont, 10);
  }
  for (int cont=100; cont>30; cont--){
    beep(buzzerPin, 10*cont, 10);
  }
  
  for (int cont=30; cont<100; cont++){ // Play Music
    beep(buzzerPin, 10*cont, 10);
  }
  for (int cont=100; cont>30; cont--){
    beep(buzzerPin, 10*cont, 10);
  }
  
  lcd.setCursor(0, 0);  
  lcd.print("     Start      ");;
  lcd.setCursor(0, 1);  
  lcd.print("   Programing   ");
  
  command = "remote";
  remoteCommand = 0;
}


