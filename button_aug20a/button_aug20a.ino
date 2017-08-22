/*
 * 使用电阻
 *//*
const int btnPin = 2;
const int ledPin = 13;
int ledState = HIGH;
int btnState;
int lastBtnState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;

void setup(){
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int reading = digitalRead(btnPin);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != btnState) {
      btnState = reading;
      if (btnState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  lastBtnState = reading;
}
*/

// 不使用电阻
void setup() {
  // 开启串行通信，并设置其频率为9600。
  // 如果没有特别要求，此数值一般都为9600。
  Serial.begin(9600);
  // 配置2号针脚为输入状态，
  // 并设置使用内部上拉电阻。
  pinMode(9, INPUT_PULLUP);
  // 定义LED输入针脚号为13号针脚。
  // 注：此处我们使用的LED神灯是Arduino UNO电路板自带，
  // 此神灯对应的针脚号默认为13，此数值不得随意更改，
  // 所以这里定义的数值13是为了和默认值相对应。
  pinMode(13, OUTPUT);
}
// 系统调用，无限循环方法
void loop() {
  // 读取2号针脚上的输入信号的数值
  int sensorVal = digitalRead(9);
  // 为了更直观的看到2号针脚输入的信号值，
  // 将获取到的数值打印到串行调试窗口，方便调试。
  Serial.println(sensorVal);
  // 如果获取到的数值为HIGH(数值大小等于1)，
  // 则向13号针脚发送LOW信号(数值大小等于0)，熄灭LED神灯，
  // 反之则发送HIGH信号(数值大小等于1)，点亮LED神灯。
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
}
