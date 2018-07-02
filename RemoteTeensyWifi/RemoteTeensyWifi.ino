#include "ESP8266AT.h"

#define SSID        "APName"
#define PASSWORD    "APPSK"

//ESP8266 wifi(Serial1);
ESP8266 wifi(Serial1, 57600);

void setup(void)
{
    Serial.begin(9600);
     
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("IP: ");
        Serial.println(wifi.getLocalIP().c_str());   
    } else {
        Serial.print("Join AP failure\r\n");
    }
   
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
   
    if (wifi.startTCPServer(8090)) {
        Serial.print("start tcp server ok\r\n");
    } else {
        Serial.print("start tcp server err\r\n");
    }
   
    if (wifi.setTCPServerTimeout(10)) {
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
   
    Serial.print("End\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        Serial.print("Status:");
        Serial.println(wifi.getIPStatus().c_str());
        
        Serial.print("Received from:");
        Serial.println(mux_id);
        delay(250)


        String input_temp = "";
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
            input_temp += (char)buffer[i];
        }

    
        Serial.println("");
       
        if(wifi.send(mux_id, buffer, len)) {
            Serial.print("send back ok\r\n");
        } else {
            Serial.print("send back err\r\n");
        }
       
        if (wifi.releaseTCP(mux_id)) {
            Serial.println("release tcp ok");
        } else {
            Serial.println("release tcp error");
        }     
    }
}
