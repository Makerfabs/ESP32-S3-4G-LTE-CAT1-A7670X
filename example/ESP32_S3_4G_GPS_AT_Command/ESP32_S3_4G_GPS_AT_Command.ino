#include <Arduino.h>

HardwareSerial mySerial2(2);

#define DEBUG true



#define IO_RXD2 47
#define IO_TXD2 48



// change this to match your SD shield or module;
// ESP32-S3 4G LTE: pin 10
const int PIN_SD_SELECT = 10;


#define IO_GSM_PWRKEY 4
#define IO_GSM_RST    5

unsigned long currentTime;


String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  mySerial2.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (mySerial2.available())
    {
      char c = mySerial2.read();
      response += c;
    }
  }
  if (debug)
  {
    USBSerial.print(response);
  }
  return response;
}


void setup() {
  // put your setup code here, to run once:
  USBSerial.begin(115200);
  USBSerial.print(F("Hello! ESP32-S3 AT command V1.0 Test"));
  mySerial2.begin(115200,SERIAL_8N1, IO_RXD2, IO_TXD2);
  pinMode(IO_GSM_RST, OUTPUT);
  digitalWrite(IO_GSM_RST, LOW);
  
  pinMode(IO_GSM_PWRKEY, OUTPUT);
  digitalWrite(IO_GSM_PWRKEY, HIGH);
  delay(3000);
  digitalWrite(IO_GSM_PWRKEY, LOW);
  
  USBSerial.println("ESP32-S3 4G LTE CAT1 Test Start!");
  delay(2000);
  delay(2000);
  USBSerial.println("Wait a few minutes for 4G star");
  delay(3000);
  sendData("AT", 1000, DEBUG);
  sendData("AT+CICCID", 1000, DEBUG);
  sendData("AT+SIMCOMATI", 1000, DEBUG);
  sendData("AT+COPS?", 1000, DEBUG); 
  sendData("AT+GMR", 1000, DEBUG); 

  #if 1
  //Get GNSS location  //GPS test
  sendData("AT+CGNSSPWR=1", 1000, DEBUG);// turn the GPS on //must wait about 10s for GPS on
  delay(12000); //Go on after shows +CGNSSPWR: READY!
  
  sendData("AT+CGNSSIPR=9600", 1000, DEBUG);//
  sendData("AT+CGNSSTST=1", 1000, DEBUG);
  sendData("AT+CGNSSINFO", 1000, DEBUG);//get GPS infomation
  #endif

#if 0
//  delay(2000);
//  delay(2000);
  delay(1000);
  //sendData("AT", 1000, DEBUG);
  delay(1000);
  sendData("AT", 1000, DEBUG);
  delay(1000);
  sendData("AT+SIMCOMATI", 1000, DEBUG);
  delay(1000);
  sendData("AT+CICCID", 1000, DEBUG);
  sendData("AT+CNUM", 1000, DEBUG);
  sendData("AT+COPS?", 1000, DEBUG);    
  sendData("AT+CPSI?", 1000, DEBUG);
  sendData("AT+CNMP?", 1000, DEBUG);
  
  //Http test
  sendData("AT+HTTPINIT", 1000, DEBUG);
  sendData("AT+HTTPPARA=\"URL\",\"https://ss0.bdstatic.com/5aV1bjqh_Q23odCf/static/mancard/css/card_min_dee38e45.css\"", 1000, DEBUG);
  sendData("AT+HTTPACTION=0", 1000, DEBUG);
  sendData("AT+CSQ", 1000, DEBUG);
  sendData("AT+HTTPHEAD", 1000, DEBUG);
  sendData("AT+HTTPREAD=0,500", 1000, DEBUG);
  sendData("AT+HTTPTERM", 1000, DEBUG);
#endif

//Make a call
#if 0
  sendData("ATD10086;", 1000, DEBUG);
  sendData("AT+COUTGAIN=2", 1000, DEBUG);//from (0-7)
  //sendData("AT+CHUP", 1000, DEBUG);//end the call
#endif
  sendData("AT+CICCID", 1000, DEBUG);
 
   currentTime = millis();
}

void loop() {

   if(millis()-currentTime>50000)
  {
      currentTime = millis();//refresh
      sendData("AT+CGNSSINFO", 1000, DEBUG);//get GPS infomation
  }
  while (USBSerial.available() > 0) {
    mySerial2.write(USBSerial.read());
    yield();
  }
  while (mySerial2.available() > 0) {
    USBSerial.write(mySerial2.read());
    yield();
  }
}
