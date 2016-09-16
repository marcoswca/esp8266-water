void setup() {
  Serial.begin(115200);

   /* switch on led */
  pinMode(LED_BUILTIN, OUTPUT);
  analogWriteRange(100);
  analogWrite(LED_BUILTIN,99);
  
  Serial.print("Booting");
  WiFi.mode(WIFI_STA);
  Serial.print(":");

  while (WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.print(".");
    WiFi.begin(ssid,password);
    delay(200);
  }
  Serial.println("");
  Serial.print("Connected, IP=");
  Serial.println(WiFi.localIP());

  labarc_setup();
  Serial.println("LCD Ready");
  
  /* OTA server events */
  ArduinoOTA.setHostname(host);

  ArduinoOTA.onError([](ota_error_t error) { ESP.restart(); });

   /* setup the OTA server */
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
  
  /* setup the HTTP server */
  server.on("/", requestLocal);

  server.on("/esp12id", getChipId);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Ready");

  client.setDataArrivedDelegate(ondata);
  if (!client.connect(hostSocket, port)) Serial.println(F("Not connected."));

  if (client.connected()) client.send("Client here!");
}

//int next_time=0;
byte led=1;

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  if( millis() > next_time ) {
     led = 100-led;
     analogWrite(LED_BUILTIN,led);
     labarc_loop();
     if (client.connected()) client.send("Hello, world!\n");
    // next_time += LOOP_INTERVAL;
  }
}


