#define START_BMPWIDTH 	60	//Width in pixels
#define START_BMPHEIGHT 	64	//Height in pixels
#define START_BMPBYTEWIDTH 	8	//Width in bytes
unsigned char start_bmp[574] PROGMEM = { //AVR-GCC, WinAVR
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xF9,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xF0,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xE0,0x7F,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xC0,0x3F,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0x80,0x1F,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0x00,0x0F,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFE,0x00,0x07,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xF0,
0xFF,0xFF,0xF8,0x00,0x01,0xFF,0xFF,0xF0,
0xFF,0xFF,0xF0,0x00,0x00,0xFF,0xFF,0xF0,
0xFF,0xFF,0xE0,0x00,0x00,0x7F,0xFF,0xF0,
0xFF,0xFF,0xC0,0x00,0x00,0x3F,0xFF,0xF0,
0xFF,0xFF,0x80,0x00,0x00,0x3F,0xFF,0xF0,
0xFF,0xFF,0x00,0x00,0x00,0x1F,0xFF,0xF0,
0xFF,0xFE,0x00,0x00,0x00,0x0F,0xFF,0xF0,
0xFF,0xFE,0x00,0x00,0x00,0x07,0xFF,0xF0,
0xFF,0xFC,0x00,0x00,0x00,0x07,0xFF,0xF0,
0xFF,0xFC,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xF8,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xFC,0x00,0x00,0x00,0x03,0xFF,0xF0,
0xFF,0xFC,0x00,0x00,0x00,0x07,0xFF,0xF0,
0xFF,0xFE,0x00,0x00,0x00,0x07,0xFF,0xF0,
0xFF,0xFE,0x00,0x00,0x00,0x0F,0xFF,0xF0,
0xFF,0xFF,0x00,0x00,0x00,0x1F,0xFF,0xF0,
0xFF,0xFF,0x80,0x00,0x00,0x1F,0xFF,0xF0,
0xFF,0xFF,0xC0,0x00,0x00,0x3F,0xFF,0xF0,
0xFF,0xFF,0xE0,0x00,0x00,0x7F,0xFF,0xF0,
0xFF,0xFF,0xF0,0x00,0x01,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0x00,0x1F,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0x83,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xF0,
0x80,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xF0,
0x88,0x7F,0xFF,0xFE,0x23,0xFF,0xFF,0xF0,
0x8C,0x70,0x38,0x0E,0x71,0x81,0xC0,0x70,
0x8C,0x60,0x38,0x0E,0x63,0x80,0xC0,0x30,
0x80,0xE3,0x19,0xC6,0x07,0xF8,0xC7,0x30,
0x80,0xE0,0x19,0xC6,0x03,0x80,0xC7,0x10,
0x8C,0x62,0x79,0xC6,0x63,0x9C,0xC7,0x30,
0x8C,0x63,0xF8,0xC6,0x71,0x18,0xC6,0x30,
0x8E,0x30,0x18,0x0E,0x71,0x80,0xC0,0x30,
0x9E,0x38,0x39,0x1E,0x79,0xC4,0xC4,0xF0,
0xFF,0xFF,0xF9,0xFF,0xFF,0xFF,0xC7,0xF0,
0xFF,0xFF,0xF9,0xFF,0xFF,0xFF,0xC7,0xF0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0
};

