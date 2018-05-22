#include "wifiController.h"
#include "ledController.h"

TaskHandle_t mainTaskHandle,realTaskHandle;
WiFiMulti wifiMulti;
WifiController WifiCon(&wifiMulti);

void setup(){
  Serial.begin(115200);
  Serial.println();
  uint64_t chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  Serial.printf("ESP32 Chip ID = %04X", (uint16_t)(chipid >> 32)); //print High 2 bytes
  Serial.printf("%08X\n", (uint32_t)chipid); //print Low 4bytes.
  Serial.print("ESP32 SDK: ");
  Serial.println(ESP.getSdkVersion());  
  WifiCon.wifiConnect();
  boardLedInit();
  
  xTaskCreate(realTask, "realTask", 5000, NULL, 1, &realTaskHandle);
} 

void loop(){ 
  
}

void realTask(void* parameter) {
  while (1) {
    ledFlash();
    if(!WifiCon.checkWifiConnect()){
      WifiCon.wifiReconnect();
    }
//  xTaskNotifyGive( mainTaskHandle ); 
//    vTaskDelete(NULL);   
  }
}
