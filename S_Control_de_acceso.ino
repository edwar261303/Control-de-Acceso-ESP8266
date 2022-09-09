#include <ESP8266WiFi.h>
 
const char* ssid = "MZKXBTOOM-2.4GHz";       
const char* password = "mzkx7266";  

int c=2;
String contraseña="1234";
String ingresado="";
 
int ledPermitdo = 14; // GPIO14
int ledDenegado = 12; // GPIO12
int foco=5;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPermitdo, OUTPUT);
  pinMode(ledDenegado, OUTPUT);
  pinMode(foco, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 

  String request = client.readStringUntil('\r');
  Serial.println(request);  
  if(request[5]!='f' && request[5]!=' ')
  {
    ingresado+=request[5];
    
    if(ingresado==contraseña){
      c=1;
      ingresado="";
    }
    if(ingresado.length()==4){
      c=0;
      ingresado="";
    }    
    if(request[5]=='0'){
      c=2;
      ingresado="";
    }
  }
  Serial.println("----"+ingresado+"----");
  client.flush();
  

 

 

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("<h1 align=center>CONTROL DE ACCESO");

  if(c == 1){
      digitalWrite(ledPermitdo, HIGH); 
      digitalWrite(foco, LOW);
      client.print("<input type='image' src='https://i.imgur.com/3NHrnAF.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/0'>");
      }
  if(c == 0){ 
      digitalWrite(ledDenegado, HIGH);
      digitalWrite(foco, HIGH);
      client.print("<input type='image' src='https://i.imgur.com/uaOptWK.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/0'>");              
      }
  
  if(c==2){
    digitalWrite(ledPermitdo, LOW);
    digitalWrite(ledDenegado, LOW);
    digitalWrite(foco, HIGH);  
    client.print("<table> <tbody> <tr></tr><tr></tr><tr></tr>");
    client.print("<tr>");
    client.print("<td><input type='image' src='https://i.imgur.com/mLStsAy.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/1'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/TQYYeGe.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/2'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/8Ay4Lfm.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/3'> <td>");
    client.print("</tr><tr>");
    client.print("<td><input type='image' src='https://i.imgur.com/4mIPCe8.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/4'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/H6rtEEz.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/5'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/a1cutWx.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/6'> <td>");
    client.print("</tr><tr>");
    client.print("<td><input type='image' src='https://i.imgur.com/LZ4dHGv.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/7'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/hffIGyz.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/8'> <td>");
    client.print("<td><input type='image' src='https://i.imgur.com/xkkgHsn.jpg' style='display:block; margin:auto' width='30%' onClick=location.href='/9'> <td>");
    client.print("</tr></tbody></table>");
  }
  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
