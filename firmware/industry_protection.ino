#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

// Define pins
#define DHTPIN D4
#define DHTTYPE DHT22
#define GASPIN A0
#define FIREPIN D8
#define LIGHTPIN A1
#define BUZZER_PIN D6
#define RELAY_PIN D7
#define LCDADDRESS 0x27
#define LCDCOLS 16
#define LCDROWS 2

// WiFi credentials
#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"
#define BLYNK_AUTH "YourBlynkAuthToken"
#define EMERGENCY_CONTACT "123456789"

// Initialize sensors and display
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystalI2C lcd(LCDADDRESS, LCDCOLS, LCDROWS);

// Global variables
float temperature = 0;
float humidity = 0;
int gasLevel = 0;
int fireLevel = 0;
int lightLevel = 0;

// Setup function
void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IoT Protection");
  lcd.setCursor(0, 1);
  lcd.print("System Init...");
  
  // Initialize sensors
  dht.begin();
  
  // Initialize pins
  pinMode(GASPIN, INPUT);
  pinMode(FIREPIN, INPUT);
  pinMode(LIGHTPIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Turn off buzzer and relay initially
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH, WIFI_SSID, WIFI_PASSWORD);
  
  delay(2000);
  lcd.clear();
}

// Main loop
void loop() {
  Blynk.run();
  
  readSensors();
  displayOnLCD();
  updateBlynk();
  checkEmergencyConditions();
  
  delay(2000);
}

// Read all sensors
void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  gasLevel = analogRead(GASPIN);
  fireLevel = analogRead(FIREPIN);
  lightLevel = analogRead(LIGHTPIN);
}

// Display data on LCD
void displayOnLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C H:");
  lcd.print(humidity);
  
  lcd.setCursor(0, 1);
  lcd.print("Gas:");
  lcd.print(gasLevel);
  lcd.print(" Fire:");
  lcd.print(fireLevel);
}

// Update Blynk app
void updateBlynk() {
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, gasLevel);
  Blynk.virtualWrite(V3, fireLevel);
  Blynk.virtualWrite(V4, lightLevel);
}

// Check emergency conditions
void checkEmergencyConditions() {
  bool emergency = false;
  String emergencyMessage = "";
  
  if (temperature > 40) {
    emergency = true;
    emergencyMessage += "High Temperature! ";
  }
  
  if (gasLevel > 500) {
    emergency = true;
    emergencyMessage += "Gas Leak! ";
  }
  
  if (fireLevel > 500) {
    emergency = true;
    emergencyMessage += "Fire Detected! ";
  }
  
  if (lightLevel < 200) {
    emergency = true;
    emergencyMessage += "Low Light! ";
  }
  
  if (emergency) {
    activateEmergencyAlert(emergencyMessage);
  } else {
    deactivateEmergencyAlert();
  }
}

// Activate emergency alert
void activateEmergencyAlert(String message) {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RELAY_PIN, HIGH);
  
  Serial.print("EMERGENCY: ");
  Serial.println(message);
  
  Blynk.notify("Alert: " + message);
}

// Deactivate emergency alert
void deactivateEmergencyAlert() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

// Blynk virtual pin handlers
BLYNK_CONNECTED() {
  Serial.println("Blynk connected!");
}
