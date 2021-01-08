#include <LWiFi.h>

int led1 = 7;
int led2 = 8;
boolean hit=false;
const int ctsPin_1=3;
const int ctsPin_2=4;
int num_1=15;
int num_2=60;
int num_3=90;
int score =0;
int ctsValue_1 =0;
int ctsValue_2 = 0;
char action = '0';  // 紀錄網址最後面的識別參數

//char wifi_ssid1[] = "HFU Guest";      //  your network SSID1 (name)
char wifi_ssid2[] = "feen";      //  your network SSID1 (name)
char wifi_pass2[] = "22558992";     // your network password for SSID2
int keyIndex = 0;                     // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);
 WiFiClient client;

//-------------------------------------------//

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ctsPin_1, INPUT);
  pinMode(ctsPin_2, INPUT);
  attachInterrupt(2,blink1,RISING);
  attachInterrupt(3,blink2,RISING);
  
 while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(wifi_ssid2);                  // print the network name (SSID1);   
    status= WiFi.begin(wifi_ssid2, wifi_pass2);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus(); 
  initial();
}
//-------------------------------------------//

void initial(){
   digitalWrite(led1,HIGH); 
   digitalWrite(led2,HIGH);
  Serial.println(ctsValue_1);
  Serial.println(ctsValue_2);
   Serial.println("----------Game Start----------");
   delay(2000);
}
//---------------------------------------------------------//
void blink1(){
 
  if(digitalRead(led1)== HIGH&& digitalRead(led2)== LOW ){
   
      score++;
      Serial.println(ctsValue_1);
      Serial.println(ctsValue_2);
      Serial.print("x=7     得分!!!");
      Serial.println(score);
     // client.print(score);   
      }
  if(digitalRead(led1)== HIGH && digitalRead(led2)== HIGH){
      score++;
      Serial.println(ctsValue_1);
      Serial.println(ctsValue_2);
      Serial.print("x=9     得分!!!");
      Serial.println(score);
      //client.print(score);   
      }
hit=true;
 }

//------------------------------------------------------//
void blink2(){
  
   if(digitalRead(led2)== HIGH &&digitalRead(led1)== LOW  ){
      score++;
      Serial.println(ctsValue_1);
      Serial.println(ctsValue_2);
      Serial.print("x=8     得分!!!");
      Serial.println(score);
      //client.print(score);   
      } 
hit=true;
 }
//------------------------------------------//

void loop() {

  digitalWrite(led1,LOW); 
  digitalWrite(led2,LOW);
  int mode;
//----------------------------------------//
client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // 依照識別參數傳送 HTTP Response 內容
          switch (action) {
              case 'q':
                mode='a';
                break;
               case 'w':
                 mode='s';
                 break;
                case 'e':
                 mode='d';
                 break;
              case 'S':
                client.print(score);
                break;
              default:
                // 若沒有識別參數則傳送預設的首頁內容
                client.print("Click <a href='/q'>here</a> to select mode 1<br>");
                client.print("Click <a href='/w'>here</a> to select mode 21<br>");
                client.print("Click <a href='/e'>here</a> to select mode 3<br>");
                client.print("Click <a href='/S'>here</a> to read score<br>");
              break;
          }

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check client request
        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        if (currentLine.startsWith("GET /q")) {  // GET /q to select mode 1
           action='q';    
        }
        if (currentLine.startsWith("GET /w")) {  // GET /w to select mode 2
           action='w';    
        }
        if (currentLine.startsWith("GET /e")) {  // GET /e to select mode 3
           action='e';    
        }
        if (currentLine.startsWith("GET /S")) {  // GET /S to read score
           action='S'; 
        }
           // check if returns are valid, if they are NaN (not a number) then something went wrong!
      
      }
    }
//-----------------------------------------//   
  //int mode;
  switch(mode){
//-----------------------------------------------//    
case 'a':
   Serial.println("-----模式一開始-----");
   delay(500);
   for(int i=0;i<num_1;i++){
  
  if (digitalRead(led1)== LOW && digitalRead(led2)== LOW){
  int x = random(7,10);
  //Serial.println(x);
  delay(1000);
  hit=false;
   int ctsValue_1 = digitalRead(ctsPin_1);  
   int ctsValue_2 = digitalRead(ctsPin_2);   
  
  if (x==7){
    digitalWrite(x,HIGH);
    delay(2000); 

    digitalWrite(x,LOW);
    //client.print(score);
    if (hit==false)
     Serial.println("MISS 7");
   
      }

  else if (x==8){
    digitalWrite(x,HIGH);
    delay(2000); 

    digitalWrite(x,LOW);
    //client.print(score);
    if (hit==false)     
      Serial.println("MISS 8");  
  
    }

else if (x==9){
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    delay(2000); 

   digitalWrite(7,LOW);
   digitalWrite(8,LOW);
   //client.print(score);
    if (hit==false)
    
     Serial.println("MISS 9");

}
}
 }
 delay(1000);
 Serial.println(score);
 client.print(score);
 action='S';
 Serial.println("--------End Game---------");
 score=0;
 break; 
  
//--------------------------------------------------//
   case 's':
   Serial.println("-----模式二開始-----");
   delay(500);
   for(int i=0;i<num_1;i++){
  
  if (digitalRead(led1)== LOW && digitalRead(led2)== LOW){
  int x = random(7,10);
  Serial.println(x);
  delay(1000);
  hit=false;
   int ctsValue_1 = digitalRead(ctsPin_1);  
   int ctsValue_2 = digitalRead(ctsPin_2);   
  
  if (x==7){
    digitalWrite(x,HIGH);
    delay(1000); 

    digitalWrite(x,LOW);
    if (hit==false)
     Serial.println("MISS 7");
   
      }

  else if (x==8){
    digitalWrite(x,HIGH);
    delay(1000); 

    digitalWrite(x,LOW);
    if (hit==false)     
      Serial.println("MISS 8");  
  
    }

else if (x==9){
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    delay(1000); 

   digitalWrite(7,LOW);
   digitalWrite(8,LOW);
    if (hit==false)
    
     Serial.println("MISS 9");
}
}
 }
 delay(1000);
 Serial.println("--------End Game---------");
 score=0;
 break;
//---------------------------------------------------//
    case 'd':
   Serial.println("-----模式三開始-----");
   delay(500);
   for(int i=0;i<num_1;i++){
  
  if (digitalRead(led1)== LOW && digitalRead(led2)== LOW){
  int x = random(7,10);
  Serial.println(x);
  delay(1000);
  hit=false;
   int ctsValue_1 = digitalRead(ctsPin_1);  
   int ctsValue_2 = digitalRead(ctsPin_2);   
  
  if (x==7){
    digitalWrite(x,HIGH);
    delay(500); 

    digitalWrite(x,LOW);
    
    if (hit==false)
     Serial.println("MISS 7");
   
      }

  else if (x==8){
    digitalWrite(x,HIGH);
    delay(500); 

    digitalWrite(x,LOW);
    if (hit==false)     
      Serial.println("MISS 8");  
  
    }

else if (x==9){
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    delay(500); 

   digitalWrite(7,LOW);
   digitalWrite(8,LOW);
    if (hit==false)
    
     Serial.println("MISS 9");
}
}
 }
 delay(1000);
 Serial.println("--------End Game---------");
 score=0;
 break;
//----------------------------------------------------//  
  
  }
//-------------------------------//

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
     //action ='0';
  
  }
}
//---------------------------------------//

//-----------------------------------------------//

//-------------------------------------------//
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
