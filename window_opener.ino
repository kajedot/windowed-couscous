#define WINDOW_MOTOR 2
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

  pinMode(WINDOW_MOTOR, OUTPUT);

  lcd.begin(16,2);
  lcd.clear();
}

void click_switch(int sw_delay) {
  digitalWrite(WINDOW_MOTOR, HIGH);
  delay(sw_delay);
  digitalWrite(WINDOW_MOTOR, LOW);
  delay(sw_delay);
}

int16_t get_room_temp() {
  sensors.requestTemperatures();
  int16_t temp = sensors.getTempCByIndex(0);
  return temp;
}

void loop() {
  int16_t temp = get_room_temp();
  Serial.println(temp);
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print(temp);
}
