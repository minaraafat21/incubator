#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins for sensors and actuators
#define DHTPIN 2     // DHT11 data pin
#define DHTTYPE DHT11
#define HEARTBEAT_PIN A0
// #define BUZZER_PIN 8
#define FAN_PIN 9
#define S2 5
#define S3 4
#define SENSOROUT 8
#define S0 7
#define S1 6

double alpha = 0.75;
int period = 200;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// // Initialize LCD
// LiquidCrystal_I2C lcd(0x27, 16, 2); 

int red = 0;
int green = 0;
int blue = 0;

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // // Initialize the LCD
  // lcd.begin();
  // lcd.backlight();

  // Set pins for color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOROUT, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  

  // Set pin modes for fan and buzzer
  // pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  // // Print initial message to LCD
  // lcd.setCursor(0, 0);
  // lcd.print("Temp: Hum: BPM:");
}

void loop() {

  

  // for heart beat
  static double oldValue = 0;
  static double oldChange = 0;

  // Read temperature and humidity from DHT sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Read heart beat sensor value
  int raw_heartbeat = analogRead(HEARTBEAT_PIN);
  double heart_beat_value = (alpha * oldValue + (1 - alpha) * raw_heartbeat)/3;
  oldValue = heart_beat_value;

  // Get color sensor values
  getColor();

  // Display values on LCD
  // lcd.setCursor(0, 1);
  // lcd.print("T:");
  // lcd.print(temp);
  // lcd.print(" H:");
  // lcd.print(hum);
  // lcd.print(" BPM:");
  // lcd.print(heartbeat);

  // Send data to ESP32
  Serial.print("temp: ");
  Serial.println(temp);
  // // Serial.print(",");
  Serial.print("hum: ");
  Serial.println(hum);
  // // Serial.print(",");
  Serial.print("heartbeat: ");
  Serial.println(heart_beat_value);
  // Serial.print(",");
  // Serial.print(red);
  // Serial.print(",");
  // Serial.print(green);
  // Serial.print(",");
  // Serial.println(blue);

  // Check if temperature is above threshold
  // if(temp > 32) {
  //   digitalWrite(FAN_PIN, HIGH); // Turn on fan
  //   digitalWrite(BUZZER_PIN, HIGH); // Sound buzzer
  // } else {
  //   digitalWrite(FAN_PIN, LOW); // Turn off fan
  //   digitalWrite(BUZZER_PIN, LOW); // Silence buzzer
  // }

  // Check if yellow color is detected
  if (isYellow()) {
    Serial.print("jaundice: ");
    Serial.println("Yellow Color Detected! Raising flag.");
  }

  delay(1000); // Update every 2 seconds
}

// Function to get color values
void getColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(SENSOROUT, LOW);

  // Read Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(SENSOROUT, LOW);

  // Read Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(SENSOROUT, LOW);
}

// Function to check if detected color is yellow
bool isYellow() {
  if (30 < redFrequency && redFrequency < 130){
    if(40 < greenFrequency &&greenFrequency < 175){

    if(65< blueFrequency && blueFrequency < 180) {
    return true;
  }}}
  else{
    return false;
  }

}