// connect LCD 1602A to ESP12           
#define LCD_D4 12
#define LCD_D5 13
#define LCD_D6 14
#define LCD_D7 4
// CAUTION: 1st statement of lcd_nibble must be adjusted if the defines of LCD_D are changed
#define LCD_E  5
#define LCD_RS 16
#define LCD_CHARS_PER_LINE 16
#define LCD_LINES 2
#define LCD_CHARS LCD_CHARS_PER_LINE*LCD_LINES

void lcd_nibble(byte d);
void lcd_init();
void lcd_string(const char *str);

