/*
 *  Simple HTTP get webclient test
 */

const int sleepSeconds = 600;


#include <ESP8266WiFi.h>

const char* ssid     = "******"; //insert ssid ******
const char* password = "*******";  // insert password

const char* host = "api.thingspeak.com";

int uusiTila = 0, vanhaTila = 0;

void setup() {
  Serial.begin(115200);
  delay(100);
pinMode (5, INPUT);
  // We start by connecting to a WiFi network




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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thingtweet/1/statuses/update?api_key=9X14CF5SMEJ48I23&status=Hei @RasmusToivanen olen toiminnassa ";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
  
void loop() {
  uusiTila = digitalRead(5); // Jos tämä on 0 niin postia on laatikossa, jos 1 niin ei postia

  // Jos sensori havaitsee paketin, jota ei ole ennen ollut ->> posti saapunut
  if ((vanhaTila != uusiTila) && (uusiTila == 0)) {
    lahetys();
    vanhaTila = 1;
  }

  // jos ennen oli paketti ja nyt ei ole ->> posti haettu
  if ((vanhaTila == 0) && (uusiTila == 1)) {
    vanhaTila = 1;
  }
  
ESP.deepSleep(sleepSeconds * 1000000);


}


void lahetys() {
  delay(1000);


  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/apps/thingtweet/1/statuses/update?api_key=*********&status=Hei @ ";  // insert Api key from Thingspeak(Thingtweet) here
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
