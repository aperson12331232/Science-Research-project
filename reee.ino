#include <pt.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define dirPin 5
#define stepPin 2
#define enablePin 8  // ******** name the enable pin

#define stepsPerRevolution 1
//#define LEDPIN 13
Adafruit_MPU6050 mpu;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);  // ******** set the enable pinMode
  digitalWrite(enablePin, LOW); // ******** enable the motors
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  // put your setup code here, to run once:

}
int count = 0;
int oldy = 0;

void loop() {
  // put your main code here, to run repeatedly:
  /* Get new sensor events with the readings */
   sensors_event_t a, g, temp;
   mpu.getEvent(&a, &g, &temp);

  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");
   if (a.acceleration.y > 0.2)
   {
      digitalWrite(dirPin, HIGH);
      // Spin the stepper motor 5 revolutions fast:
      for (int i = 0; i < 10; i++)
      {
          // These four lines result in 1 step:
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500); 
      }

      //count = count + 1;
   }
   if (a.acceleration.y < -0.2)
   {
      digitalWrite(dirPin, LOW);
      // Spin the stepper motor 5 revolutions fast:
      for (int i = 0; i < 10; i++)
      {
          // These four lines result in 1 step:
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);   
      }
   }
   // Insert motor control here
   // Insert motor control here
   //digitalWrite(dirPin, HIGH);
  // delay(1);
}
