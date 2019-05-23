#include "Header.h"

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);    // create a websocket server on port 81

// Setup a oneWire instance to communicate with any OneWire devices  
OneWire oneWire(ONE_WIRE_BUS); 

/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

Ticker timer;

const char* ssid = "QueensLab_Guest"; //Enter SSID
const char* password = "utveckling-design"; //Enter Password

char const webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
   <head>
      <title>Temperature Sensor</title>
      
      <script>
          var websock;
         
          function init_ws(){
      
            var host = window.location.hostname;
 
            websock = new WebSocket('ws://' + host + ':81/');
      
            websock.onopen = function(evt) {
              console.log('websock open');
            };
         
            websock.onerror = function(evt) {
                console.log(evt);
            };
         
            websock.onmessage = function(evt) {
                var data = JSON.parse(evt.data);
                console.log(data);
                return false;
            };
             
            websock.onclose = function(){
                console.log('websock close');
            };
        }
      </script>
     
   </head>
   <body onload="javascript:init_ws();">
      
   </body>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
     <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.8.0/Chart.min.js"></script>
</html>
)=====";

float getTemperature() {
  float temp;
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);

  String json = "{\"value\":";
  json += temp;
  json += "}";
  webSocket.broadcastTXT(json.c_str(), json.length());
  
  return temp;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t len)
{
    if(type == WStype_TEXT){
        digitalWrite(LED, LOW);
        Serial.printf("%s\r\n", payload);
        digitalWrite(LED, HIGH);
    } 
}

// Initial settings will be done in this method
void setup() {

  delay(1000);
  
  /* Our initial baudrate will be 115200 */
  Serial.begin(115200);

  /* Configure and setup WiFi settings */
  //Serial.println(); 
  //Serial.print("Setting soft-AP configuration ... ");

  //Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  //Serial.print("Setting soft-AP ... ");
  //WiFi.mode(WIFI_AP);

  //*--------------------------
  //* Change the next line to your desired WiFi SSID  : 
  //*--------------------------
  //Serial.println(WiFi.softAP("GroupX") ? "Ready" : "Failed!");
  //Serial.print("Soft-AP IP address = ");
  //Serial.println(WiFi.softAPIP());

  //if (!MDNS.begin("temp")) {             // Start the mDNS responder for esp8266.local
    //Serial.println("Error setting up MDNS responder!");
  //}
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  
  /* Start the web server */
  server.begin();

  /* start the websockets server */
  webSocket.begin();

  /* Attach the eventHandler for different return messages */
  webSocket.onEvent(webSocketEvent);

  /* Explicitly make the LED pin as output */
  pinMode(LED, OUTPUT);  
  pinMode(D1, INPUT);  
  
  sensors.begin();

  timer.attach(1, getTemperature);

  
  server.on("/", [](){
     server.send_P(200, "text/html", webpage);
  });
}

void loop() {

  webSocket.loop();
  server.handleClient();

}
