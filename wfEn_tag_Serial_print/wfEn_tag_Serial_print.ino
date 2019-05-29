//wfEn태그 시리얼 모니터 출력
#include<ESP8266WiFi.h>

String readLine = "";
String wfEn = "<wfEn>";
String s = "";
String now = "";
String pubDate = "";

const char* ssid = "AndroidHotspot7764"; //wifi
const char* password = "wjdghks2";
const char* host = "www.kma.go.kr"; //여기 웹사티으를 기반으로 가져오라는 것.
//?zone = 1159068000 지역을 숫자로 표현한 것이다. 

void setup(){

  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }//while문
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
          Serial.println("Not Updated");
          delay(180000);
          break;
        }//else문
      }//바깥 if문
      if (readLine.indexOf("data seq") > -1){
        now = readLine;
      }//if문
      if (now.indexOf("\"0\"") > -1 && readLine.indexOf("<wfEn>") > -1){
        s = readLine.substring(readLine.indexOf("<wfEn>") + wfEn.length(), readLine.indexOf("</wfEn"));
        Serial.println(s);      //위에 wfEn.length()는 태그 뒤에 부터 읽기 위해 추가함.
      }//if문
    }//while문
  }//가장 바깥 if문
}//loop문
