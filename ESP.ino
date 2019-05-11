#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
const int RSSI_buffer_leangth = 10;
int RSSI_buffer[RSSI_buffer_leangth];
int i;
String id = "";

void setup() {

  Serial.begin(115200);
  Serial.println("hello there");

  WiFi.begin("testy", "trapsaregay");


  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");

  Serial.println(WiFi.localIP());

  Udp.begin(69);
  id = WiFi.macAddress();
}

void isort(int *a, int n)
{
 for (int i = 1; i < n; ++i)
 {
   int j = a[i];
   int k;
   for (k = i - 1; (k >= 0) && (j < a[k]); k--)
   {
     a[k + 1] = a[k];
   }
   a[k + 1] = j;
 }
}


void loop() {
  if(RSSI_buffer[RSSI_buffer_leangth-1]==0){
    for(i = 0; i < RSSI_buffer_leangth; i++){
      if(RSSI_buffer[i]==0){
        RSSI_buffer[i] = WiFi.RSSI();
        break;
      }
    }
  }
  else{
    isort(RSSI_buffer, RSSI_buffer_leangth );
    
    Udp.beginPacket("192.168.43.1", 6969);
    Udp.write((id + "=" + String(RSSI_buffer[(RSSI_buffer_leangth-1)/2])).c_str());
    Udp.endPacket();
    for(i = 0; i < RSSI_buffer_leangth; i++){
      RSSI_buffer[i] = 0;
    }
  }
}
