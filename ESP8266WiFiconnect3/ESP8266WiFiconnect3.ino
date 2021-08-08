#include <ESP8266WiFi.h>
const char*ssid="CMCC-DyVv";
const char*password="pba5ayzk";
bool autoConnect = true;//设置自动连接所需变量

IPAddress staticIP(192, 168, 1, 88);//请按照自己的网络环境设置这三个参数
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
static const char xyz[] PROGMEM = "This is a string stored in flash";

void setup()
{
  Serial.begin(115200);
  Serial.println();

    //无线终端模式下配置IP，并将接口的IP配置设置为用户定义的值
  WiFi.config(staticIP, gateway, subnet);
  
  Serial.println("开始连接");
  Serial.println("检查自动连接设置状态");
   if (WiFi.getAutoConnect() == true) {
    Serial.println("已设置自连接");
  }
  else
    Serial.println("未设置连接");
  
  WiFi.setAutoConnect(autoConnect);//启用自动连接模式
  delay(500);//启用自动连接后再检查一次，确定设置变化
  
  Serial.println("再次检查自动连接设置状态");
  if (WiFi.getAutoConnect() == true) {
    Serial.println("已设置自连接");
  }
  else
    Serial.println("未设置连接");
  
  //调用 WiFi.begin()函数，开始连接接入点
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  uint8_t i=0;//用来判定连接是否超时的累加量
  while (WiFi.status() != WL_CONNECTED)
  {
   i++;
    delay(500);
    Serial.print(".");
    if (i > 120) { //60秒后如果还是连接不上，就判定为连接超时
      Serial.print("连接超时！请检查网络环境");
      break;
    }
  }
  Serial.println("网络连接成功");

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(" The following is the ESP8266 hardware information: ");
  wifi_date();
}

void loop() {
  Serial.println(FPSTR(xyz));
  }
void wifi_date(){
  //mac地址
 // Serial.println(WiFi.macAddress().c_str());
   Serial.printf("macAddress = %s\n",WiFi.macAddress().c_str());
   IPAddress myIP = WiFi.localIP(),
   wayIP=WiFi.gatewayIP(),
   netMask=WiFi.subnetMask(),
   broadcastIP=WiFi.broadcastIP();
    //IP地址
  Serial.print("AP IP address: ");
  Serial.println(myIP);
   //网关地址
  Serial.print("STA IP wayIP: ");
  Serial.println(wayIP);
  //子掩码
    Serial.print("netMask: ");
  Serial.println(netMask);
  //广播地址
      Serial.print("broadcastIP: ");
  Serial.println(broadcastIP);
  
  const String  ssid = WiFi.SSID();
 const  String  password = WiFi.psk();
  Serial.println(ssid);
  Serial.println(password);
        //DNS
      Serial.print("DNS 1: ");
      Serial.println(WiFi.dnsIP(0));
      Serial.print("DNS 2: ");
      Serial.println(WiFi.dnsIP(1));
   
  Serial.printf("BSSIDstr: %s ,%d \n",WiFi.BSSIDstr().c_str(),WiFi.RSSI());
    Serial.print("当前工作模式:");     // 当前工作模式
  Serial.println(WiFi.getMode());
}
