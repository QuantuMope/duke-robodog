#include <Servo.h>

// F = Forward, B = Back, L = Left, R = Right, 1 = Top, 2 = Bottom
Servo Head;
Servo FL1;
Servo FL2;
Servo BL1;
Servo BL2;
Servo FR1;
Servo FR2;
Servo BR1;
Servo BR2;
Servo Tail;
int front_left_top_angle;
int front_right_top_angle;
int front_left_bottom_angle;
int front_right_bottom_angle;
int back_left_top_angle;
int back_right_top_angle;
int back_left_bottom_angle;
int back_right_bottom_angle;
byte com;


void setup() {
  Head.attach(2);
  FL1.attach(3);
  FL2.attach(5);
  BL1.attach(7);
  BL2.attach(9);
  FR1.attach(4);
  FR2.attach(6);
  BR1.attach(8);
  BR2.attach(10);
  Tail.attach(11);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  delay(2000);
  Serial.write(0xAA);
  Serial.write(0x37);
  delay(1000);
  Serial.write(0xAA);
  Serial.write(0x21);
  
}

void standup()
{
  Head.write(94);
  FL1.write(83);
  FL2.write(98);
  FR1.write(85);
  FR2.write(96);
  BL1.write(88);
  BL2.write(82);
  BR1.write(90);
  BR2.write(86);
  Tail.write(87);
}


void stretch()
{
  front_right_top_angle = 85;
  front_left_bottom_angle = 98;
  front_right_bottom_angle = 96;
  back_left_top_angle = 88;
  back_right_top_angle = 90;
  back_left_bottom_angle = 82;
  back_right_bottom_angle = 86;
  for (front_left_top_angle = 83; front_left_top_angle > 43; front_left_top_angle -=1)
  {
    FL1.write(front_left_top_angle);
    BL1.write(back_left_top_angle);
    FR1.write(front_right_top_angle);
    BR1.write(back_right_top_angle);
    FL2.write(front_left_bottom_angle);
    BL2.write(back_left_bottom_angle);
    FR2.write(front_right_bottom_angle);
    BR2.write(back_right_bottom_angle);
    front_right_top_angle += 1;
    front_left_bottom_angle += 1;
    front_right_bottom_angle -= 1;
    back_left_top_angle += 1;
    back_right_top_angle -= 1;
    back_left_bottom_angle -= 1;
    back_right_bottom_angle += 1;
    delay(50);
  }
  for (front_left_top_angle = 43; front_left_top_angle < 83; front_left_top_angle +=1)
  {
    FL1.write(front_left_top_angle);
    BL1.write(back_left_top_angle);
    FR1.write(front_right_top_angle);
    BR1.write(back_right_top_angle);
    FL2.write(front_left_bottom_angle);
    BL2.write(back_left_bottom_angle);
    FR2.write(front_right_bottom_angle);
    BR2.write(back_right_bottom_angle);
    front_right_top_angle -= 1;
    front_left_bottom_angle -= 1;
    front_right_bottom_angle += 1;
    back_left_top_angle -= 1;
    back_right_top_angle += 1;
    back_left_bottom_angle += 1;
    back_right_bottom_angle -= 1;
    delay(50);
  }
}
  
void sit()
{
  front_left_top_angle = 83;
  front_right_top_angle = 85;
  front_left_bottom_angle = 98;
  front_right_bottom_angle = 96;
  back_left_top_angle = 88;
  back_right_top_angle = 90;
  back_left_bottom_angle = 82;
  back_right_bottom_angle = 86;
  for (back_left_top_angle = 82; back_left_top_angle < 150; back_left_top_angle += 4)
  {
    FL1.write(front_left_top_angle);
    BL1.write(back_left_top_angle);
    FR1.write(front_right_top_angle);
    BR1.write(back_right_top_angle);
    FL2.write(front_left_bottom_angle);
    BL2.write(back_left_bottom_angle);
    FR2.write(front_right_bottom_angle);
    BR2.write(back_right_bottom_angle);
    front_left_top_angle += 1;
    front_right_top_angle -= 1;
    front_left_bottom_angle -= 0;
    front_right_bottom_angle += 0;
    back_right_top_angle -= 4;
    back_left_bottom_angle -= 4;
    back_right_bottom_angle += 4;
    delay(100);
  }
}

void tailwag()
{
  for (int i = 0; i < 5; i++)
  {
    Tail.write(10);
    delay(100);
    Tail.write(170);
    delay(100);
  }
}


void loop() {

  while(Serial.available()){
    com = Serial.read();
    switch(com){

      case 0x11:

        tone(12,1200,500);
        delay(500);
        standup();

      break;

      case 0x12:

      sit();

      break;

      case 0x13:

      stretch();

      break;

      case 0x14:

      tone(12,2400,200);
      delay(300);
      tone(12,2400,200);
      delay(500);
      standup();
      delay(500);
      tailwag();
      delay(100);
      Tail.write(87);

      break;

      case 0x15:

      tone(12,500,1000);
      standup();

      break;
      
    }
  }

}
 

