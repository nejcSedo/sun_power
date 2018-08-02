#include <Servo.h>

#define FOTORES_L A0
#define FOTORES_D A1
#define FOTORES_U A2
#define SERVO_LD 6
#define SERVO_UD 4

Servo ServoLD;
Servo ServoUD;

int sensorValue_D(0);
int sensorValue_L(0);
int sensorValue_U(0);
int sensorTmp(0);
int servoLD_pos(90);
int servoUD_pos(170);
int servo_move_speed(1);
int delay_before_read(100);
int sleep(500);
int position_precision(50);
int Variable1;

void setup() {
  Serial.begin(9600);
  ServoLD.attach(SERVO_LD);
  ServoUD.attach(SERVO_UD,900, 2400);
  ServoLD.write(servoLD_pos);
  ServoUD.write(servoUD_pos);
}

void ServoLD_move(int val) {
  servoLD_pos += val;
  if(servoLD_pos >= 175) {
    servoLD_pos = 175;
  }
  else if(servoLD_pos <= 5) {
    servoLD_pos = 5;
  }
  ServoLD.write(servoLD_pos);
  delay(1);
}

void ServoUD_move(int val) {
  servoUD_pos += val;
  if(servoUD_pos >= 175) {
    servoUD_pos = 175;
  }
  else if(servoUD_pos <= 110) {
    servoUD_pos = 110;
  }
  ServoUD.write(servoUD_pos);
  delay(1);
}

void ReadSensor() {
  sensorValue_D = analogRead(FOTORES_D);
  delay(2);
  sensorValue_L = analogRead(FOTORES_L);
  delay(2);
  sensorValue_U = analogRead(FOTORES_U);
  delay(2);
}

void MoveRight() {
  ServoLD_move(servo_move_speed);
  ReadSensor();
}

void MoveLeft() {
  ServoLD_move(-servo_move_speed);
  ReadSensor();
}

void MoveUp() {
  ServoUD_move(servo_move_speed);
  ReadSensor();
}

void MoveDown() {
  ServoUD_move(-servo_move_speed);
  ReadSensor();
}

void loop() {
  ReadSensor();
  position_precision = map(sensorValue_U, 0, 1023, 100, 35);
  while((sensorValue_D - sensorValue_L) > position_precision && !(servoLD_pos < 6)) {
    MoveLeft();
    delay(delay_before_read);
  }
  while((sensorValue_L - sensorValue_D) > position_precision && !(servoLD_pos > 174)) {
    MoveRight();
    delay(delay_before_read);
  }
  while(((sensorValue_U - sensorValue_D) > position_precision || (sensorValue_U - sensorValue_L) > position_precision) && !(servoUD_pos < 91)) {
    MoveDown();
    delay(delay_before_read);
  }
  while(((sensorValue_D - sensorValue_U) > position_precision || (sensorValue_L - sensorValue_U) > position_precision) && !(servoUD_pos > 174)) {
    MoveUp();
    delay(delay_before_read);
  }
  Serial.println(ServoLD.read());
  Serial.println(ServoUD.read());
  delay(sleep);
}
