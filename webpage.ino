
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 #include "user_interface.h" 
MDNSResponder mdns;
ESP8266WebServer server(80);
#define INPUT_PIN 5
os_timer_t myTimer;
#define TIMER_UPDATE 1000

// Bolean variable for digital input reads
bool inp = 0;
void timerCallback(void *pArg) {
  inp=digitalRead(INPUT_PIN);
  Serial.print("Read digital input: ");
  Serial.println(inp);
}
String webPage =
{
  "<!DOCTYPE HTML><html>"
"<head>"
  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
 " <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>"
"  <style>"
  "  html {"
   "  font-family: Arial;"
    " display: inline-block;"
    " margin: 0px auto;"
     "text-align: center;"
   " }"
   " h2 { font-size: 3.0rem; }"
  "  p { font-size: 3.0rem; }"
  "  .units { font-size: 1.2rem; }"
    ".dht-labels{"
     " font-size: 1.5rem;"
    "  vertical-align:middle;"
     " padding-bottom: 15px;"
    "}"
  "</style>"
"</head>"
"<body>"
 " <h2>Front Door Status</h2>"
 " <p>"
  "  <i class='fas fa-thermometer-half' style='color:#059e8a;'></i> "
   " <span class='dht-labels'>Temperature</span> "
  "  <span id='temperature'>28</span>"
   " <sup class='units'>&deg;C</sup>"
 " </p>"
 " <p>"
    "<i class='fas fa-tint' style='color:#00add6;'></i>" 
    "<span class='dht-labels'>Humidity</span>"
    "<span id='humidity'> 60</span>"
    "<sup class='units'>%</sup>"
  "</p>"
 
};
String webPage1 {
  " <p>"

  "  <i class='fas fa-door-open style=' style='color:#1890ff;'></i> "
   " <span class='dht-labels'>Front Door</span>"
 "   <span id='humidity'>Open</span>"
    
 " </p>"
"</body>"
"</html>"
};
String webPage2 {
  " <p>"

  "  <i class='fas fa-door-closed style=' style='color:#1890ff;'></i> "
   " <span class='dht-labels'>Front Door</span>"
 "   <span id='humidity'>Closed</span>"
    
 " </p>"
"</body>"
"</html>"
};



void TrangChu()
{
  server.send(200, "text/html", webPage);
}

void setup()
{
   pinMode(INPUT_PIN, INPUT);
   os_timer_setfn(&myTimer, timerCallback, NULL);
  os_timer_arm(&myTimer, TIMER_UPDATE, true);
  
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(":(", "hahahaha");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
   server.on("/", [](){
    Serial.println("HTTP request");
    if (inp==0)
    server.send(200, "text/html", webPage+webPage1);
    
     else
    server.send(200, "text/html", webPage+webPage2);
   
  });
  server.begin();
  Serial.println("HTTP server started"); 
}
void loop()
{
  server.handleClient();
}
