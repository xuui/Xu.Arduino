int Sensor_pin = 13;
int Led_pin = 4; //3

void setup() {
  Serial.begin(9600);
  pinMode(Sensor_pin,INPUT);
  pinMode(Led_pin,OUTPUT);
}
void loop() {
  int SensorState=digitalRead(Sensor_pin);
  Serial.println(SensorState);

  if(SensorState == 1){ 
    Alarm();
  }else{
    return;
  }
  delay(100);
}

void Alarm(){
  for(int i=0;i<100;i++){
    digitalWrite(Led_pin,HIGH); //led 点亮
    digitalWrite(Led_pin,LOW); //led 熄灭
  }
}

