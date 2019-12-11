const int trig = 4;
const int echo = 3;
const int motor_11 = 6;
const int motor_12 = 7;
const int motor_21 = 8;
const int motor_22 = 9;
const int motor_31 = 10;
const int motor_32 = 11;
const int solinoid_v = 2;
int step_count = 0;
long duration;
float distance;
int controlMotor_one();//control distance from object
int controlMotor_two_L2R();//motor two left to right direction
int controlMotor_two_R2L();//motor two right to left direction
int controlMotor_three();//motor three control up and down
int solinoid_valve();//on spray for  color
int Stop();//stop all programm

void setup() {
  Serial.begin(9600);
  Serial.println("getting start ");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(motor_11, OUTPUT);
  pinMode(motor_12, OUTPUT);
  pinMode(motor_21, OUTPUT);
  pinMode(motor_22, OUTPUT);
  pinMode(motor_31, OUTPUT);
  pinMode(motor_32, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  //measure distance using sonar
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // delayMicroseconds(2);
  duration = pulseIn(echo, HIGH);
  distance = duration * .034 / 2;
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
  controlMotor_one();
  solinoid_valve();
  controlMotor_two_L2R();
  controlMotor_three();
  controlMotor_two_R2L();
  controlMotor_three();
  if (step_count) {
    Stop();
  }
}

//control motor one  for face distance
int controlMotor_one() {
  Serial.println("motor one");
  if (distance > 8) {
    digitalWrite(motor_11, HIGH);
    digitalWrite(motor_12, LOW);
    //    delay(100);
  }
  else if (distance < 7)
  {
    digitalWrite(motor_11, LOW);
    digitalWrite(motor_12, HIGH);
    delay(100);
  }
  else
  {
    digitalWrite(motor_11, LOW);
    digitalWrite(motor_12, LOW);
    delay(100);
  }
}

//control direction left 2 right motor two

int  controlMotor_two_L2R() {
  Serial.println("motor two L2R");
  //on 10 second
  digitalWrite(motor_21, HIGH);
  digitalWrite(motor_22, LOW);
  delay(10000);
  //off life time
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
}

//control direction right 2 left motor two

int  controlMotor_two_R2L() {
  Serial.println("motor two R2L");
  //on 10 second
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, HIGH);
  delay(10000);
  //off life time
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
}

//control up down using motor threee
int controlMotor_three() {
  step_count++;
  Serial.println("motor three");
  digitalWrite(motor_31, HIGH);
  digitalWrite(motor_32, LOW);
  //  delay(1000);
  digitalWrite(motor_31, LOW);
  digitalWrite(motor_32, LOW);
}

//switch on for spray color

int solinoid_valve() {
  if (distance >= 7 && distance <= 8) {
    digitalWrite(solinoid_v, HIGH);
    Serial.println("Bulb high");
    delay(100);
  }
}


//stop machine  after work done

Stop()
{
  digitalWrite(solinoid_v, LOW);
  digitalWrite(motor_11, LOW);
  digitalWrite(motor_12, LOW);
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
  int i;
  for (i = 0; i < step_count; i++);
  digitalWrite(motor_31, LOW);
  digitalWrite(motor_32, HIGH);
  delay(100);
}
digitalWrite(motor_31, LOW);
digitalWrite(motor_32, LOW);
