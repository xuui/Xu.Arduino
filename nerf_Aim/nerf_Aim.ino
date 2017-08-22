#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_F_6800 u8g(U8G2_R0, 13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_8080 u8g(U8G2_R0, 13, 11, 2, 3, 4, 5, 6, A4, /*enable=*/ 7, /*cs=*/ 10, /*dc=*/ 9, /*reset=*/ 8);

const int btnPin = 9;
int draw_state = 0;

void nerfCross() { // +
  u8g.drawLine(63, 25, 63, 37);
  u8g.drawLine(57, 31, 69, 31);
}
void nerfCrossB() { // ++
  u8g.drawLine(63, 15, 63, 46);
  u8g.drawLine(47, 31, 78, 31);
}
void nerfWarp() { // []
  u8g.drawLine(5, 0, 0, 5); //L
  u8g.drawLine(0, 5, 0, 58);
  u8g.drawLine(0, 58, 5, 63);
  u8g.drawLine(122, 0, 127, 5); //R
  u8g.drawLine(127, 5, 127, 58);
  u8g.drawLine(127, 58, 122, 63);
}
void intbox() { // < >
  u8g.drawLine(58, 11, 57, 10); //1
  u8g.drawLine(57, 10, 54, 10);
  u8g.drawLine(54, 10, 42, 22);
  u8g.drawLine(42, 22, 42, 25);
  u8g.drawLine(42, 25, 43, 26);
  u8g.drawLine(43, 35, 42, 36); //2
  u8g.drawLine(42, 36, 42, 39);
  u8g.drawLine(42, 39, 54, 51);
  u8g.drawLine(54, 51, 57, 51);
  u8g.drawLine(57, 51, 58, 50);
  u8g.drawLine(67, 11, 68, 10); //3
  u8g.drawLine(68, 10, 71, 10);
  u8g.drawLine(71, 10, 83, 22);
  u8g.drawLine(83, 22, 83, 25);
  u8g.drawLine(83, 25, 82, 26);
  u8g.drawLine(82, 35, 83, 36); //4
  u8g.drawLine(83, 36, 83, 39);
  u8g.drawLine(83, 39, 71, 51);
  u8g.drawLine(71, 51, 68, 51);
  u8g.drawLine(68, 51, 67, 50);
}
void intboxB() {
  u8g.drawLine(55, 1, 54, 0); //1
  u8g.drawLine(54, 0, 50, 0);
  u8g.drawLine(50, 0, 32, 18);
  u8g.drawLine(32, 18, 32, 22);
  u8g.drawLine(32, 22, 33, 23);
  u8g.drawLine(33, 39, 32, 40); //2
  u8g.drawLine(32, 40, 32, 44);
  u8g.drawLine(32, 44, 50, 62);
  u8g.drawLine(50, 62, 54, 62);
  u8g.drawLine(54, 62, 55, 61);
  u8g.drawLine(71, 1, 72, 0); //3
  u8g.drawLine(72, 0, 76, 0);
  u8g.drawLine(76, 0, 94, 18);
  u8g.drawLine(94, 18, 94, 22);
  u8g.drawLine(94, 22, 93, 23);
  u8g.drawLine(93, 39, 94, 40); //4
  u8g.drawLine(94, 40, 94, 44);
  u8g.drawLine(94, 44, 76, 62);
  u8g.drawLine(76, 62, 72, 62);
  u8g.drawLine(72, 62, 71, 61);
}

void discWarp() {
  u8g.drawCircle(63, 31, 63, U8G2_DRAW_ALL); // 空心圆
  //u8g.drawCircle(63,31, 31, U8G2_DRAW_ALL);
}

void disci() {
  u8g.drawDisc(63, 31, 3); // 实心圆
}
void discAim() {
  u8g.drawCircle(63, 31, 21, U8G2_DRAW_ALL);; // 空心圆
  u8g.drawDisc(63, 31, 3); // 实心圆
}
void discAim2() {
  u8g.drawCircle(63, 31, 21, U8G2_DRAW_ALL);; // 空心圆
  u8g.setDrawColor(0); //透明色
  u8g.drawBox(59, 8, 9, 5); // 方块
  u8g.setDrawColor(1);
  u8g.drawDisc(63, 31, 3); // 实心圆
  u8g.drawDisc(63, 23, 1);
  u8g.drawDisc(63, 17, 1);
  u8g.drawDisc(63, 11, 1);
}
void discAim3() {
  u8g.drawCircle(63, 31, 31, U8G2_DRAW_ALL);
  u8g.drawDisc(63, 31, 3, U8G2_DRAW_ALL);
  u8g.drawLine(32, 31, 42, 31);
  u8g.drawLine(94, 31, 84, 31);
  u8g.drawLine(63, 0, 63, 11);
  u8g.drawLine(63, 62, 63, 52);
}
void lineAim() {
  u8g.drawDisc(63, 31, 3, U8G2_DRAW_ALL);
  u8g.drawLine(53, 31, 43, 31);
  u8g.drawLine(73, 31, 83, 31);
}

void nerf_Aim(void) {
  //nerfCross();
  //nerfCrossB();
  //nerfWarp();
  //intbox();
  //intboxB();
  //discWarp();
  //discAim();
  //discAim2();
  //discAim3();
  //lineAim();
  //u8g.drawCircle(63,31, 31, U8G2_DRAW_ALL);

  /**/
  switch (draw_state) {
    case 0: nerfCross(); intbox(); break;
    case 1: nerfCrossB(); intboxB(); break;
    case 2: nerfWarp(); nerfCross(); intbox(); break;
    case 3: discAim(); break;
    case 4: discWarp(); discAim(); break;
    case 5: discWarp(); disci(); break;
    case 6: discAim2(); break;
    case 7: discAim3(); break;
    case 8: lineAim(); break;
    default: lineAim();
  }

}

void setup(void) {
  //Serial.begin(9600);
  pinMode(btnPin,INPUT_PULLUP); // INPUT or OUTPUT
  u8g.begin();
}
void loop(void) {
  u8g.clearBuffer();         // clear the internal memory
  nerf_Aim();
  u8g.sendBuffer();          // transfer internal memory to the display
  
  int reading = digitalRead(btnPin);
  //Serial.println(reading);
  if(reading==HIGH){
    draw_state++;
  }else{
  }
  if(draw_state>= 9){
    draw_state = 0;
  }
  delay(100);
}


