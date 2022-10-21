#include <Arduino.h>
#include "main.h"
#include "HTTPGet.h"


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      Serial.println(serverPath);
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
         
   JSONVar temperature=myObject["main"]["temp"];
   JSONVar pressure=myObject["main"]["pressure"];
   JSONVar humidity=myObject["main"]["humidity"];
   JSONVar windspeed=myObject["wind"]["speed"];

   int tempThings=temperature;
   tempThings=tempThings-273;
   int pressureThings=pressure;
   int humidityThings=humidity;
   int windspeedThings=windspeed;

           ThingSpeak.setField(1, tempThings);
           ThingSpeak.setField(2, pressureThings);
           ThingSpeak.setField(3, humidityThings);
           ThingSpeak.setField(4, windspeedThings);

        int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if(x == 200){
          Serial.println("Channel update successful.");
        }
        else{
          Serial.println("Problem updating channel. HTTP error code " + String(x));
        }
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Temperature in Celcius: ");
     // Serial.println(myObject["main"]["temp"]);
      Serial.println(temperature);
      Serial.print("Pressure in hPa: ");
      Serial.println(myObject["main"]["pressure"]);
      Serial.print("Humidity in %: ");
      Serial.println(myObject["main"]["humidity"]);
      Serial.print("Wind Speed in m/s NW: ");
      Serial.println(myObject["wind"]["speed"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}