/*
 *  Simple HTTP get webclient test
 *  
 *  
 */

const int sleepSeconds = 6;
int postisaapumiset;

char* saapumisilmoitus[] = { "POSTI TULI @RasmusToivanen", "Halojata tuu hakee posti @RasmusToivanen", 
                                "POOOOSTIIIII @RasmusToivanen", "Wild Charizard appeared! @RasmusToivanen", 
                                "Minulla on sinulle jotakin... @RasmusToivanen", "Päivää @RasmusToivanen",
                                "Joku tunkee paperia @RasmusToivanen", "Syön kohta postisi @RasmusToivanen",
                                "Postie tulloo @RasmusToivanen", "Pate kävi taas @RasmusToivanen",
                                "Postin tuo, postin tuo... @RasmusToivanen", "Ja taas mainoksia... @RasmusToivanen"};

char* postityhja[] = {"Kiitos kun tyhjensit minut @RasmusToivanen", "Meinasin tukahtua oksennukseeni @RasmusToivanen", 
                        "AHHHHHH @RasmusToivanen", "Ja taas ootellaan @RasmusToivanen", "Ja tyhjänä jälleen @RasmusToivanen",
                        "Kiitos kun veit laskut mukanasi @RasmusToivanen", "En ois kestäny enää kauemmin @RasmusToivanen",
                        "Sepäs helpotti @RasmusToivanen", "Nauti lehdistäsi @RasmusToivanen", "Ensikertaan tv. postilaatikkosi @RasmusToivanen"};

char* toiminnassa[] = {"Olen kuningas! @RasmusToivanen", "Olen hengissä @RasmusToivanen", 
                        "Täällä jälleen @RasmusToivanen", "Ka jo oli aikakin, back in action @RasmusToivanen", 
                        "I'm here once again and functioning properly @RasmusToivanen", "Ja taas mennään @RasmusToivanen",
                        "Joo joo, oon hereillä! @RasmusToivanen", "Ei vielä, en jaksa toimia vielä @RasmusToivanen"};
#include <ESP8266WiFi.h>

/*NETGEARI
const char* ssid     ="***INSERT_SSID_HERE***";
const char* password = "***INSERT_PASS_HERE***";
*/

// PUHELIN
const char* ssid     = "***INSERT_SSID_HERE***";
const char* password = "***INSERT_PASS_HERE***";

const char* host = "api.thingspeak.com";

int uusiTila = 1, vanhaTila = 1;

void setup() {
  Serial.begin(115200);
  delay(100);
pinMode (D5, INPUT);
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
  int arpa = ( rand() % 8 ) ; //randomi väliltä 0-7
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=*****INSERT_API_KEY_HERE****&status=";
  strcat(url, toiminnassa[arpa]); 
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
  uusiTila = digitalRead(D5); // Jos tämä on 0 niin postia on laatikossa, jos 1 niin ei postia
  Serial.print("Sensorin arvo: ");
  Serial.println(uusiTila);
  // Jos sensori havaitsee paketin, jota ei ole ennen ollut ->> posti saapunut
  if ((vanhaTila != uusiTila) && (uusiTila == 0)) {
    lahetys();
    vanhaTila = 0;
  }

  // jos ennen oli paketti ja nyt ei ole ->> posti haettu
  if ((vanhaTila == 0) && (uusiTila == 1)) {
    vanhaTila = 1;
    haku();
  }
  
//ESP.deepSleep(1000);
delay(3600);

}


void lahetys() {
  delay(5000);


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
  //srand(time(NULL));
  int arpa = ( rand() % 12 ) ; //randomi väliltä 0-12
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=*****INSERT_API_KEY_HERE****"&status=";
  strcat(url, saapumisilmoitus[arpa]); 
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  //delay(3600000);
}

// tämä viesti tulee kun posti on haettu

void haku() {
  delay(5000);


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
  int arpa = ( rand() % 10 ) ; //randomi väliltä 0-9
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=9X14CF5SMEJ48I23&status=";
  strcat(url, postityhja[arpa]); 
  Serial.print("Requesting URL: ");
  Serial.println(url);

  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}



