#define b1 8
#define b2 9
#define rLED 4
#define gLED 5
int keyRead1,keyRead2, keyRls1=1, keyRls2=1, ledState1=0, ledState2=0;

void setup() {
  Serial.begin(9600);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT); 
}

void loop() {
 keyRead1= digitalRead(b1);
  //b= digitalRead(b2);


  if(keyRead1==0 and keyRls1==1){
    keyRls1=0;
    if(ledState1==0){
      digitalWrite(rLED, HIGH);
      ledState1=1;
    }
    else{
      digitalWrite(rLED, LOW);
      ledState1=0;
    }
  }

  else if(keyRead1==1 and keyRls1==0){
    keyRls1=1;
  }
  
  /*if(a==0 or b==0){
    digitalWrite(rLED, HIGH);
  }
  */

  /*if(a==b){
    digitalWrite(rLED, LOW);
  }

  else{
    digitalWrite(rLED, HIGH);
  }

  /*if(a==0 and b==0){
    digitalWrite(rLED, LOW);
  }*/



 keyRead2= digitalRead(b2);
  //b= digitalRead(b2);
     Serial.print(keyRead1);  Serial.print(keyRls1);  Serial.print(keyRls2);
  Serial.println(keyRead2);

  if(keyRead2==0 and keyRls2==1){
    keyRls2=0;
    if(ledState2==0){
      digitalWrite(gLED, HIGH);
      ledState2=1;
    }
    else{
      digitalWrite(gLED, LOW);
      ledState2=0;
    }
  }

  else if(keyRead2==1 and keyRls2==0){
    keyRls2=1;
  }
  delay(2);}

