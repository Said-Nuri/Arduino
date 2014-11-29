#define MIN_INTR 20
#define MAX_INTR 500

float INTR_RATE = ((float)MIN_INTR)/MAX_INTR;
int pin = 7;
int readPin = 0;
int intrpNum1 = 0;
int intrpNum2 = 1;
float accRate;

boolean flag = false;
boolean brakeFlag = false;

unsigned long previusTime = 0;
unsigned long currentTime = 0;
unsigned long timeDif;

volatile int state = RISING;

// the setup routine runs once when you press reset:
void setup() {                
  // 9600 BAUD
  Serial.begin(9600); 
  pinMode(pin, INPUT);
  attachInterrupt(intrpNum1, callback1, FALLING);
  attachInterrupt(intrpNum2, callback2, RISING);
}

// the loop routine runs over and over again forever:
void loop() {
  readPin = digitalRead(pin);
  
  if(readPin == 0){
    Serial.println("Brake!");
    delay(100);
  }
  
  delay(100);               // wait for a second
}

void callback1(){

  if(flag == true){
    flag = false;
  }else{
    flag = true;
  }
  previusTime= millis();
  
}
  
void callback2(){
  
  if(flag){
    currentTime = millis();
    timeDif = (currentTime - previusTime);
    
    if((timeDif > MIN_INTR) && (timeDif < MAX_INTR)){
      Serial.print("rate: %");
      accRate = 100-((timeDif-MIN_INTR)*(100.0/MAX_INTR));
      //accRate = (accRate-20)*(100.0/80);
      Serial.println(accRate);
      flag = false;
    }else if((timeDif < MAX_INTR)){
      //Serial.print("too fast!");
      //Serial.println(timeDif);
    }else{
      Serial.print("too slow!");
      Serial.println(timeDif);
    }
  }
}
