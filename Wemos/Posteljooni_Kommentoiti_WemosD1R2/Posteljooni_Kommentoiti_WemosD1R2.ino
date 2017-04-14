// Listat joissa mahdolliset twitterilmoitukset

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

#include <ESP8266WiFi.h> // Kirjasto internetyhteyden käyttämiseksi

// Rasmuksen puhelimen wifin tunnus ja salasana :)
const char* ssid     = "rt";
const char* password = "R4ZZ392!";

const char* host = "api.thingspeak.com"; // Nettisivu jonka APIn kautta saadaan viestit twitteriin

int uusiTila = 1, vanhaTila = 1; // Alustetaan kaksi muuttujaa

void setup() {
  pinMode (D5, INPUT); // pinni D5 inputiksi
  
  WiFi.begin(ssid, password); // Yhdistetään Rasmuksen puhelimeen

  // Odotetaan kunnes saadaan yhteys:
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
  }
  
  // WiFiClient päälle, portiksi 80, tarkistetaan että yhteys saatu
  WiFiClient client;
  const int httpPort = 80; // http portiksi 80
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  // Arvotaan joku ilmoitus ja laitetaan se twitteriin
  int arpa = ( rand() % 8 ) ; //randomi väliltä 0-7
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=9X14CF5SMEJ48I23&status=";
  strcat(url, toiminnassa[arpa]); 
  // nyt muuttuja "url" on internetosoite muotoa api.thingspeak.com/apps/.....&status=LÄHETETTÄVÄVIESTI
  
  // Käydään kyseisessä osoitteessa, jolloin viesti lähtee twitteriin
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
}

// Aloitetaan looppi:
void loop() {
  uusiTila = digitalRead(D5); // Jos tämä on 0 niin postia on laatikossa, jos 1 niin ei postia

  // Jos sensori havaitsee paketin, jota ei ole ennen ollut ->> posti saapunut ja lähetetään viesti twitteriin
  if ((vanhaTila != uusiTila) && (uusiTila == 0)) {
    lahetys();
    vanhaTila = 0;
  }

  // jos ennen oli paketti ja nyt ei ole ->> posti haettu, laitetaan ilmoitus haetusta postistakin twitteriin
  if ((vanhaTila == 0) && (uusiTila == 1)) {
    vanhaTila = 1;
    haku();
  }
  
// pieni viive 
delay(3600);

} // Looppi päättyy tähän


// Alla määritelty aliohjelma nimeltä lahetys()
void lahetys() {
  
  // WiFiClient päälle ja yhdistys
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  // Luodaan taas nettiosoite+viesti jolla saadaan viesti twitteriin
  int arpa = ( rand() % 12 ) ; //randomi väliltä 0-12
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=9X14CF5SMEJ48I23&status=";
  strcat(url, saapumisilmoitus[arpa]); 
  
  // Mennään siihen internetosoitteeseen
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1500); //pieni viive aikaa yhdistää

} // aliohjelma päättyy


// Alla vastaavasti määritelty aliohjelma joka lähettää postin hakemisesta tulevan viestin
void haku() {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  int arpa = ( rand() % 10 ) ;
  char url[150] = "/apps/thingtweet/1/statuses/update?api_key=9X14CF5SMEJ48I23&status=";
  strcat(url, postityhja[arpa]); 
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1500);
}

// Tässä kaikki mitä tarvittiin, Yhteensä noin 120 riviä koodia (sisältäen tyhjät rivit ja kommenttirivit)

// Mitä kaikkea sitä pystytäänkään tekemään 10 000 tai miljoonalla rivillä?

