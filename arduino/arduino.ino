#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM maths.
// #include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library. 

// Define pins for sensors and actuators
#define DHTPIN 2     // DHT11 data pin
#define DHTTYPE DHT11
#define HEARTBEAT_PIN A0
// #define BUZZER_PIN 8
#define FAN_PIN 10
#define FAN_PIN_1 11
#define cooling_led 12
#define alert_led 3
// const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
// int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
// int Threshold = 350;


// PulseSensorPlayground pulseSensor;

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

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int red = 0;
int green = 0;
int blue = 0;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;




void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // // Initialize the LCD
  // lcd.begin();
  lcd.init();
  lcd.backlight();

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
  pinMode(FAN_PIN_1, OUTPUT);
  pinMode(alert_led, OUTPUT);
  pinMode(cooling_led, OUTPUT);

  // // Print initial message to LCD
  // lcd.setCursor(0, 0);
  // lcd.print("Temp: Hum: BPM:");

  // pulseSensor.analogInput(PulseWire);  
  // pulseSensor.setThreshold(Threshold);  
  // pulseSensor.begin();
  // Double-check the "pulseSensor" object was created and "began" seeing a signal.



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
  // int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now.


  // Get color sensor values
  getColor();

  // Display values on LCD
  lcd.setCursor(0,0);
  // lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print(" H:");
  lcd.print(hum);
  lcd.setCursor(0, 1);
  lcd.print(" BPM:");
  lcd.print(heart_beat_value);




  Serial.print("heartbeat: ");
  Serial.println(heart_beat_value);
  // Send data to ESP32
  Serial.print("temp: ");
  Serial.println(temp);
  // Serial.print(",");
  Serial.print("hum: ");
  Serial.println(hum);
  // if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
  // Serial.print("BPM: ");                        // Print phrase "BPM: "
  // Serial.println(myBPM);                        // Print the value inside of myBPM.
  // }
  // // Serial.print(",");
  
  // Serial.print(",");
  // Serial.print(red);
  // Serial.print(",");
  // Serial.print(green);
  // Serial.print(",");
  // Serial.println(blue);

  // Check if temperature is above threshold
  if(temp > 37) {
    digitalWrite(FAN_PIN, HIGH); // Turn on fan
    digitalWrite(FAN_PIN_1, HIGH);
    digitalWrite(alert_led, LOW);
    digitalWrite(cooling_led, HIGH);
  //   digitalWrite(BUZZER_PIN, HIGH); // Sound buzzer
  } else if(temp < 35) {
    digitalWrite(FAN_PIN, LOW); // Turn off fan
    digitalWrite(FAN_PIN_1, LOW);
    digitalWrite(alert_led, HIGH);
    digitalWrite(cooling_led, LOW);
  //   digitalWrite(BUZZER_PIN, LOW); // Silence buzzer
  }
  else{
    digitalWrite(FAN_PIN, LOW); // Turn on fan
    digitalWrite(FAN_PIN_1, LOW);
    digitalWrite(alert_led, LOW);
  }

  // Check if yellow color is detected
  if (isYellow()) {
    Serial.print("jaundice: ");
    Serial.println("Yellow Color Detected! Raising flag.");
    lcd.clear();
    lcd.print("Jaundice detected");
    delay(1000);
  }

  delay(500); // Update every 2 seconds
}

// Function to get color values
void getColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(SENSOROUT, LOW);

  

  redColor = map(redFrequency, 58, 335, 255,0);
  // Serial.print("R = ");
  // Serial.print(redColor);

  // Read Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(SENSOROUT, LOW);

  greenColor = map(greenFrequency, 144, 405, 255, 0);
  // Serial.print(" G = ");
  // Serial.print(greenColor);


  // Read Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(SENSOROUT, LOW);

  

  blueColor = map(blueFrequency, 166, 356, 255, 0);
  // Serial.print(" B = ");
  // Serial.println(blueColor);
}

// Function to check if detected color is yellow
bool isYellow() {
  if (26 < redFrequency && redFrequency < 42){
    if(26 < greenFrequency &&greenFrequency < 40){

    if(26< blueFrequency && blueFrequency < 75) {
    return true;
  }}}
  // if ( redFrequency < 42){
  //   if(greenFrequency < 40){

  //   if( blueFrequency < 68) {
  //   return true;
  // }}}
  // if (210 < redColor && redColor < 239){
  //   if(105 < greenColor &&greenColor < 248){

  //   if(88< blueColor && blueColor < 316) {
  //   return true;
  // }}}
  // if (redColor > greenColor && redColor > blueColor && greenColor > redColor && greenColor > blueColor){
  //   return true;
  // }
  else{
    return false;
  }

}