#define STATUS_SCREENWIDTH 		115	//Width in pixels
#define STATUS_SCREENHEIGHT 	19	//Height in pixels
#define STATUS_SCREENBYTEWIDTH 	15	//Width in bytes
unsigned char status_screen0_bmp[] PROGMEM = { //AVR-GCC, WinAVR
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x0C,0x60,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x47,0x0E,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4F,0x0F,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5F,0x0F,0xA0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5E,0x07,0xA0,
0x7F,0x80,0x00,0x3F,0xC0,0x00,0x3F,0xC0,0x00,0x41,0x04,0x00,0x40,0x60,0x20,
0xFB,0xC0,0x00,0x79,0xE0,0x00,0x79,0xE0,0x00,0x20,0x82,0x00,0x40,0xF0,0x20,
0xF3,0xC0,0x00,0x76,0xE0,0x00,0x76,0xE0,0x00,0x20,0x82,0x00,0x40,0xF0,0x20,
0xEB,0xC0,0x00,0x7E,0xE0,0x00,0x7E,0xE0,0x00,0x41,0x04,0x00,0x40,0x60,0x20,
0x7B,0x80,0x00,0x3D,0xC0,0x00,0x39,0xC0,0x00,0x82,0x08,0x00,0x5E,0x07,0xA0,
0x7B,0x80,0x00,0x3B,0xC0,0x00,0x3E,0xC0,0x01,0x04,0x10,0x00,0x5F,0x0F,0xA0,
0xFB,0xC0,0x00,0x77,0xE0,0x00,0x76,0xE0,0x01,0x04,0x10,0x00,0x4F,0x0F,0x20,
0xFB,0xC0,0x00,0x70,0xE0,0x00,0x79,0xE0,0x00,0x82,0x08,0x00,0x47,0x0E,0x20,
0xFF,0xC0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x41,0x04,0x00,0x63,0x0C,0x60,
0x3F,0x00,0x00,0x1F,0x80,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,0x70,0x00,0xE0,
0x1E,0x00,0x00,0x0F,0x00,0x00,0x0F,0x00,0x01,0xFF,0xFF,0x80,0x7F,0xFF,0xE0,
0x0C,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x01,0xFF,0xFF,0x80,0x00,0x00,0x00
};

#define STATUS_SCREENWIDTH 		115	//Width in pixels
#define STATUS_SCREENHEIGHT 	19	//Height in pixels
#define STATUS_SCREENBYTEWIDTH 	15	//Width in bytes
unsigned char status_screen1_bmp[] PROGMEM = { //AVR-GCC, WinAVR
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x61,0xF8,0x60,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0xF8,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xF0,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x60,0x20,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x58,0x01,0xA0,
0x7F,0x80,0x00,0x3F,0xC0,0x00,0x3F,0xC0,0x00,0x41,0x04,0x00,0x5C,0x63,0xA0,
0xFB,0xC0,0x00,0x79,0xE0,0x00,0x79,0xE0,0x00,0x20,0x82,0x00,0x5E,0xF7,0xA0,
0xF3,0xC0,0x00,0x76,0xE0,0x00,0x76,0xE0,0x00,0x20,0x82,0x00,0x5E,0xF7,0xA0,
0xEB,0xC0,0x00,0x7E,0xE0,0x00,0x7E,0xE0,0x00,0x41,0x04,0x00,0x5C,0x63,0xA0,
0x7B,0x80,0x00,0x3D,0xC0,0x00,0x39,0xC0,0x00,0x82,0x08,0x00,0x58,0x01,0xA0,
0x7B,0x80,0x00,0x3B,0xC0,0x00,0x3E,0xC0,0x01,0x04,0x10,0x00,0x40,0x60,0x20,
0xFB,0xC0,0x00,0x77,0xE0,0x00,0x76,0xE0,0x01,0x04,0x10,0x00,0x40,0xF0,0x20,
0xFB,0xC0,0x00,0x70,0xE0,0x00,0x79,0xE0,0x00,0x82,0x08,0x00,0x41,0xF8,0x20,
0xFF,0xC0,0x00,0x7F,0xE0,0x00,0x7F,0xE0,0x00,0x41,0x04,0x00,0x61,0xF8,0x60,
0x3F,0x00,0x00,0x1F,0x80,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,0x70,0x00,0xE0,
0x1E,0x00,0x00,0x0F,0x00,0x00,0x0F,0x00,0x01,0xFF,0xFF,0x80,0x7F,0xFF,0xE0,
0x0C,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x01,0xFF,0xFF,0x80,0x00,0x00,0x00
};



