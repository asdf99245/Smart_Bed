#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12


int SEND_UP_CODE = 182012;
int SEND_DOWN_CODE =154783;
int step_number=0; 
int recvd;

void setup() {
   Serial.begin(9600);
   
  // put your setup code here, to run once:
  pinMode(STEPPER_PIN_1,OUTPUT);
  pinMode(STEPPER_PIN_2,OUTPUT);
  pinMode(STEPPER_PIN_3,OUTPUT);
  pinMode(STEPPER_PIN_4,OUTPUT);
}

void loop(){
  
 

   
      for(int i=0;i<500;i++){
        Serial.println("aaaaa");
        OneStep(true);
      }
    
    
   
      for(int i=0;i<500;i++){
        Serial.println("bbbbb");
           //159반시계
        OneStep(false);
      }
    
  

}

void OneStep(bool dir){
//Serial.println("one step");
  if(dir){
      switch(step_number){
      case 0:
      //Serial.println("**************************");
      digitalWrite(STEPPER_PIN_1,HIGH);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
      case 1:
      //Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,HIGH);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
      
      case 2:
      //Serial.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,HIGH);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
      
      case 3:
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,HIGH);
      break;
    }
  }
  else{
    switch(step_number){
      case 0:
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,HIGH);
      break;
      case 1:
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,HIGH);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
      
      case 2:
      digitalWrite(STEPPER_PIN_1,LOW);
      digitalWrite(STEPPER_PIN_2,HIGH);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
      
      case 3:
      digitalWrite(STEPPER_PIN_1,HIGH);
      digitalWrite(STEPPER_PIN_2,LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
      digitalWrite(STEPPER_PIN_4,LOW);
      break;
    }
  }
  step_number++;
  if(step_number>3){
    step_number=0;
  }
}
