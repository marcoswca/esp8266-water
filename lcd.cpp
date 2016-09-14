#include <ESP8266WiFi.h>
#include "lcd.h"

void lcd_nibble(byte d) {  // send one nibble of data in d[3:0] to LCD
  register int out = ((d&7)<<12)  // LCD_D[6:4]
                    |((d&8)<<1);  // LCD_D[7]    // 4 MSB of d are ignored
  GPOS = out;        // set LCD_D pins that are 1
  out ^= (1<<LCD_D7)|(1<<LCD_D6)|(1<<LCD_D5)|(1<<LCD_D4); // invert bits for LCD_D
  GPOC = out;        // clear LCD_D pins that are 0
  out  = (1<<LCD_E); // pulse on LCD_E
  GPOS = out;
  GPOC = out;  
}

void lcd_byte(byte d) { // send one byte of data to LCD
  delay(1); lcd_nibble(d>>4);
            lcd_nibble(d);
}

void lcd_init() {  // initialize LCD after reset and power up
  pinMode(LCD_E,  OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_D4, OUTPUT);
  pinMode(LCD_D5, OUTPUT);
  pinMode(LCD_D6, OUTPUT);
  pinMode(LCD_D7, OUTPUT);
  lcd_nibble(0);
  digitalWrite(LCD_RS,LOW);
  digitalWrite(LCD_E,LOW);
  // http://web.alfredstate.edu/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
  delay(150); lcd_nibble(3); // Special case of Function Set
  delay(  5); lcd_nibble(3); // Special case of Function Set
  delay(  1); lcd_nibble(3); // Special case of Function Set
  delay(  1); lcd_nibble(2); // Function Set  4 bits
              lcd_byte(0x28); // Function Set  2 lines
              lcd_byte(0x08); // Display off
              lcd_byte(0x01); // clear Display
  delay(  3); lcd_byte(0x06); // Entry mode Increment, no shift
              lcd_byte(0x0C); // Display on 
}

void lcd_string(const char *str) { // send an ASCII string to LCD
  lcd_byte(0x80); // DDRAM address=07 - start of first line
  digitalWrite(LCD_RS,HIGH);
  for(byte i=0; i<LCD_CHARS && str[i]; i++) {
    if(i==LCD_CHARS_PER_LINE) {
      digitalWrite(LCD_RS,LOW);
      lcd_byte(0xC0); // DDRAM address=40 - start of second line
      digitalWrite(LCD_RS,HIGH);
    }
    lcd_byte(str[i]);
  }
  digitalWrite(LCD_RS,LOW);
}


