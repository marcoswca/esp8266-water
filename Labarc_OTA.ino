#include "labarc_inicio.h"
#include "mergesort.h"

const char* host = "ota-00"; // aqui você deve colocar o numero do seu PC

const int ledsv = 13;
const int chipId = ESP.getChipId();

char value_str[10];
#define SEND_INTERVAL 10000
int next_time = SEND_INTERVAL;
int prev = 0;
int actual = 0;
#define LED_PIN  2
#define OSC_IN  12
#define OSC_OUT 13
#include "caixadagua.h"



void labarc_setup() {
  pinMode(OSC_IN, INPUT);
  pinMode(OSC_OUT, OUTPUT);
}

#define LOOP_INTERVAL 1000
void labarc_loop() {
  // Futura chamada ao servidor na nuvem para atualizar os dados da caixa
  //itoa(cachaca(), value_str, 10);
  next_time += SEND_INTERVAL;

  prev = actual;

  actual = calculateLevel(getSamples());

  if(fabs(actual - prev) > 5) {
      HTTPClient http;
      http.begin("http://marcosarruda.me/povmt/esp12/");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      http.POST(requestLevel());
      http.writeToStream(&Serial);
      http.end();
  }  
}

#include "labarc_fim.h"

