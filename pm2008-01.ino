#include <pm2008_i2c.h>

PM2008_I2C pm2008_i2c;

void setup() {
  pm2008_i2c.begin();
  Serial.begin(9600);
  pm2008_i2c.command();
  delay(1000);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  uint8_t ret = pm2008_i2c.read();

  uint8_t pm1p0_grade = 0;
  uint8_t pm2p5_grade = 0;
  uint8_t pm10_grade = 0;
  uint8_t total_grade = 0;

  if (ret == 0) {
    // PM 1.0
    if (pm2008_i2c.pm1p0_grimm < 16) {
      pm1p0_grade = 1;
    } else if (pm2008_i2c.pm1p0_grimm < 35) {
      pm1p0_grade = 2;
    } else {
      pm1p0_grade = 3;
    }

    // PM 2.5
    if (pm2008_i2c.pm2p5_grimm < 16) {
      pm2p5_grade = 1;
    } else if (pm2008_i2c.pm2p5_grimm < 35) {
      pm2p5_grade = 2;
    } else {
      pm2p5_grade = 3;
    }

    // PM 10
    if (pm2008_i2c.pm10_grimm < 51) {
      pm10_grade = 1;
    } else if (pm2008_i2c.pm10_grimm < 101) {
      pm10_grade = 2;
    } else {
      pm10_grade = 3;
    }

    // Get worst grade
    total_grade = max(pm1p0_grade, pm2p5_grade);
    total_grade = max(total_grade, pm10_grade);

    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

    Serial.print("PM1.0: ");
    Serial.println(pm2008_i2c.pm1p0_grimm);
    Serial.print("PM2.5: ");
    Serial.println(pm2008_i2c.pm2p5_grimm);
    Serial.print("PM10: ");
    Serial.println(pm2008_i2c.pm10_grimm);

    switch (total_grade) {
      case 1: {
        Serial.println("Good!");
        digitalWrite(3, HIGH);
        break;
      }

      case 2: {
        Serial.println("Nomal!");
        digitalWrite(4, HIGH);
        break;
      }

      case 3: {
        Serial.println("Worst!!!");
        digitalWrite(5, HIGH);
        break;
      }

      default:
        break;
    }
  }
  
  delay(2000);

}
