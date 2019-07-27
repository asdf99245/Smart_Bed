
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(169, 254, 95, 29);
//169.254.95.29

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
int idx;
char c;

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

#define DEBUG true

 //not pin num
#define TEMPER_ON_CODE 1     
#define TEMPER_OFF_CODE 2   
#define LIGHT_ON_CODE 3       
#define LIGHT_OFF_CODE 4    
#define MOVE_UP_CODE 5        
#define MOVE_DOWN_CODE 6       
#define TEMPER_UP_CODE 7
#define TEMPER_DOWN_CODE 8


#define TEMPER_RED_LED 5
#define TEMPER_GREEN_LED 6
#define TEMPER_BLUE_LED 7

#define LIGHT_SSR_ALG A0
#define LIGHT_LED 8

bool lightPinAct=true;
bool temperPinAct=true;
bool temperChanged= false;

int cur_red_light ,cur_blue_light;
int SEND_UP_CODE = 182012;
int SEND_DOWN_CODE =154783;

int lightValue;   //  조도센서에 입력된 빛의 세기
bool isVertical=false;  //침대 기울기 false: 수평

 
void setup() {
  Serial.begin(9600);
 

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  pinMode(LIGHT_LED, OUTPUT);
  digitalWrite(LIGHT_LED, LOW);
  
  pinMode(TEMPER_RED_LED,OUTPUT);
  pinMode(TEMPER_GREEN_LED,OUTPUT);
  pinMode(TEMPER_BLUE_LED,OUTPUT);
}
 
void loop() {

  EthernetClient client = server.available();

  Serial.println("before if");
   
  if (client) {
 
    while (client.connected()) {
      
      if (client.available()) {
   
        c = client.read();
        
        if (idx == 1){
          break;
        }
        
        if(c == '=' ) {
          idx++;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1000);
   
 
    idx=0;

    int commandCode= c-'0';
  
    
    if(commandCode == TEMPER_ON_CODE) {
        
        if(temperPinAct==true){
         // Serial.println("temparture function is already on ");
        }
        
        else{
          temperPinAct=true;
         // Serial.println("temparture function turned on");
        }
    }

    else if(commandCode == TEMPER_OFF_CODE) {
   
        if(temperPinAct==true){
          temperPinAct=false;
          temperChanged=false;
         // Serial.println("temparture function turned off");
        }
        
        else{
          //Serial.println("temparture function is already off");
        }
    }

    else if(commandCode == TEMPER_UP_CODE){
        if(temperPinAct==true){
          temperControlFunction(true);               // true: 온도 높이기
          temperChanged=true;
        }
    }

    else if(commandCode ==TEMPER_DOWN_CODE){
        if(temperPinAct=true){
          temperControlFunction(false);        
          temperChanged=true;          
        }
    }
      
    else if(commandCode == LIGHT_ON_CODE){
        
        if(lightPinAct==true){
          //Serial.println("light function is already on");
        }
        
        else{
          lightPinAct=true;
          //Serial.println("light function turned on");
        }
    }

    else if(commandCode == LIGHT_OFF_CODE){

        if(lightPinAct==true){
          lightPinAct=false;
          //Serial.println("light function turned off");
        }
        else{
          //Serial.println("light function is already off");
        }
    }

    else if(commandCode == MOVE_UP_CODE){
        if(isVertical==false){
          sendBedMoveCode(true);
          isVertical=true;
          //Serial.println("bed was folded");
        }
        else{
          //Serial.println("bed is already folded");
        }
    }

    else if(commandCode == MOVE_DOWN_CODE){
        if(isVertical==true){
          sendBedMoveCode(false);
          isVertical=false;
          //Serial.println("bed was unfolded");
        }
        else{
          //Serial.println("bed is already unfolded");
        }
    }

    client.stop();
  }
  
  if(temperChanged==true){
    analogWrite(TEMPER_BLUE_LED,cur_blue_light);
    analogWrite(TEMPER_RED_LED,cur_red_light);
    analogWrite(TEMPER_GREEN_LED,0);
  }
  
  else if(temperPinAct==true){
    temperFunction();
  }

  else{
    analogWrite(TEMPER_BLUE_LED,0);
    analogWrite(TEMPER_RED_LED,0);
    analogWrite(TEMPER_GREEN_LED,0);
    Serial.println("temperature function off");
  }
  
  if(lightPinAct==true){
    lightFunction();
  }

  else{
    digitalWrite(LIGHT_LED, LOW);
    Serial.println("auto light function off");
  }
}

void temperFunction(){
  
  
  int tmp = dht.readTemperature();
  Serial.print("temperature : ");
  Serial.println(tmp);

  if(tmp <= 28){
    analogWrite(TEMPER_BLUE_LED,255);
    analogWrite(TEMPER_RED_LED,0);
    analogWrite(TEMPER_GREEN_LED,0);
    cur_red_light=0;
    cur_blue_light=255;
  }
  else if(tmp <= 31){
    analogWrite(TEMPER_GREEN_LED,0);
    analogWrite(TEMPER_RED_LED,127);
    analogWrite(TEMPER_BLUE_LED,127);
    cur_red_light=127;
    cur_blue_light=127;
  }
  else{
    analogWrite(TEMPER_RED_LED,255);
    analogWrite(TEMPER_BLUE_LED,0);
    analogWrite(TEMPER_GREEN_LED,0);
    cur_red_light=255;
    cur_blue_light=0;
  }
 delay(1000);
}

void lightFunction(){
  Serial.print("light:");
  
  lightValue =  analogRead(LIGHT_SSR_ALG);
  Serial.println(lightValue);
  
  if(lightValue<700){
    digitalWrite(LIGHT_LED,LOW);
  }
  else{
    digitalWrite(LIGHT_LED,HIGH);
  }
  delay(1000);
}

void sendBedMoveCode(bool upOrDown){

  if(upOrDown == true)
    Serial.write(SEND_UP_CODE);      
  else
    Serial.write(SEND_DOWN_CODE);
}



void temperControlFunction(bool isGoHigh){
  int r,b;
  
  if(isGoHigh==true){
    for( r = cur_red_light, b= cur_blue_light  ; r < cur_red_light+100  ,b >  cur_blue_light-100 ; r++,b--){
      analogWrite(TEMPER_RED_LED, r);
      analogWrite(TEMPER_BLUE_LED, b);
      analogWrite(TEMPER_GREEN_LED,0);
    }
  }

  else{
    for( r=cur_red_light, b=cur_blue_light; r > cur_red_light-100 ,b < cur_blue_light+100 ; r--,b++){
      analogWrite(TEMPER_RED_LED, r);
      analogWrite(TEMPER_BLUE_LED, b);
      analogWrite(TEMPER_GREEN_LED,0);
    }
  }
   
   cur_red_light = r > 255 ? 255 : r;
   cur_red_light = r < 0 ? 0 : r;
   
   cur_blue_light= b > 255 ? 255 : b;
   cur_blue_light = b < 0 ? 0 : b;
}



