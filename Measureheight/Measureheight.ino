#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


const int trigPin = 9;
const int echoPin = 10;
const int startButton = 2;
const int buzzer = 3;

long duration;
int distance;
int sensorHeight = 200;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(startButton, INPUT);
  pinMode(buzzer, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Programmer Muemai");
  display.display();

  Serial.begin(9600);
}
void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = sensorHeight-(duration * 0.034 / 2);



  if (digitalRead(startButton) == 1) {
    waitMessages();
    delay(2000);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    showDistance();

  }
}

void waitMessages() {
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Wait...");
  display.display();
}

void showDistance() {
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  display.print(distance);
  display.setTextSize(3);
  display.setCursor(70, 8);
  display.println(" cm");
  display.display();
}
