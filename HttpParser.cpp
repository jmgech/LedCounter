#include "HttpParser.h"
#include "debug.h"
#include "config.h"


String HttpParser::readJSONFromPage() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.setTimeout(1000*30);
    
    http.begin(DATA_PROVIDER);  // BUG : Not working with HTTPS

    LOGF("Get: %s\n ", DATA_PROVIDER);

    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      return payload;
    }
    else {
      LOGF("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }


    http.end();

  }
}
