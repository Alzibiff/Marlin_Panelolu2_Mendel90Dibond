#ifndef ULTRA_LCD_IMPLEMENTATION_PANELOLU2_H
#define ULTRA_LCD_IMPLEMENTATION_PANELOLU2_H

/**
* Implementation of the LCD display routines for the Panelolu2 I2C controller.
* Based on and the "ultralcd_implementation_hitachi_HD44780.h" code with I2C modifications which are 
* modelled on Lincomatic's port of Marlin, (see https://github.com/lincomatic/Marlin).
* This is also utilises Lincomatic's LiquidTWI2 library(see http://blog.lincomatic.com/?p=965). 
* 
* for more information see http://blog.think3dprint3d.com/2013/02/panelolu2.html
**/


/* Custom characters defined in the first 8 characters of the LCD */
#define LCD_STR_BEDTEMP     "\x00"
#define LCD_STR_DEGREE      "\x01"
#define LCD_STR_THERMOMETER "\x02"
#define LCD_STR_UPLEVEL     "\x03"
#define LCD_STR_REFRESH     "\x04"
#define LCD_STR_FOLDER      "\x05"
#define LCD_STR_FEEDRATE    "\x06"
#define LCD_STR_CLOCK       "\x07"
#define LCD_STR_ARROW_RIGHT "\x7E"  /* from the default character set */

//for the LED indicators
  #define LED_A 0x04 //100
  #define LED_B 0x02 //010
  #define LED_C 0x01  //001

#include <Wire.h>
#include <LiquidTWI2.h>
 
 //forward declaration
static void lcd_implementation_update_indicators();
 
LiquidTWI2 lcd(0);  //An alternative I2C master address can be used in place of "0"

