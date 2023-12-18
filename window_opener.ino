#define WINDOW_OPEN_PIN 10
#define WINDOW_CLOSE_PIN 9
#define THERMOMETER 12

#define LCD_RS 3
#define LCD_EN 4
#define LCD_DB4 5
#define LCD_DB5 6
#define LCD_DB6 7
#define LCD_DB7 8

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

OneWire oneWire(THERMOMETER);
DallasTemperature sensors(&oneWire);

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup() {
  sensors.begin();
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
}

void window_open() {
  // pinMode workaround explanation: 
  // https://electronics.stackexchange.com/a/508672
  pinMode(WINDOW_OPEN_PIN, OUTPUT);
  Serial.println("HIGH");
  digitalWrite(WINDOW_OPEN_PIN, HIGH);
  delay(5000);
  Serial.println("LOW");
  digitalWrite(WINDOW_OPEN_PIN, LOW);
  delay(5000);
  pinMode(WINDOW_OPEN_PIN, INPUT);
}

int16_t get_room_temp() {
  sensors.requestTemperatures();
  int16_t temp = sensors.getTempCByIndex(0);
  return temp;
}

void print_temp(){  
  int16_t temp = get_room_temp();
  Serial.println(temp);
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print(temp);
}

void loop() {
  window_open();
}

// TODO: check if relay remains state after power down
