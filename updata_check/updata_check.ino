//업데이트 확인
#include<ESP8266WiFi.h>

String readLine = "";
String pubData = "";

const char* ssid = "AndroidHotspot7764"; //wifi
const char* password = "wjdghks2";
const char* host = "www.kma.go.kr";


void setup(){
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.vegin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }//while문
}


void loop(){
  WiFiClient client;
  if(client.connect(host, 80)){
    client.print(String("GET ") + "/wid/queryDFSRSS.jsp?zone=1123066000"+"HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");
    while(!client.available());
    while (client.available()){
      readLine = client.readStringUntil('\n');
      Serial.println(readLine);
      if (readLine.indexOf("pubDate") > - 1){
        if(pubDate != readLine) {
          pubDate = readLine;
          Serial.println(pubDate);
        }//if문
        else{
          Serial.println("Not Updated");
          delay(180000);
          break;
        }//else문
      }//바깥 if문
    }//while문
    delay(60000);
  }//if문
  
}//loop문
