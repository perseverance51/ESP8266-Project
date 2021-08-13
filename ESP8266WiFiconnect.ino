#include <ESP8266WiFi.h>
const char*ssid="CMCC-DyVv";
const char*password="pba5ayzk";
float num =0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
//  WiFi.macAddress(MAC_array_STA);
//  WiFi.softAPmacAddress(MAC_array_AP);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(800);
    Serial.print("\n WiFi not connect.");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(" The following is the ESP8266 hardware information: ");
  hardware();
}

void loop() {}
void hardware(){
  Serial.printf("\n ESP.getChipId =  %u \n\n",ESP.getChipId());// ESP.getChipId =  11075638
    delay(10);
  Serial.printf("\n ESP.getCpuFreqMHz =  %u MHz \n\n",ESP.getCpuFreqMHz());//ESP.getCpuFreqMHz =  80 MHz
    delay(10);
  Serial.printf("\n ESP.getSketchSize =  %u bytes\n\n",ESP.getSketchSize());//ESP.getSketchSize =  313824 bytes
  delay(10);
  Serial.printf("\n ESP.getFreeSketchSpace =  %u bytes\n\n",ESP.getFreeSketchSpace());//ESP.getFreeSketchSpace =  1781760 bytes
  delay(10);
  Serial.printf("\n ESP.getSketchMD5 =  %s \n",ESP.getSketchMD5().c_str());//ESP.getSketchMD5 =  f578cc35ea3ba1d4de0493873978e83b

    FlashMode_t ideMode = ESP.getFlashChipMode();
  Serial.printf("Flash ide mode:  %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
  //Flash ide mode:  DIO
  
  delay(10);
Serial.printf("\n ESP.getFlashChipId =  %u \n",ESP.getFlashChipId());//ESP.getFlashChipId =  1523951
  delay(10);
  Serial.printf("\n ESP.getFlashChipSize =  %u \n",ESP.getFlashChipSize());//ESP.getFlashChipSize =  8388608
  delay(10);
  Serial.printf("\n ESP.getFlashChipRealSize =  %u \n",ESP.getFlashChipRealSize());//ESP.getFlashChipRealSize =  8388608
  delay(10);
  Serial.printf("\n ESP.getFlashChipSpeed =  %u Hz\n",ESP.getFlashChipSpeed());//ESP.getFlashChipSpeed =  40000000 Hz
  delay(10);
  Serial.printf("\n ESP.getCycleCount =  %u \n",ESP.getCycleCount());//ESP.getCycleCount =  25178339
  delay(10);
  Serial.printf("\n ESP.random =  %u \n",ESP.random());//ESP.random =  2827193237
  delay(10);
  Serial.printf("\n getVcc =  %u \n",ESP.getVcc());//getVcc =  65535
    delay(10);
  Serial.printf("\n getFreeHeap =  %u \n",ESP.getFreeHeap());//getFreeHeap =  50488
      delay(10);
  Serial.printf("\n getMaxFreeBlockSize =  %u \n",ESP.getMaxFreeBlockSize());//getMaxFreeBlockSize =  50096
 // Serial.println(WiFi.macAddress().c_str());
   Serial.printf("macAddress = %s",WiFi.macAddress());
   IPAddress myIP = WiFi.localIP(),wayIP=WiFi.gatewayIP(),netMask=WiFi.subnetMask();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("STA IP wayIP: ");
  Serial.println(wayIP);
    Serial.print("netMask: ");
  Serial.println(netMask);
 
  num +=0.5;
 Serial.printf(" %f \n",sin(num)); 
}
