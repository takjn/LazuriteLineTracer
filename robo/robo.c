#include "robo_ide.h"		// Additional Header

#define PHOTOSENSOR1 A1
#define PHOTOSENSOR2 A3
#define ALPHA 900

#define SERVO_A 9
#define SERVO_B 10
#define SERVO_STEP 5

#define MOTOR_AIN1 2
#define MOTOR_AIN2 3
#define MOTOR_PWMA 4
#define MOTOR_SPEED_A 128

#define MOTOR_BIN1 5
#define MOTOR_BIN2 6
#define MOTOR_PWMB 7
#define MOTOR_SPEED_B 128

long servo_A;
long servo_B;
int servo_A_step;
int servo_B_step;

void setup() {
	byte rc;
	servo_A = 1300;
	servo_B = 1500;
	servo_A_step = +(SERVO_STEP);
	servo_B_step = -(SERVO_STEP);

	// initializing motor
	pinMode(MOTOR_AIN1, OUTPUT);
	pinMode(MOTOR_AIN2, OUTPUT);
	pinMode(MOTOR_PWMA, OUTPUT);
	
	pinMode(MOTOR_BIN1, OUTPUT);
	pinMode(MOTOR_BIN2, OUTPUT);
	pinMode(MOTOR_PWMB, OUTPUT);

//	pinMode(PHOTOSENSOR1, INPUT);
//	pinMode(PHOTOSENSOR2, INPUT);

	Serial.begin(115200);
	
	hsv.init(2, 24000);
	hsv.attach(0, SERVO_A);
	hsv.attach(1, SERVO_B);
	hsv.write(0, servo_A);
	hsv.write(1, servo_B);
	hsv.start();

	
}

void loop() {
	int valA;
	int valB;

	servo_A += servo_A_step;
	servo_B += servo_B_step;
	if (servo_A > 1700 || servo_A < 1300) {
		servo_A_step = servo_A_step * -1;		
	}
	if (servo_B > 1700 || servo_B < 1300) {
		servo_B_step = servo_B_step * -1;		
	}

	valA = analogRead(PHOTOSENSOR1);
	valB = analogRead(PHOTOSENSOR2);
	
	Serial.print_long((long)valA, DEC);
	Serial.print(",");
	Serial.print_long((long)valB, DEC);
	Serial.println("");
  
	hsv.write(0, servo_A);
	hsv.write(1, servo_B);

	if (valA > ALPHA && valB > ALPHA){
		//左、右ともに白なら停止
		digitalWrite(MOTOR_PWMA, LOW);
		digitalWrite(MOTOR_PWMB, LOW);
	}else if(valA <= ALPHA && valB > ALPHA){
		digitalWrite(MOTOR_AIN1, HIGH);
		digitalWrite(MOTOR_AIN2, LOW);
		digitalWrite(MOTOR_BIN1, LOW);
		digitalWrite(MOTOR_BIN2, HIGH);
		digitalWrite(MOTOR_PWMA, HIGH);
		digitalWrite(MOTOR_PWMB, HIGH);
	}else if(valA > ALPHA && valB <= ALPHA){
		digitalWrite(MOTOR_AIN1, LOW);
		digitalWrite(MOTOR_AIN2, HIGH);
		digitalWrite(MOTOR_BIN1, HIGH);
		digitalWrite(MOTOR_BIN2, LOW);
		digitalWrite(MOTOR_PWMA, HIGH);
		digitalWrite(MOTOR_PWMB, HIGH);
	}else{
		//左、右ともに黒なら直進
		digitalWrite(MOTOR_AIN2, HIGH);
		digitalWrite(MOTOR_AIN1, LOW);
		digitalWrite(MOTOR_BIN2, HIGH);
		digitalWrite(MOTOR_BIN1, LOW);
		digitalWrite(MOTOR_PWMA, HIGH);
		digitalWrite(MOTOR_PWMB, HIGH);
	}
	delay(10);

}
