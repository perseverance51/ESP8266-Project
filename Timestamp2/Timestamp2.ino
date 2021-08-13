#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>//新增

const char*ssid="CMCC-DyVv";
const char*password="pba5ayzk";
long int Time;
String Time_api = "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp";
 void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
    while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
Serial.printf("WiFi name:%s\n IP Address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());   
}


void loop()
{
 Time = getTimestamp(Time_api); //nowapi时间API
  Serial.println(Time);
  delay(6000);
}

long int getTimestamp(String url)
{
  String Time = "";
  long long Time1;
   WiFiClient client;//新增
  HTTPClient http;
  http.begin(client,url);//新增形参



  // start connection and send HTTP headerFFF
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      int pos = (payload.indexOf("data"));
      Time = payload.substring(pos + 12, payload.length() - 6);
      Serial.println(payload.substring(pos + 12, payload.length() - 6));
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  
  return atoll(Time.c_str());
}