static void lcd_implementation_init()
{
    byte bedTemp[8] =
    {
        B00000,
        B11111,
        B10101,
        B10001,
        B10101,
        B11111,
        B00000,
        B00000
    }; //thanks Sonny Mounicou
    byte degree[8] =
    {
        B01100,
        B10010,
        B10010,
        B01100,
        B00000,
        B00000,
        B00000,
        B00000
    };
    byte thermometer[8] =
    {
        B00100,
        B01010,
        B01010,
        B01010,
        B01010,
        B10001,
        B10001,
        B01110
    };
    byte uplevel[8]={
        B00100,
        B01110,
        B11111,
        B00100,
        B11100,
        B00000,
        B00000,
        B00000
    }; //thanks joris
    byte refresh[8]={
        B00000,
        B00110,
        B11001,
        B11000,
        B00011,
        B10011,
        B01100,
        B00000,
    }; //thanks joris
    byte folder [8]={
        B00000,
        B11100,
        B11111,
        B10001,
        B10001,
        B11111,
        B00000,
        B00000
    }; //thanks joris
    byte feedrate [8]={
        B11100,
        B10000,
        B11000,
        B10111,
        B00101,
        B00110,
        B00101,
        B00000
    }; //thanks Sonny Mounicou
    byte clock [8]={
        B00000,
        B01110,
        B10011,
        B10101,
        B10001,
        B01110,
        B00000,
        B00000
    }; //thanks Sonny Mounicou
	lcd.setMCPType(LTI_TYPE_MCP23017);
    lcd.begin(LCD_WIDTH, LCD_HEIGHT);
    lcd.createChar(LCD_STR_BEDTEMP[0], bedTemp);
    lcd.createChar(LCD_STR_DEGREE[0], degree);
    lcd.createChar(LCD_STR_THERMOMETER[0], thermometer);
    lcd.createChar(LCD_STR_UPLEVEL[0], uplevel);
    lcd.createChar(LCD_STR_REFRESH[0], refresh);
    lcd.createChar(LCD_STR_FOLDER[0], folder);
    lcd.createChar(LCD_STR_FEEDRATE[0], feedrate);
    lcd.createChar(LCD_STR_CLOCK[0], clock);
    lcd.clear();
	lcd.setBacklight(0); //set all the LEDs off to begin with
}
static void lcd_implementation_clear()
{
    lcd.clear();
}
/* Arduino < 1.0.0 is missing a function to print PROGMEM strings, so we need to implement our own */
static void lcd_printPGM(const char* str)
{
    char c;
    while((c = pgm_read_byte(str++)) != '\0')
    {
        lcd.write(c);
    }
}
/*
Possible status screens:
16x2   |0123456789012345|
       |000/000 B000/000|
       |Status line.....|

16x4   |0123456789012345|
       |000/000 B000/000|
       |SD100%    Z000.0|
       |F100%     T--:--|
       |Status line.....|

20x2   |01234567890123456789|
       |T000/000D B000/000D |
       |Status line.........|

20x4   |01234567890123456789|
       |T000/000D B000/000D |
       |X+000.0 Y+000.0 Z+000.0|
       |F100%  SD100% T--:--|
       |Status line.........|

20x4   |01234567890123456789|     icare display
       |T000/000D B000/000D |
       |X+000 Y+000 Z 000.00|
       |F100%  SD100% T--:--|
       |Status line.........|

20x4   |01234567890123456789|
       |T000/000D B000/000D |
       |T000/000D     Z000.0|
       |F100%  SD100% T--:--|
       |Status line.........|
*/
static void lcd_implementation_status_screen() //d�but affichage
{
    int tHotend=int(degHotend(0) + 0.5); //temperature hotend0 entier
    int tTarget=int(degTargetHotend(0) + 0.5); //temperature consigne0 entier

#if LCD_WIDTH < 20 //moins de 20 caracteres
    lcd.setCursor(0, 0); //curseur en home
    lcd.print((tHotend)); //affiche temperature hotend
    lcd.print('/'); //affiche separateur
    lcd.print(itostr3left(tTarget)); //affiche temperature consigne

# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(8, 0); //curseur colonne 8 ligne 0
#  if EXTRUDERS > 1 //plus de 1 extrudeur
    tHotend = int(degHotend(1) + 0.5); //temperature hotend1 entier
    tTarget = int(degTargetHotend(1) + 0.5); //temperature consigne1 entier
    lcd.print(LCD_STR_THERMOMETER[0]);  //affiche le symbole thermometre
#  else//Heated bed
    tHotend=int(degBed() + 0.5); //temperature bed entier
    tTarget=int(degTargetBed() + 0.5); //temperature consigne entier
    lcd.print(LCD_STR_BEDTEMP[0]); //affiche symbole temperature bed
#  endif //fin EXTRUDERS > 1
    lcd.print(itostr3(tHotend)); //affiche temperature bed entier
    lcd.print('/'); //affiche separateur
    lcd.print(itostr3left(tTarget)); //affiche temperature consigne bed
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0

#else//LCD_WIDTH > 19 //afficheur de 20 caracteres
    lcd.setCursor(0, 0); //curseur en home
    lcd.print(LCD_STR_THERMOMETER[0]); //affiche le symbole thermometre
    lcd.print(itostr3(tHotend)); //temperature hotend
    lcd.print('/'); //affiche separateur
    lcd.print(itostr3left(tTarget)); //temperature consigne hotend
    lcd_printPGM(PSTR(LCD_STR_DEGREE " ")); //affiche symbole �
    if (tTarget < 10)
        lcd.print(' ');

# if EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
    //If we have an 2nd extruder or heated bed, show that in the top right corner
    lcd.setCursor(10, 0);
#  if EXTRUDERS > 1
    tHotend = int(degHotend(1) + 0.5);
    tTarget = int(degTargetHotend(1) + 0.5);
    lcd.print(LCD_STR_THERMOMETER[0]);
#  else//Heated bed
    tHotend=int(degBed() + 0.5); //temperature bed entier
    tTarget=int(degTargetBed() + 0.5); //temperature consigne bed entier
    lcd.print(LCD_STR_BEDTEMP[0]); //affiche symbole temperature bed
#  endif
    lcd.print(itostr3(tHotend)); //
    lcd.print('/'); //affiche separateur
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " ")); //symbole �
    if (tTarget < 10)
        lcd.print(' ');
# endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
#endif//LCD_WIDTH > 19

#if LCD_HEIGHT > 2
//Lines 2 for 4 line LCD
# if LCD_WIDTH < 20
#  ifdef SDSUPPORT
    lcd.setCursor(0, 2);
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif//SDSUPPORT
# else//LCD_WIDTH > 19
#  if EXTRUDERS > 1 && TEMP_SENSOR_BED != 0
    //If we both have a 2nd extruder and a heated bed, show the heated bed temp on the 2nd line on the left, as the first line is filled with extruder temps
    tHotend=int(degBed() + 0.5);
    tTarget=int(degTargetBed() + 0.5);

    lcd.setCursor(0, 1);
    lcd.print(LCD_STR_BEDTEMP[0]);
    lcd.print(itostr3(tHotend));
    lcd.print('/');
    lcd.print(itostr3left(tTarget));
    lcd_printPGM(PSTR(LCD_STR_DEGREE " "));
    if (tTarget < 10)
        lcd.print(' ');
#  else
    lcd.setCursor(0,1);
    lcd.print('X');
//    lcd.print(ftostr3(current_position[X_AXIS])); //icare modification
    lcd.print(ftostr3i(current_position[X_AXIS])); //icare modification
    lcd_printPGM(PSTR(" Y"));
//    lcd.print(ftostr3(current_position[Y_AXIS])); //icare modification
    lcd.print(ftostr3i(current_position[Y_AXIS])); //icare modification
#  endif//EXTRUDERS > 1 || TEMP_SENSOR_BED != 0
# endif//LCD_WIDTH > 19
    lcd.setCursor(LCD_WIDTH - 8, 1);
//    lcd.print('Z');
    lcd.print("Z "); //icare modification space between Z and number
    lcd.print(ftostr32(current_position[Z_AXIS]));
#endif//LCD_HEIGHT > 2

#if LCD_HEIGHT > 3
    lcd.setCursor(0, 2);
    lcd.print(LCD_STR_FEEDRATE[0]);
    lcd.print(itostr3(feedmultiply));
    lcd.print('%');
# if LCD_WIDTH > 19
#  ifdef SDSUPPORT
    lcd.setCursor(7, 2);
    lcd_printPGM(PSTR("SD"));
    if (IS_SD_PRINTING)
        lcd.print(itostr3(card.percentDone()));
    else
        lcd_printPGM(PSTR("---"));
    lcd.print('%');
#  endif//SDSUPPORT
# endif//LCD_WIDTH > 19
    lcd.setCursor(LCD_WIDTH - 6, 2);
    lcd.print(LCD_STR_CLOCK[0]);
    if(starttime != 0)
    {
        uint16_t time = millis()/60000 - starttime/60000;
        lcd.print(itostr2(time/60));
        lcd.print(':');
        lcd.print(itostr2(time%60));
    }else{
        lcd_printPGM(PSTR("--:--"));
    }
#endif

    //Status message line on the last line
    lcd.setCursor(0, LCD_HEIGHT - 1);
    lcd.print(lcd_status_message);
	lcd_implementation_update_indicators();
}
static void lcd_implementation_drawmenu_generic(uint8_t row, const char* pstr, char pre_char, char post_char)
{
    char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1;
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2;
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    while(n--)
        lcd.print(' ');
    lcd.print(post_char);
    lcd.print(' ');
}
static void lcd_implementation_drawmenu_setting_edit_generic(uint8_t row, const char* pstr, char pre_char, char* data)
{
  char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1 - strlen(data);
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2 - strlen(data);
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    lcd.print(':');
    while(n--)
        lcd.print(' ');
    lcd.print(data);
}
static void lcd_implementation_drawmenu_setting_edit_generic_P(uint8_t row, const char* pstr, char pre_char, const char* data)
{
  char c;
    //Use all characters in narrow LCDs
  #if LCD_WIDTH < 20
    	uint8_t n = LCD_WIDTH - 1 - 1 - strlen_P(data);
    #else
    	uint8_t n = LCD_WIDTH - 1 - 2 - strlen_P(data);
  #endif
    lcd.setCursor(0, row);
    lcd.print(pre_char);
    while((c = pgm_read_byte(pstr)) != '\0')
    {
        lcd.print(c);
        pstr++;
        n--;
    }
    lcd.print(':');
    while(n--)
        lcd.print(' ');
    lcd_printPGM(data);
}
#define lcd_implementation_drawmenu_setting_edit_int3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_int3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_bool_selected(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define lcd_implementation_drawmenu_setting_edit_bool(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))

