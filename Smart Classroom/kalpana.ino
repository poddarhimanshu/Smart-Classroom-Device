#include<DS3231.h>
#include<String.h>

byte relayPin=9;
byte relayFan=12;
byte inPin=2;
byte ldrSensor=A0;
byte pirPin = 7; 

byte previous=LOW;
byte fanState=LOW;
byte state=LOW;
byte reading;
byte flag=0;

long samay=0;
long debounce=200;
int calibrationTime = 15;

long unsigned int pause = 5000;  
long unsigned int lowIn;  
long stime=0;       

boolean lockLow = true;
boolean takeLowTime;

// clock initialization
DS3231  rtc(SDA, SCL);

void setup() 
{
	// initial state
	digitalWrite(relayPin, HIGH);
	digitalWrite(relayFan, HIGH);
	// set pin modes
	pinMode(relayPin, OUTPUT);
	pinMode(ldrSensor, INPUT);
	pinMode(relayFan, OUTPUT);
	rtc.begin();

	// for debugging
	Serial.begin(9600);
	Serial.print("calibrating sensors ");
	for(int i = 0; i < calibrationTime; i++)
	{
	  Serial.print(".");
	  delay(1000);
	}

	Serial.println("Done...");
	Serial.println("SENSORS ACTIVE");
	delay(50);

	digitalWrite(relayPin,HIGH);
	digitalWrite(relayFan,HIGH);

	// set time for the clock 
	rtc.setDOW(TUESDAY);   
	rtc.setTime(18,28,00);
	rtc.setDate(24,10,2017);

 
}

void loop()
{
	/* Below values can be used for debugging purposes
	* Serial.println(rtc.getDOWStr());
	* Serial.print("---- ");
	* Serial.print(rtc.getDateStr());
	* Serial.println(" -- ");
	* Serial.println(rtc.getTimeStr());
	* Serial.print("Temperature: ");
	* Serial.print(rtc.getTemp());
	* Serial.println(" C");
	*/
	
	clockRelay();
	pushRelay();
	ldrSensor();
	tempRelay();
	checkPIR();
}
void clockRelay()
{
	// only turn off on weekdays
	if( (!strcmp(rtc.getDOWStr(),"Monday")) || (!strcmp(rtc.getDOWStr(),"Tuesday")) || (!strcmp(rtc.getDOWStr(),"Wednesday")) || (!strcmp(rtc.getDOWStr(),"Thursday")) || (!strcmp(rtc.getDOWStr(),"Friday")) )
	{
		// for demonstration purpose session timings are chosen 10s apart
		if(!strcmp(rtc.getTimeStr(),"18:28:10"))
		{
			fanState = state = HIGH;
		}
		if(!strcmp(rtc.getTimeStr(),"18:28:20"))
		{
			fanState = state = HIGH;
		}
		if(!strcmp(rtc.getTimeStr(),"18:28:30"))
		{
			fanState = state = HIGH;
		}
	}
	digitalWrite(relayPin, state);
}

void pushRelay()
{
	reading=digitalRead(inPin);
	if( reading == HIGH && previous == LOW && millis()-samay > debounce)
	{
		if(state == LOW)
			state = HIGH;
		else
			state = LOW;
		samay = millis();
		fanState = state; 
	}
	
	digitalWrite(relayPin, state);
	digitalWrite(relayFan, fanState);
	previous = reading;
}
void ldrSensor()
{
	unsigned int sunIntensity;
	sunIntensity = analogRead(ldrSensor);
	// Serial.print(sun);
	if(sunIntensity < 100)
		state = HIGH;

	digitalWrite(relayPin,state);
}

void tempRelay()
{
	//Serial.print(rtc.getTemp());
	if(rtc.getTemp()>35)
	fanState = HIGH;
	digitalWrite(relayFan,fanState);
}

//passive infra red function
void checkPIR()
{
    if(digitalRead(pirPin) == HIGH)
	{
		if(lockLow)
		{  
			 //makes sure we wait for a transition to LOW before any further output is made:
			 lockLow = false;            
			 Serial.println("---");
			 Serial.print("motion detected at ");
			 Serial.print(millis()/1000);
			 Serial.println(" sec"); 
			 stime=(millis()/1000);
			 delay(50);
		 }         
         takeLowTime = true;
    }
	Serial.println(rtc.getTimeStr());
    if(digitalRead(pirPin) == LOW)
	{       
		if(takeLowTime)
		{
			lowIn = millis();          //save the time of the transition from high to LOW
			takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
		//if the sensor is low for more than the given pause, 
		//we assume that no more motion is going to happen
		if(!lockLow && millis() - lowIn > pause)
		{  
           //makes sure this block of code is only executed again after a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
       }
    }
	// If no motion is encountered in the next 30seconds turn off the loads in the classroom
    if(((millis()/1000)-stime)>30)
	{
		state=HIGH;
		fanState=HIGH;
	}
	digitalWrite(relayPin, state);
	digitalWrite(relayFan,fanState);
}

