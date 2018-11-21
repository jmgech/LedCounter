#include "Network.h"

#include "debug.h"

#include <WiFiClient.h>
#include <ArduinoHttpClient.h>

    int _port = 80;
    char _server[] = "jmge.ch";   

    WiFiClient wifi;
    
    HttpClient _client = HttpClient(wifi, _server, _port);

    String response;
    int statusCode = 0;
    
  
/* =================================================================== */
     
    void Network::init(){ }

    
    void Network::connect(const char* ssid, const char* password){
       
      if(WiFi.status() == WL_DISCONNECTED) {
        
        WiFi.mode(WIFI_STA);
        wifi_station_set_hostname("SocialCounterMatrix");
        WiFi.begin(ssid, password);  

        delay(2000);

      }

      _ip = WiFi.localIP();     
            
    }

    
    String Network::getClassName(){ return "Network"; }

    
    String Network::getIpAddress(){
      return WiFi.localIP().toString();
    }

    
    void Network::pingWebServer(){

      String txtPost = "This may very well be another test";
      String contentType = "application/x-www-form-urlencoded";
      String path = "/api_fetch/ping.php";
      String postData = "ardval=" + Network::getIpAddress();
      //Serial.println(postData);
      
       // send the POST request
      _client.post(path, contentType, postData); 

      // read the status code and body of the response
      statusCode = _client.responseStatusCode();
      response = _client.responseBody();
          
    }


    void Network::wifiManager(){

        WiFiManager wifiManager;
        wifiManager.setBreakAfterConfig(true);
        
        wifiManager.autoConnect("LaBox-Installation");
        wifiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>");
        
        WiFiManagerParameter custom_text("<p>La Box - WiFi Configuration</p>");
        wifiManager.addParameter(&custom_text);

        LOGF("The box's IP is: %s\n", Network::getIpAddress());
      
    }

    void Network::configModeCallback (WiFiManager *myWiFiManager) {
      LOGLN("Entered config mode");
      LOGLN(WiFi.softAPIP());
      LOGLN(myWiFiManager->getConfigPortalSSID());
    } 
