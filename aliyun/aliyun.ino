 
#include "DHT.h"   //导入别人封装好的DHT包，在arduino就可下载
#include <ESP8266WiFi.h>//wifi功能包
#include <ArduinoJson.h>//json包
#include <AliyunIoTSDK.h>//GitHub上一个封装好的阿里云数据传输包，特别好用
AliyunIoTSDK iot;
static WiFiClient espClient;

//阿里云设备三元组，能够唯一确定设备
#define PRODUCT_KEY "a1fd5jdx48v"
#define DEVICE_NAME "LightTH"
#define DEVICE_SECRET "6YVP3aAo7fbm0Tl0i MMS2nNpFI"
//地区
#define REGION_ID "cn-shanghai"
//wifi信息
#define WIFI_SSID "Red 0 Pro"
#define WIFI_PASSWD "88 888"

//定义接入的引脚为Gpio5
#define DHTPIN 5
//定义传感器类型为DHT11，因为DHT.h中封装了多种温湿度传感器的功能
#define DHTTYPE DHT11
//定义对象
DHT dht(DHTPIN, DHTTYPE);

//初始化wifi信息
void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    WiFi.setAutoConnect (true);
    WiFi.setAutoReconnect (true);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}


void setup()
{
    Serial.begin(115200);
    dht.begin(); //DHT开始工作
    //连接网络
    wifiInit(WIFI_SSID, WIFI_PASSWD);
 
  //连接阿里云
    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);

    // 绑定属性回调，即确定从阿里云向设备发送信息后触发的方法
    AliyunIoTSDK::bindData("temp", powerCallback);
}

unsigned long lastMsMain = 0;
//StaticJsonBuffer<200> jsonBuffer;
//JsonObject& object = jsonBuffer.createObject();
DynamicJsonDocument doc(1024);
void loop()
{
    AliyunIoTSDK::loop();
    if (millis() - lastMsMain >= 3000)
    {
        lastMsMain = millis();
        doc["humi"] = dht.readHumidity();//读湿度
        doc["temp"] = dht.readTemperature();//读温度，默认为摄氏度
        String output;
        //这里需要将数据json序列化，因为send方法的参数是const char*类型。
        //具体可参考文章末尾<AliyunIoTSDK.h>源码链接
        serializeJson(doc, output);
        const char *str = output.c_str(); 
        //将数据发送至阿里云，使用的topic类列表中的物模型通信topic中的
        //  /sys/a1pjDXR6L0q/${deviceName}/thing/event/property/post
        // 这个是阿里云自带的topic。
        AliyunIoTSDK::send(str); 
        
    }
    
}

//回调函数
void powerCallback(JsonVariant p)
{
    int PowerSwitch = p["PowerSwitch"];
    if (PowerSwitch == 1)
    {
        Serial.println("11111111111111111111");
    }
    else
    {
        Serial.println("000000000000000000");
    }
}
