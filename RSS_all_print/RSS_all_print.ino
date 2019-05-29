//Rss전체 출력하기
#include<ESP8266WiFi.h>

const char* ssid = "AndroidHotspot7764"; //wifi
const char* password = "wjdghks2";
const char* host = "www.kma.go.kr";
String s;

void setup(){
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }//whlie문

  Serial.println();
  Serial.println("WiFi connectde");
  Serial.println("IP address : ");
  Serial.println(WiFi.localIP());
}//setup문

void loop(){
  WiFiClient client;
  if(client.connect(host, 80)){ //아래의 query ~~zone=숫자 : 숫자는 지역의 의미를 말함 -> 이는 RSS 웹의 주소를 뜻함.
    client.print(String("GET ") + "/wid/queryDFSRSS.jsp?zone=1123066000"+"HTTP/1.1\r\n" + 
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n");
    while(!client.available()); //연결될 떄까지 반복문 돎
    while (client.available()){
      s = client.readStringUntil('\n'); //사이트에서 엔터가 나올 때까지 계속 읽는다. -> 한줄씩 다 읽어 온다는 것이다.
      Serial.println(s); //시리얼 모니터에 출력
    }//while문
    delay(60000); //굳이 매초마다 반복문을 돌 필요가 없으므로 그냥 큰 값을 준 것이다.
  }//if문
  
}//loop문
