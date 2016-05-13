
/***********************************************************
* Verify if there is data at BT if YES, storage at "command"
************************************************************/
 void checkBTcmd()  
 { 
   while (BT.available())   //Check if there is an available byte to read
   {
     delay(10); //Delay added to make thing stable 
     char c = BT.read(); //Conduct a serial read
     device += c; //build the string.
   }  
   if (device.length() > 0) 
   {
     Serial.print("Command received from BT ==> ");
     Serial.println(device); 
     command = device;
     device ="";  //Reset the variable
    } 
}



/***********************************************************
* Sound Generator
************************************************************/
void beep(int pin, int freq, long ms)   //square wave - freq ==> ms
{
  int i;
  long semiper = (long) (1000000/(freq*2));
  long loops = (long)((ms*1000)/(semiper*2));
  for (i=0;i<loops;i++){
    digitalWrite(pin, HIGH);  //set buzzer pin high
    delayMicroseconds(semiper);  //for half of the period
    digitalWrite(pin, LOW);   //set buzzer pin low
    delayMicroseconds(semiper);  //for the other half of the period
    }
}

/***************************************************
* Debouncing a key
****************************************************/
boolean debounce(int pin)
{
  boolean state;
  boolean previousState;
  const int debounceDelay = 60;
  
  previousState = digitalRead(pin);
  for(int counter=0; counter< debounceDelay; counter++)
  {
    delay(1);
    state = digitalRead(pin);
    if(state != previousState)
    {
      counter =0;
      previousState = state;
    } 
  }
  return state;
}

/***************************************************
* Display message at LCD
****************************************************/
void lcdMessage(String line1, String line2)
{
    lcd.begin(16, 2);
    lcd.print("                ");
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.print(line2);
}

