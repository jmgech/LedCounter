#ifndef HttpParser_h
#define HttpParser_h


#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// This should be added to the top where your other includes are
extern "C" {
#include "user_interface.h"
}

class HttpParser {

  public:
    String readJSONFromPage();

  private:
        
};

#endif
