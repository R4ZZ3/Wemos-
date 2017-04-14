#include <SoftwareSerial.h>

SoftwareSerial esp8266(2, 3); // RX, TX
#include <Wire.h>
int digitalpin = 4; // Pinni johon "silmän" musta johto tulee Arduinossa


char pass[12] = "\"R4ZZ392!\"";
char ssid[12] = "\"rt\"";
char TCP[12]  = "\"TCP\"";
char API[30]  = "\"api.thingspeak.com\"";


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


//// ALOITETAAN OHJELMA JA MÄRITETÄÄN VAADITTAVAT ASETUKSET
pinMode(4, INPUT);
  Serial.println("Started");
  esp8266.begin(9600);
  if (esp8266.available())
    Serial.write(esp8266.read());
  delay(2000);
  esp8266.println("AT\r\n");
  Serial.println("AT");
  delay(1000);
  esp8266.println("AT+CWMODE=3");
    delay(2000);
    esp8266.println("AT+CIPMUX=1");
    delay(2000);
  esp8266.println("AT+CIPMODE=0");

 //// TÄSSÄ YHDISTETÄÄN ESP8266 ALUSSA MÄÄRITELTYYN TUKIASEMAAN 
  char yhdistys[50] = "AT+CWJAP=";
  strcat(yhdistys, ssid);
  strcat(yhdistys, ",");
  strcat(yhdistys, pass);
  strcat(yhdistys, "\n");
  esp8266.println(yhdistys);
  Serial.println(yhdistys);
  delay(7000);

ilmoitus(); 

  Serial.println("looppiin");
  delay(2000);
}
  

void loop() {
int luearvo = digitalRead(4);
Serial. println(luearvo);
delay(10000);
if (luearvo == 0)
  ilmoitus();
}


void ilmoitus() {
  Serial.println("kohta pitäs lähteä jotain mualimalle");
   char thingspeak[80] = "AT+CIPSTART=0,";
  strcat(thingspeak, TCP);
  strcat(thingspeak, ",");
  strcat(thingspeak, API);
  strcat(thingspeak, ",80");
  esp8266.println(thingspeak);
  Serial.println(thingspeak);
  delay(500);
  esp8266.println("AT+CIPSEND=0,110");
  Serial.println("AT+CIPSEND=0,110");
  delay(1000);
  esp8266.println("GET /apps/thingtweet/1/statuses/update?LTVFCBSELWDPNJ6J&status=Hei, olen Rasmus Toivasen ja H_kauppilan tweettaava postilaatikko");
  for (int i=0;i<7;i++) {  
    delay(1000);
  esp8266.println("");
  }
}
