#ifndef Network_h
#define Network_h


#include "Arduino.h"

// This should be added to the top where your other includes are
extern "C" {
#include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


class Network {

  public:
    void init();
    void connect(const char* ssid, const char* password);
    void wifiManager();
    void configModeCallback (WiFiManager *myWiFiManager);
    String getClassName();
    String getIpAddress();
    void pingWebServer();
    void getJSONFromWeb();

  private:
    int _port;
    const char* _host;
    IPAddress _ip;
    
    

};


#endif
