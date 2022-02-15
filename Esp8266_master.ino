#include <ESP8266WiFi.h>
#include <Wire.h>
const char* ssid     = "DIGI_k1lb";
const char* passwd = "@D1ff3r3nt";
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;
WiFiServer server(80);
IPAddress ip(192, 168, 1, 6);
IPAddress gateway(192, 168, 1, 1);
String in_raw = ""; //sample: GET /A,255,28,119,0,0,255,255,255,0,0,105,182,255,0,0,3,133,206,Z,#ff1c77,#ffffff,#69b6ff
int prefix = 0;
int suffix = 0;
char raw_charArray[100];
String cut_String = "";


int numArray[30];
int pos = 0;
int id = 0;
int id2 = 0;
String NUMS = "0";
int strLength=0;
int asd = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(4);
  delay(10);
  Serial.print(F("Static IP: "));
  Serial.println(ip);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("WiFi connected");
  server.begin();
  Serial.print(WiFi.localIP());}
  
String website ="<!DOCTYPE html><html><head><link rel=\"icon\" href=\"https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Flogos-download.com%2Fwp-content%2Fuploads%2F2019%2F01%2FJavaScript_Logo.png&f=1&nofb=1\"><title>My Room</title><link rel=\"stylesheet\" type=\"text/css\" href=\"https://rbence07.github.io/led/theme.css\"><script src=\"https://cdn.jsdelivr.net/npm/@jaames/iro@5\"></script><script async src='/cdn-cgi/bm/cv/669835187/api.js'></script></head><body><center><div class=\"wrapper-div\"><div class=\"elements\"><div class=\"elements-content\"><h2>CURTAIN</h2><p>STATUS</p><div class=\"curtain-div\"><input id=\"curtain_1\" class=\"slider\" type=\"range\" min=\"0\" max=\"4\" value=\"0\" onchange=\"curtain_1()\"></div></div><div class=\"elements-content\"><h2>TABLE LAMP</h2><p>BRIGHTNESS</p><div class=\"brightness-div\"><input id=\"brightness_4\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"brightness_4()\"></div></div><div class=\"elements-content\"><h2>BED LAMP</h2><p>BRIGHTNESS</p><div class=\"brightness-div\"><input id=\"brightness_5\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"brightness_5()\"></div></div><div class=\"mobile\"><div class=\"elements-content\"><a href=\"#\" id=\"change_color\" role=\"button\">CHANGE COLOR</a></div></div></div><div class=\"elements\"><div class=\"elements-content\"><h2>RIGHT LAMP</h2><div id=\"picker1\" style=\"padding:10px\"></div><p>BRIGHTNESS</p><div class=\"brightness-div\"><input id=\"brightness_1\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"brightness_1()\"></div><p>COLOR TEMPERATURE</p><div class=\"kelvin-div\"><input id=\"kelvin_1\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"kelvin_1()\"></div></div><div class=\"mobile\"><div class=\"elements-content\"><a href=\"#\" id=\"change_color\" role=\"button\">CHANGE COLOR</a></div></div></div><div class=\"elements\"><div class=\"elements-content\"><h2>MIDDLE LAMP</h2><div id=\"picker2\" style=\"padding:10px\"></div><p>BRIGHTNESS</p><div class=\"brightness-div\"><input id=\"brightness_2\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"brightness_2()\"></div><p>COLOR TEMPERATURE</p><div class=\"kelvin-div\"><input id=\"kelvin_2\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"kelvin_2()\"></div></div><div class=\"mobile\"><div class=\"elements-content\"><a href=\"#\" id=\"change_color\" role=\"button\">CHANGE COLOR</a></div></div><div class=\"desktop\"><div class=\"elements-content\"><a href=\"?r\" class=\"reset\" role=\"button\">RESET</a></div></div></div><div class=\"elements\"><div class=\"elements-content\"><h2>LEFT LAMP</h2><div id=\"picker3\" style=\"padding:10px\"></div><p>BRIGHTNESS</p><div class=\"brightness-div\"><input id=\"brightness_3\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"brightness_3()\"></div><p>COLOR TEMPERATURE</p><div class=\"kelvin-div\"><input id=\"kelvin_3\" class=\"slider\" type=\"range\" min=\"0\" max=\"255\" value=\"0\" onchange=\"kelvin_3()\"></div></div><div class=\"mobile\"><div class=\"elements-content\"><a href=\"#\" id=\"change_color\" role=\"button\">CHANGE COLOR</a></div></div></div></div><p id=\"text\"></p></center><script src=\"https://rbence07.github.io/led/code.js\"></script><script type=\"text/javascript\">(function(){window['__CF$cv$params']={r:'6d6d7a85a8556852',m:'veKnGhFwfUWpi9ImJmOvWWg5rxizWDzZ8nbdZrZrBz4-1643742613-0-Acu4nw6o9PN0tYavF59zSkqKLCyPaI0A/laIllshTsl7+zWii9k0Hx5WBISeV9ch6Uki0i3z19YcKkz+eisTFjFpduG8Ea3ielZBKzclYclZQ3xHTGzYmTZiXxkI5iDgt5ORyMqqWAELsPwBazWUDsN5l7yoNYbkp9GHKC3mcCXNMDNCBvoC9LZtQl9zLTMsyA==',s:[0x5647a12d67,0x7d47bc444a],}})();</script></body></html>";
void loop(){
  WiFiClient client = server.available();
  if (client) {
    currentTime = millis();previousTime = currentTime;String currentLine = "";
    //Serial.println("New Client.");
    while (client.connected() && currentTime - previousTime <= timeoutTime) {            // loop while the client's connected
      currentTime = millis();
      if (client.available()) {
        char in_char = client.read();
        in_raw += in_char;
        if (in_char == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");client.println("Content-type:text/html");client.println("Connection: close");client.println();client.println(website);client.println();
            if(in_raw.indexOf("GET /A,") >= 0) {
              prefix = in_raw.indexOf("A");
              suffix = in_raw.indexOf("Z");
              cut_String = in_raw.substring(prefix+2,suffix-1);
              cut_String.toCharArray(raw_charArray,100);
              sendNums(raw_charArray);
            }
            break;
          } else {currentLine = "";}
        } else if (in_char != '\r') {currentLine += in_char;
        }
      }
    }
    in_raw = "";
    client.stop();
  }
}
void sendNums(String raw_charArray){
  Serial.print(raw_charArray);
  pos = 0;
  id = 0;
  NUMS = "0";
  strLength=0;
  asd = 0;
  strLength = raw_charArray.length();
  while(pos<=strLength-1){
    NUMS = raw_charArray.substring(pos,raw_charArray.indexOf(',',pos));
    asd = NUMS.toInt();
    numArray[id] = asd;
    if(raw_charArray.indexOf(',',pos) == -1)
    break;
    pos=raw_charArray.indexOf(',',pos)+1;
    id++;
  }
  Wire.beginTransmission(4);
  for(int id2=0; id2<20; id2++){
    Wire.write(numArray[id2]); //Byte-ként küldi el!!!
    delay(10);}
  Wire.endTransmission();
}
