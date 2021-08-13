#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Ticker.h>



Ticker ticker;
#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // ESP32 DOES NOT DEFINE LED_BUILTIN
#endif
int LED = LED_BUILTIN;
String urla = "https://v1.hitokoto.cn/?encode=json&min_length=1&max_length=21"; // 网络服务器地址
void tick()
{
  digitalWrite(LED, !digitalRead(LED));     // set pin to the opposite state
}
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  ticker.attach(0.2, tick);
}
String callHttps(String url);//获取一言json函数
void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  ticker.attach(0.6, tick);
  WiFiManager wm;
  wm.setAPCallback(configModeCallback);
  if (!wm.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.println("connected...yeey :)");
  ticker.detach();
  digitalWrite(LED, LOW);
  callHttps(urla);  //调用API接口，来获取指定网站返回的数据
  delay(1000);
}
void loop() {}
//https请求
String callHttps(String url)
{
  String payload;
  Serial.print("requesting URL: ");
  Serial.println(url);
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  //client->setFingerprint(fingerprint); //检验指纹
  client->setInsecure(); //不检验
  HTTPClient https;
  if (https.begin(*client, url))
  {
    int httpsCode = https.GET();
    if (httpsCode > 0)  //判断有无返回值
    {
      if (httpsCode == 200 || httpsCode == 304 || httpsCode == 403 || httpsCode == 404 || httpsCode ==   500) //判断请求是正确
      {
        payload = https.getString();
        Serial.println(payload);
        Serial.println("");
        DynamicJsonDocument doc(512);//分配内存,动态
        DeserializationError error = deserializeJson(doc, payload);
        const char* hitokoto = doc["hitokoto"]; // "一定要保护自己的梦想，即使牺牲一切。"
        if(doc.isNull()==0)
        Serial.println(hitokoto);
          return payload;      
      }
      else
      {
        Serial.print("请求错误："); Serial.println(httpsCode); Serial.println(" ");
        char* httpsCode_c = new char[8];
        itoa(httpsCode, httpsCode_c, 10); //int转char*
        payload = "{\"status_code\":\"" + String("请求错误:") + String(httpsCode_c) + "\"}";
        return payload;
      }
    }
    else
    {
      Serial.println(" "); Serial.print("GET请求错误："); Serial.println(httpsCode);
      Serial.printf("[HTTPS] GET... 失败, 错误: %s\n", https.errorToString(httpsCode).c_str());
      payload = "{\"status_code\":\"" + String(https.errorToString(httpsCode).c_str()) + "\"}";
      //Serial.println(payload);
      return payload;
    }
  }
  else
  {
    Serial.printf("[HTTPS] 无法连接服务器\n");
    payload = "{\"status_code\":\"" + String("无法连接服务器") + "\"}";
    return payload;
  }
  https.end();
}
