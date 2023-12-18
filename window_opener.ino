#define WINDOW_OPEN_RELAY 10
#define WINDOW_CLOSE_RELAY 9

#define SWITCH_TEMP_MODE A1
#define SWITCH_FREQ_MODE A0

#define BUTTON_INCREMENT A2
#define BUTTON_DECREMENT A3

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
  Serial.begin(9600);

  sensors.begin();

  lcd.begin(16,2);
  lcd.clear();

  pinMode(SWITCH_TEMP_MODE, INPUT_PULLUP);
  pinMode(SWITCH_FREQ_MODE, INPUT_PULLUP);
  pinMode(BUTTON_INCREMENT, INPUT_PULLUP);
  pinMode(BUTTON_DECREMENT, INPUT_PULLUP);

}

void window_open() {
  // pinMode workaround explanation: 
  // https://electronics.stackexchange.com/a/508672  
  pinMode(WINDOW_OPEN_RELAY, OUTPUT);
  Serial.println("HIGH");
  digitalWrite(WINDOW_OPEN_RELAY, HIGH);
  delay(5000);
  Serial.println("LOW");
  digitalWrite(WINDOW_OPEN_RELAY, LOW);
  delay(5000);
  pinMode(WINDOW_OPEN_RELAY, INPUT);
}

int16_t get_room_temp() {
  sensors.requestTemperatures();
  int16_t temp = sensors.getTempCByIndex(0);
  return temp;
}

void print_temp(){  
  int16_t temp = get_room_temp();
  Serial.print("T=");
  Serial.println(temp);
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("T=");
  lcd.print(temp);
}

void debug_mode(){
  print_temp();

  Serial.print("SET_TEMP=");
  Serial.println(digitalRead(SWITCH_TEMP_MODE));
  Serial.print("SET_FREQ=");
  Serial.println(digitalRead(SWITCH_FREQ_MODE));

  Serial.print("BN_I=");
  Serial.println(digitalRead(BUTTON_INCREMENT));
  Serial.print("BN_D=");
  Serial.println(digitalRead(BUTTON_DECREMENT));

  lcd.setCursor(0,1);
 
}

void loop() {
  debug_mode();
}

// TODO: check if relay remains state after power down
