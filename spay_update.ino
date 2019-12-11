const int trig = 3;
const int echo = 4;
const int motor_11 = 8; //motot 1
const int motor_12 = 9;
int ENA = 10;
const int motor_21 = 5;//motor 2
const int motor_22 = 6;
int ENB = 7;
const int motor_31 = 11;//motor3
const int motor_32 = 13;
int ENC = 12;

int flag = 0;
const int solinoid_v = 2;//spray machine
const int buzzer = 1;//sound
const int led=0;//light
int step_count = 0;//step to move top to bottom
long duration=0;
int distance=0;
const int Speed = 210;//analog control
int controlMotor_one();     // control distance from object
int controlMotor_two_L2R(); // motor two left to right direction
int controlMotor_two_R2L(); // motor two right to left direction
int controlMotor_three();   // motor three control up and down
int solinoid_valve_open();       // on spray for  color
int Stop();                 // stop all programm
int calculateDistance(const int, const int); //calculate distance using sonar

bool check_solinoid_start = false;

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
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENC, OUTPUT);

  pinMode(solinoid_v, OUTPUT);//control  spray
  pinMode(buzzer, OUTPUT);//for stop signal using sound
  pinMode(led,OUTPUT);//for stop signal using light
  // put your setup code here, to run once:
}


void loop() {
  // measure distance using sonar
  distance = calculateDistance(trig, echo);
  //  for (;;) {
  //    Serial.println(calculateDistance(trig, echo));
  //  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
  
  if(distance <10 && distance >12 && check_solinoid_start == false)
  {
	  digitalWrite(led,HIGH);
  }
  // controlMotor_one();
  if(distance >=10 && distance <=12){
	  digitalWrite(led,LOW);
	  solinoid_valve_open();
  }
  
  if (check_solinoid_start) {
    controlMotor_two_L2R();
    controlMotor_three();
    controlMotor_two_R2L();
    controlMotor_three();
  }
  if (step_count == 10) {
    Stop();
    tone(buzzer, 1000, 500); // buzzer sound
    delay(1000000);
  }
  if(check_solinoid_start){
	Serial.print("count : ");
	Serial.println(step_count);
  }
}

// control motor one  for face distance
// control z distance
int controlMotor_one() {

   // Serial.println("motor one");
  if (distance > 12) {
    digitalWrite(motor_11, HIGH);
    digitalWrite(motor_12, LOW);
      analogWrite(ENA, Speed);
	// digitalWrite(led,HIGH);
    // solinoid_valve_close();
    //    delay(100);
  } else if (distance < 10) {
    digitalWrite(motor_11, LOW);
    digitalWrite(motor_12, HIGH);
    analogWrite(ENA, Speed);
    // delay(100);
    // digitalWrite(led,HIGH);
	// solinoid_valve_close();
	
  } else {
    // solinoid_valve_open();
    digitalWrite(motor_11, LOW);
    digitalWrite(motor_12, LOW);
      // analogWrite(ENA, Speed);
    // delay(100);
  }
}

// control direction left 2 right motor two

int controlMotor_two_L2R() {
  Serial.println("motor two running L2R");
  // on 10 second
  const auto finalTime = millis() + 10 * 1000;
  while (millis() < finalTime) {
	  //start motor 2
    digitalWrite(motor_21, HIGH);
    digitalWrite(motor_22, LOW);
    analogWrite(ENB, Speed); // control rpm
    distance = calculateDistance(trig, echo);
    controlMotor_one();
    /* delay(); */
  }
  /* delay(10000); */
  //off motor 1
  
  // off life time 
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
}

// control direction right 2 left motor two

int controlMotor_two_R2L() {
  Serial.println("motor two running R2L");
  // on 10 second

  const auto finalTime = millis() + 10 * 1000;
  while (millis() < finalTime) {
    digitalWrite(motor_21, LOW);
    digitalWrite(motor_22, HIGH);
    analogWrite(ENB, Speed);
    distance = calculateDistance(trig, echo);
    controlMotor_one();
  }
  /* delay(10000); */
  // off life time
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
}

// control up down using motor threee
int controlMotor_three() {
  
  //off motor 1
  digitalWrite(motor_11, LOW);
  digitalWrite(motor_12, LOW);
  
  //for motor 3
  step_count = step_count + 1; // increse line paint
  Serial.println("motor three running");
  digitalWrite(motor_31, HIGH);
  digitalWrite(motor_32, LOW);
  analogWrite(ENC, Speed); // control rpm
  delay(5000);
  digitalWrite(motor_31, LOW);
  digitalWrite(motor_32, LOW);
  
}

// switch on for spray color

int solinoid_valve_open() {
	check_solinoid_start = true;
  // flag = 1;
  digitalWrite(solinoid_v, HIGH);
  Serial.println("solinoid running");
  delay(1000);
}

int solinoid_valve_close() {
  flag = 0;
  check_solinoid_start = false;
  digitalWrite(solinoid_v, LOW);
  //  Serial.println("Bulb high");/
  delay(100);
}

//calculation distance
int calculateDistance(const int trigPin, const int echoPin) {
  // long duration = 0;
  // int distance = 0;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  return distance;
}

// stop machine  after work done

int Stop() {
  digitalWrite(solinoid_v, LOW);
  digitalWrite(motor_11, LOW);
  digitalWrite(motor_12, LOW);
  digitalWrite(motor_21, LOW);
  digitalWrite(motor_22, LOW);
  int i;
  for (i = 0; i < step_count-1; i++) {
    digitalWrite(motor_31, LOW);
    digitalWrite(motor_32, HIGH);
	tone(buzzer, 1000, 500); // buzzer sound
    delay(1000);
  }
  digitalWrite(motor_31, LOW);
  digitalWrite(motor_32, LOW);
}
