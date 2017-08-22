
#include <U8glib.h>
// IIC
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);  // HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)

void nerfCross(){ // +
  u8g.drawLine(63,25, 63,37);
  u8g.drawLine(57,31, 69,31);
}
void nerfCrossB(){ // ++
  u8g.drawLine(63,15, 63,46);
  u8g.drawLine(47,31, 78,31);
}
void nerfWarp(){ // []
  u8g.drawLine(5,0, 0,5);//L
  u8g.drawLine(0,5, 0,58);
  u8g.drawLine(0,58, 5,63);
  u8g.drawLine(122,0, 127,5);//R
  u8g.drawLine(127,5, 127,58);
  u8g.drawLine(127,58, 122,63);
}
void intbox(){ // < >
  u8g.drawLine(58,11, 57,10);//1
  u8g.drawLine(57,10, 54,10);
  u8g.drawLine(54,10, 42,22);
  u8g.drawLine(42,22, 42,25);
  u8g.drawLine(42,25, 43,26);
  u8g.drawLine(43,35, 42,36);//2
  u8g.drawLine(42,36, 42,39);
  u8g.drawLine(42,39, 54,51);
  u8g.drawLine(54,51, 57,51);
  u8g.drawLine(57,51, 58,50);
  u8g.drawLine(67,11, 68,10);//3
  u8g.drawLine(68,10, 71,10);
  u8g.drawLine(71,10, 83,22);
  u8g.drawLine(83,22, 83,25);
  u8g.drawLine(83,25, 82,26);
  u8g.drawLine(82,35, 83,36);//4
  u8g.drawLine(83,36, 83,39);
  u8g.drawLine(83,39, 71,51);
  u8g.drawLine(71,51, 68,51);
  u8g.drawLine(71,51, 67,50);
}
void intboxB(){
  u8g.drawLine(55,1, 54,0);//1
  u8g.drawLine(54,0, 50,0);
  u8g.drawLine(50,0, 32,18);
  u8g.drawLine(32,18, 32,22);
  u8g.drawLine(32,22, 33,23);
  u8g.drawLine(33,39, 32,40);//2
  u8g.drawLine(32,40, 32,44);
  u8g.drawLine(32,44, 50,62);
  u8g.drawLine(50,62, 54,62);
  u8g.drawLine(54,62, 55,61);
  u8g.drawLine(71,1, 72,0);//3
  u8g.drawLine(72,0, 76,0);
  u8g.drawLine(76,0, 94,18);
  u8g.drawLine(94,18, 94,22);
  u8g.drawLine(94,22, 93,23);
  u8g.drawLine(93,39, 94,40);//4
  u8g.drawLine(94,40, 94,44);
  u8g.drawLine(94,44, 76,62);
  u8g.drawLine(76,62, 72,62);
  u8g.drawLine(72,62, 71,61);
}
 
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  nerfCross();
  //nerfCrossB();
  //nerfWarp();
  //intbox();
  intboxB();
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
}

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}

