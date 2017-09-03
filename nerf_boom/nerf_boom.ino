#include <Arduino.h>
#include <U8g2lib.h>
#include <Keypad.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=SDA/ A4, /* data=SCL/ A5, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

/* Keypad 4x4 */
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 10, 11, 12}; //connect to the column pinouts of the keypad
/** // Keypad 3x4 *//*
  const byte ROWS=4; //four rows
  const byte COLS=3; //four columns
  char hexaKeys[ROWS][COLS]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
  byte rowPins[ROWS]={5,6,7,8}; //connect to the row pinouts of the keypad
  byte colPins[COLS]={9,10,11}; //connect to the column pinouts of the keypad
*/

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

/**********************************************************/
const int ledPin = 3;
const int biPin = 4;

char keyInput = "";
int passState = 0;
int countDown = 60; // 倒计时时间
int loopState = 1;
int loopTime = 17;

int KeyLockED = 0; // 键盘锁定
int randPassKey; // 随机密匙
int inputKey = 16;
/**********************************************************/

void oledShow() {
  //u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_profont22_tf);
  u8g2.setCursor(1, 15);
  //u8g2.print("Pass:");
  //u8g2.print(randPassKey);
  //u8g2.print(":");
  if (inputKey == randPassKey) {
    //u8g2.print(inputKey);
    u8g2.print("Unlocked!");
    KeyLockED = 1;
  }

  //u8g2.setDrawColor(1);
  //u8g2.drawBox(0,16,128,64);
  //u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_logisoso38_tf );
  u8g2.setCursor(1, 62);
  u8g2.print(countDown);

  if (inputKey == randPassKey) {
    //u8g2.setFont(u8g2_font_unifont_t_symbols);
    //u8g2.drawGlyph(100, 12, 0x2713);
    digitalWrite(ledPin, HIGH);
  } else {
    //u8g2.setFont(u8g2_font_unifont_t_symbols);
    //u8g2.drawGlyph(100, 12, 0x2717);
    digitalWrite(ledPin, LOW);
  }
}
/**/
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  keypad.addEventListener(keypadEvent);  // Add an event listener for this keypad
  u8g2.begin();
  //u8g2.setFont(u8g2_font_ncenB14_tr);

  //analogWrite(3, 255);// +
  //pinMode(4, OUTPUT);// - INPUT
  pinMode(biPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  randPassKey = random(0, 15);

  Serial.print("PassKey: ");
  Serial.println(randPassKey);
}

void loop() {
  u8g2.firstPage(); do {
    oledShow();
  } while (u8g2.nextPage());

  char key = keypad.getKey();
  //if(key){Serial.println(key);}

  //ledLoopTime();
  if (loopState == 1) {
    if (countDown != 0) { // 倒计时是否为0
      if (loopTime != 0) {
        loopTime--;
      } else {
        loopTime = 16;
        countDown--;
        //Serial.println(millis());
      }
      digitalWrite(biPin, LOW);
    } else {
      digitalWrite(biPin, HIGH);
      KeyLockED = 1;
    }
  }

  if (inputKey == randPassKey) {
    loopState = 0;
  } else {
    loopState = 1;
  }

  //delay(10);
}

void keypadEvent(KeypadEvent key) {
  //Serial.print("Pressed Keypad: ");
  //Serial.println(key);
  switch (keypad.getState()) {
    case PRESSED: // 按下
      if (KeyLockED == 0) {
        switch (key) {
          case '0':
            inputKey = 0;
            break;
          case '1':
            inputKey = 1;
            break;
          case '2':
            inputKey = 2;
            break;
          case '3':
            inputKey = 3;
            break;
          case '4':
            inputKey = 4;
            break;
          case '5':
            inputKey = 5;
            break;
          case '6':
            inputKey = 6;
            break;
          case '7':
            inputKey = 7;
            break;
          case '8':
            inputKey = 8;
            break;
          case '9':
            inputKey = 9;
            break;
          case '*':
            inputKey = 10;
            break;
          case '#':
            inputKey = 11;
            countDown = 3;
            //digitalWrite(ledPin,!digitalRead(ledPin));
            //ledPin_state=digitalRead(ledPin);        // Remember LED state, lit or unlit.
            break;
          case 'A':
            inputKey = 12;
            break;
          case 'B':
            inputKey = 13;
            break;
          case 'C':
            inputKey = 14;
            break;
          case 'D':
            inputKey = 15;
            break;
        }
      }
      break;
    case RELEASED: // 放开
      if (key == '*') {
        //digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
        //blink = false;
      }
      break;
    case HOLD: // 按住
      switch (key) {
        case 'D':
          KeyLockED = 0;
          break;
        case 'B':
          //if(KeyLockED==0)
          countDown = 60;
          //loopState=1;
          break;
      }
      break;
  }
}

