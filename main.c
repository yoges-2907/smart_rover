#include <ESP32Servo.h>

#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 8
#define IN3 9
#define IN4 10

#define TRIG 3
#define ECHO 4

Servo radarServo;

long distance();

void setup()
{
    Serial.begin(115200);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    radarServo.attach(2);

    analogWrite(ENA, 180);
    analogWrite(ENB, 180);
}

void loop()
{
    long d = distance();

    Serial.println(d);

    if (d > 25)
    {
        forward();
    }
    else
    {
        stopMotor();

        delay(300);

        backward();

        delay(400);

        stopMotor();

        radarServo.write(20);

        delay(500);

        long left = distance();

        radarServo.write(160);

        delay(500);

        long right = distance();

        radarServo.write(90);

        if (left > right)
        {
            turnLeft();
        }
        else
        {
            turnRight();
        }

        delay(500);

        stopMotor();
    }
}

long distance()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);

    return duration * 0.034 / 2;
}

void forward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void backward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void turnLeft()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void turnRight()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotor()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
