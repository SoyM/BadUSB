#include "wifiController.h"

extern WiFiMulti wifiMulti;

WifiController::WifiController(WiFiMulti *wifiMulti){
   WiFi.mode(WIFI_STA);
   WiFi.disconnect();
  
  int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");
    
  _wifiMulti = wifiMulti;
}


int WifiController::checkWifiConnect(){
  return (wifiMulti.run() == WL_CONNECTED);
}

void WifiController::wifiConnect() {
  wifiMulti.addAP("ASUS", "00000000");
  wifiMulti.addAP("huang2", "hxz04010.");
  wifiMulti.addAP("TP-LINK_4A49", "Lanyinkejiccs");
  Serial.println("wifiConnect Start");
  for (int loops = 0; loops < 5; loops++) {
    if (checkWifiConnect()) {
      Serial.println("WiFiConnect success");
      break;
    }
    else {
      Serial.println(loops);
      delay(1000);
    }
  }
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi connect failed!Rebooting...");
    ESP.restart();
  }
  Serial.println(WiFi.SSID());
//  Serial.println("IP address: " + WiFi.localIP());
//  Serial.println("ESP Mac Address: " + WiFi.macAddress());
//  Serial.println("Subnet Mask: " + WiFi.subnetMask());
//  Serial.println("Gateway IP: " + WiFi.gatewayIP());
//  Serial.println("DNS: " + WiFi.dnsIP());
  Serial.println("wifiConnect end");
}

void WifiController::wifiReconnect() {
  for(char i=0; i<=4; i++){
    if(!WifiController::checkWifiConnect()){
      WifiController::wifiConnect();  
      WiFiClient client;
      if (!client.connect("www.icloud.com", '80')) {
        Serial.print("Attempting Wifi connection...");
        WifiController::wifiConnect();
      }
    }else{
      return;
    }
    if(i=4){
        ESP.restart();
    }
    delay(1000);
  }
}

