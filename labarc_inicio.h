#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>

#include <SocketIOClient.h>
SocketIOClient client;  

char hostSocket[] = "http://web.cloud.lsd.ufcg.edu.br";
int port = 42138;

extern "C" {
  #include "user_interface.h"
  #include "spi_flash.h"
}

ESP8266WebServer server(80);

const char* ssid = "Marcos - Wifi";
const char* password = "11223344r";

#define LED_BUILTIN 2

void handleNotFound(){
  server.send(404, "text/plain", "Not Found\n\n");
}

void ondata(SocketIOClient client, char *data) {
  Serial.print(data);
}