//Add version for callback functions
#define lcd_implementation_drawmenu_setting_edit_callback_int3_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_int3(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float3_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float3(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float32_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float32(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float5_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float5(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float52_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float52(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float51_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_float51(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_long5_selected(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_long5(row, pstr, pstr2, data, minValue, maxValue, callback) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_callback_bool_selected(row, pstr, pstr2, data, callback) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define lcd_implementation_drawmenu_setting_edit_callback_bool(row, pstr, pstr2, data, callback) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))


void lcd_implementation_drawedit(const char* pstr, char* value)
{
    lcd.setCursor(1, 1);
    lcd_printPGM(pstr);
    lcd.print(':');
   #if LCD_WIDTH < 20
    	lcd.setCursor(LCD_WIDTH - strlen(value), 1);
    #else
    	lcd.setCursor(LCD_WIDTH -1 - strlen(value), 1);
   #endif
    lcd.print(value);
	lcd_implementation_update_indicators();
}
static void lcd_implementation_drawmenu_sdfile_selected(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 1;
    lcd.setCursor(0, row);
    lcd.print('>');
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-1] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sdfile(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 1;
    lcd.setCursor(0, row);
    lcd.print(' ');
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-1] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sddirectory_selected(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 2;
    lcd.setCursor(0, row);
    lcd.print('>');
    lcd.print(LCD_STR_FOLDER[0]);
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-2] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
static void lcd_implementation_drawmenu_sddirectory(uint8_t row, const char* pstr, const char* filename, char* longFilename)
{
    char c;
    uint8_t n = LCD_WIDTH - 2;
    lcd.setCursor(0, row);
    lcd.print(' ');
    lcd.print(LCD_STR_FOLDER[0]);
    if (longFilename[0] != '\0')
    {
        filename = longFilename;
        longFilename[LCD_WIDTH-2] = '\0';
    }
    while((c = *filename) != '\0')
    {
        lcd.print(c);
        filename++;
        n--;
    }
    while(n--)
        lcd.print(' ');
}
#define lcd_implementation_drawmenu_back_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, LCD_STR_UPLEVEL[0], LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_back(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_submenu_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', LCD_STR_ARROW_RIGHT[0])
#define lcd_implementation_drawmenu_submenu(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', LCD_STR_ARROW_RIGHT[0])
#define lcd_implementation_drawmenu_gcode_selected(row, pstr, gcode) lcd_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define lcd_implementation_drawmenu_gcode(row, pstr, gcode) lcd_implementation_drawmenu_generic(row, pstr, ' ', ' ')
#define lcd_implementation_drawmenu_function_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define lcd_implementation_drawmenu_function(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', ' ')

static void lcd_implementation_quick_feedback()
{
  //Buzzer on the Panelolu2 accessed over I2C
  #ifdef PAN_BEEP
     lcd.buzz(300,2000);
  #endif
  lcd_implementation_update_indicators();
}

static void lcd_implementation_update_indicators()
{
  //set the LEDS - referred to as backlights by the LiquidTWI2 library 
  static uint8_t ledsprev = 0;
  uint8_t leds = 0;
  if (isHeatingBed()) leds |= LED_A;
  if (isHeatingHotend(0)) leds |= LED_B;
  if (fanSpeed) leds |= LED_C;
  #if EXTRUDERS > 1  
    if (isHeatingHotend(1)) leds |= LED_C;
  #endif
  if (leds != ledsprev) {
    lcd.setBacklight(leds);
    ledsprev = leds;
  }
}

#endif//ULTRA_LCD_IMPLEMENTATION_PANELOLU2_H
