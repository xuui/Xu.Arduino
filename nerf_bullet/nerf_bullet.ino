#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//const;
int btnPin = 9;
int iNum = 200;

void showNum(int num) {
  char str[20];
  char N1[20] = "0";
  char N2[20] = "00";
  itoa(num, str, 10);
  //strcat(N1,str);

  u8g2.firstPage();
  do {
    if (num <= 99) {
      if (num <= 9) {
        u8g2.drawStr(0, 63, strcat(N2, str));
      } else {
        u8g2.drawStr(0, 63, strcat(N1, str));
      }
    } else {
      u8g2.drawStr(0, 63, str);
    }
    //u8g2.drawStr(0,63,"Hello!"+str);
  } while (u8g2.nextPage());
  delay(65);
}

void setup(void) {
  pinMode(btnPin,OUTPUT);
  //pinMode(btnPin,INPUT);
  u8g2.begin();
  //u8g2.begin(7,A1,A2,A0,9,8);
  u8g2.setFont(u8g2_font_logisoso62_tn);
}

void loop(void) {
  showNum(iNum);
  
  int n = digitalRead(btnPin);
  //if (n == LOW) {
  if (n == HIGH) {
     if (iNum > 0) iNum--;
  }

}

