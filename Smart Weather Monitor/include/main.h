#include <WiFi.h>
#include <Arduino_JSON.h>
#include "ThingSpeak.h"
WiFiClient  client;

unsigned long myChannelNumber = 1825678;
const char * myWriteAPIKey = "LNMRRGOONLYCSQ7R";

const char* ssid = "Neej's Personal";   // your network SSID (name) 
const char* password = "tp010601";   // your network password

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "d7d24f4f6ed034b658fcfef0d82d93db";
String city = "Kaithal";
String countryCode = "IN";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;
String jsonBuffer;