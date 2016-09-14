int max_osc = 133;
int samples [10];

uint8_t cachaca() {
  // http://labarc.ufcg.edu.br/loac/index.php?n=OAC.ESP12#cachaca
  register uint8_t now = 0, prev = 1, value = 0;
  for (register uint8_t i = 0; i < 200; i++) {
      now = GPIP(OSC_IN);
      value += now ^ prev;
      prev = now;
      if ( now ) GPOC = (1 << OSC_OUT);
      else      GPOS = (1 << OSC_OUT);
  }
  return value;
}

int getSamples() {

  int arr_size = sizeof(samples)/sizeof(samples[0]);

  for (int i = 0; i< 10; i++){
      samples[i] = cachaca();
  }

  mergeSort(samples, 0, arr_size - 1);

  int median = (samples[5] + samples[6])/2;
  
  return median;
}

bool checkWater() {
  bool water = false;
  for (int i = 0; i < 10; i++) {      
      if (cachaca() > 1) {
          water = true;
      }
   } 
  return water;
}

int calculateLevel(int median) {
      int level = 100*(median/(max_osc * 0.585));
      if (level > 100) {
          level = 100;
      }
      return level;
}


String requestLevel() {
      
  if (!checkWater()){
      return "level=0&chipId=" + String(chipId);
  }  else {
      int level = calculateLevel(getSamples());
      return "level=" + String(level) + "&chipId=" + String(chipId);
   }
}

void requestLocal() {
      int level = 0;
      if (!checkWater()){
        server.send(200, "text/plain", "level=Caixa Vazia&chipId=" + String(chipId));
      } else {
         int level = calculateLevel(getSamples());
         server.send(200, "text/plain", "level=" + String(level) + "&chipId=" + String(chipId));
      }
}

void getChipId(){
    server.send(200, "text/plain", String(chipId));
}

