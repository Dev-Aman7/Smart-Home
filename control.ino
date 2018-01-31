#include<SPI.h>
#include<Ethernet.h>
int pir=8;
int led=5;
int led1=6;
int led2=7;
int buzzer=3;
int s=0;
int p=0;
int motion;
int tv=2;

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};


// enter the ip address according to your system. (open cmd ,type ipconfig,check your ip, change the last tuple)
EthernetServer server(12345);
IPAddress ip(  192,168,43,150);



String request;


void homeMode()
{


   motion=digitalRead(pir);

  EthernetClient client = server.available();
  if(client)
  {
    Serial.println("Client is trying to connect......");
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        request.concat(c);
        if(c=='\n'){
        Serial.print(request);
        if(request.indexOf("ON")>0){
          digitalWrite(tv,HIGH);
          Serial.println("ON");
          }

          else if(request.indexOf("OFF")>0){
            digitalWrite(tv,LOW);
            Serial.println("OFF");
            }
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Refresh: 2");  // refresh the page automatically every 5 sec
        client.println();

        client.println("<!doctype html>");
        client.println("<html>");
        
        client.println("<head><title>homeMode</title></head>");
      
        client.println("<head><h1 style = ' text-align:center'>Smart home</h1>");
        client.print("<!DOCTYPE HTML><html><body style ='background-color:powderblue;' ><a href ='/?LED_ON'><p style = ' text-align:center'>LED ON</p></a><br><a href ='/?LED_OFF'><p style = ' text-align:center'>LED OFF</P></a><br></body></html>" );
            
            if (motion==1 && p==0)
             {
               Serial.println("motion detected");
     
               p=1;
               }
             else if(motion ==0 && p==1)
            {
              s=s+1;
              p=0;
              Serial.print("number of persons  ");
              
   
               Serial.println(s);
  
           }
           if(s>=1 && s<=3)
           {
             if (s==1)
             {
              digitalWrite(led,HIGH);
             }
             else if (s==2)
             {
              digitalWrite(led,HIGH);
              digitalWrite(led1,HIGH);
             }
             else
             {
              digitalWrite(led,HIGH);
              digitalWrite(led1,HIGH);
              digitalWrite(led2,HIGH);
             }
           }
           client.print("number of person ");
           client.println(s);
           client.println("</br>");
            int tem=analogRead(A1);
            int ldr=analogRead(A0);
            client.println("Temperature ");
            
            client.print(" is ");
            client.print(tem*0.041);
            
            client.println("<br />");
            client.print("luminisity is ");
            client.print(ldr);
            client.println("<br />");
          
        client.println("</html>");
        client.stop();
        request="";
        
      }
      }
     }
      
  }
  }

void intruderMode()
{

  int motion=digitalRead(pir);

  EthernetClient client = server.available();
  if(client)
  {
    Serial.println("Client is trying to connect......");
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        request.concat(c);
        if(c=='\n'){
        Serial.print(request);
        if(request.indexOf("ON")>0){
          digitalWrite(tv,HIGH);
          Serial.println("ON");
          }

          else if(request.indexOf("OFF")>0){
            digitalWrite(tv,LOW);
            Serial.println("OFF");
            }
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Refresh: 2");  // refresh the page automatically every 5 sec
        client.println();

        client.println("<!doctype html>");
        client.println("<html>");
        client.println("<head><title>IntruderMode</title></head>");
        client.println("<head><h1 style = ' text-align:center'>Smart home</h1>");
        client.print("<!DOCTYPE HTML><html><body style ='background-color:red;' ><a href ='/?LED_ON'><p style = ' text-align:center'>HOUSE ALARM ON</p></a><br><a href ='/?LED_OFF'><p style = ' text-align:center'>HOUSE ALARM OFF</P></a><br></body></html>" );
            
            if (motion==1 && p==0)
             {
               Serial.println("motion detected");
     
               p=1;
               }
             else if(motion ==0 && p==1)
            {
              s=s+1;
              p=0;
              Serial.print("number of persons  ");
              
   
               Serial.println(s);
  
           }
           client.println("</br>");

           
           if(s>0)
           {

             digitalWrite(3,HIGH);
           }
           client.print("Intruder detected   number of person ");
           client.println(s);
           client.println("</br>");
            int tem=analogRead(A1);
            int ldr=analogRead(A0);
            client.println(" Temperature ");
            
            client.print(" is ");
            client.print(tem*0.041);
            
            client.println("<br />");
            client.print("luminisity is ");
            client.print(ldr);
            client.println("<br />");
          
        client.println("</html>");
        client.stop();
        request="";
        
      }
      }
     }
      
  }
}
  




int n=0;
String si;


void setup(){
  Ethernet.begin(mac,ip);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial.print("HI");
  Serial.println(Ethernet.localIP());
   while(Serial.available()==0)
 {
  
 }
si=Serial.readString();
if(si=="homeMode")
{
  Serial.println("You have selected homeMode");
  homeMode();
  n=1;
}

else if(si=="intruderMode")
{
  Serial.println("You have selected IntruderMode");
  intruderMode();
  n=2;
  
}
else
{
  Serial.println("WrongInput ......Try again.......");
  si="";
 
  }
}
void loop()
{

  if(n==1)
  {
    
    homeMode();
  }
  else if(n==2)
  {
    
    intruderMode();
  }
  
 }
                                                                                                                                                                                                                                          // Code Written by Aman 
