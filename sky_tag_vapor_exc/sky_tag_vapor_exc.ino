//Sky태그에 따라 가습기 모듈 동작
#include<ESP8266WiFi.h>

int vapor = D7;

String readLine = "";
String sky = "<sky>";
String s = "";
String now = "";
String pubDate = "";

const char* ssid = "AndroidHotspot7764"; //wifi
const char* password = "wjdghks2";
const char* host = "www.kma.go.kr";

void setup(){
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }//while문
  pinMode(vapor, INPUT);
}//setup문

void loop(){
  WiFiClient client;
  if(client.connect(host, 80)){
    client.print(String("GET ") + "/wid/queryDFSRSS.jsp?zone=1123066000"+"HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");
    while(!client.available());
    while (client.available()){
      readLine = client.readStringUntil('\n');
      if (readLine.indexOf("pubDate") > - 1){
        if(pubDate != readLine) {
          pubDate = readLine;
        }//if문
        else{
          delay(180000);
          break;
        }//else문
      }//바깥 if문

      
      if (readLine.indexOf("data seq") > -1){
        now = readLine;
      }//if문
      if (now.indexOf("\"0\"") > -1 && readLine.indexOf("<sky>") > -1){
        s = readLine.substring(readLine.indexOf("<sky>") + sky.length(), readLine.indexOf("</sky>"));
        if (s.toInt() > 0) {
          pinMode(vapor, OUTPUT);
          digitalWrite(vapor, 1);
        }//if문
        else{
          pinMode(vapor,INPUT);
        }//else문
      }
    }//if문      
  }
}//loop문
