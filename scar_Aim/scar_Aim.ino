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

const int btnPin = 9;
int btnState;
int lastBtnState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

int draw_state = 0;
/*
  int rand_run=0;
  uint8_t draw_state = 0;
  uint8_t rand_run=0;
*/

void CrossA() { // +
  u8g.drawLine(61, 31, 81, 31);
  u8g.drawLine(71, 21, 71, 41);
}
void CrossB() { // ++
  u8g.drawLine(49, 31, 93, 31);
  u8g.drawLine(71, 9, 71, 53);
}
void CrossC() {
  u8g.drawLine(71, 31, 62, 40);
  u8g.drawLine(71, 31, 80, 40);
}
void draw() {
  u8g.drawDisc(71, 31, 1); // 瀹炲績鍦�
  u8g.drawCircle(71, 31, 15, U8G2_DRAW_ALL); // 绌哄績鍦�
}
void drawB() {
  u8g.drawDisc(71, 31, 2); // 瀹炲績鍦�
}
void drawCircle() {
  u8g.drawCircle(71, 31, 5, U8G2_DRAW_ALL);
}
void drawDiscL() {
  u8g.drawDisc(71, 31, 2, U8G2_DRAW_ALL);
  u8g.drawLine(63, 31, 57, 31);
  u8g.drawLine(79, 31, 85, 31);
}

void nerf_Aim(void) {
  //u8g.drawLine(x1,y1, x2,y2);
  /**/ // aim test Start.
  
  u8g.drawDisc(71, 31, 2, U8G2_DRAW_ALL);
  u8g.drawLine(62, 31, 56, 31);
  u8g.drawLine(80, 31, 86, 31);
  
  //*/ // aim test End.
  /* /
  switch (draw_state) {
    case 0: CrossA(); break;
    case 1: CrossB(); break;
    case 2: CrossC(); break;
    case 3: draw(); break;
    case 4: drawB(); break;
    case 5: drawCircle(); break;
    case 6: drawDiscL(); break;
      //case 7: discAim3(); break;
      //case 8: lineAim(); break;
      //default: CrossA();
  }
  /**/
}

void setup(void) {
  //Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(btnPin, INPUT); // INPUT or OUTPUT or INPUT_PULLUP
  u8g.begin();
  draw_state = random(0, 6);
}
void loop(void) {
  u8g.clearBuffer();
  //u8g.firstPage();do{
  nerf_Aim();
  u8g.sendBuffer();
  //}while(u8g.nextPage());

  int reading = digitalRead(btnPin);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != btnState) {
      btnState = reading;
      if (btnState == HIGH) {
        //draw_state++;
      }
    }
  }
  lastBtnState = reading;
  if (draw_state >= 7) {
    //draw_state = 0;
  }
  /**
    if (reading == HIGH) {
    draw_state++;
    }
    /**/
}

