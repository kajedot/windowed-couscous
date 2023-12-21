#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define WINDOW_PIN_OPEN 10
#define WINDOW_PIN_CLOSE 9

#define THERM_PIN 12

#define LCD_PIN_A 5
#define LCD_PIN_B 6
#define LCD_PIN_C 7
#define LCD_PIN_D 8
#define LCD_PIN_E 4
#define LCD_PIN_RS 3

#define SWITCH_PIN_FREQ A0
#define SWITCH_PIN_TEMP A1

#define BUTTON_PIN_INC A2
#define BUTTON_PIN_DEC A3

#define OPEN_CLOSE_WINDOW_TIME 5000
#define BEFORE_BUTTON_TIME 200

OneWire oneWire(THERM_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_A, LCD_PIN_B, LCD_PIN_C, LCD_PIN_D);

int tempBorder = 25;
int refreshMinutes = 5;
unsigned long lastCheckMs = 0;
int lastMode = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();

  sensors.begin();

  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensors.");

  if (!sensors.getAddress(thermometer, 0)) Serial.println("Unable to find thermometer");

  pinMode(SWITCH_PIN_FREQ, INPUT_PULLUP);
  pinMode(SWITCH_PIN_TEMP, INPUT_PULLUP);
  pinMode(BUTTON_PIN_INC, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DEC, INPUT_PULLUP);
}

void updateWindowStateBasingOnTemp(float temp) {
  lcd.clear();
  if (temp > tempBorder) {
    lcd.print("OTWIERANIE OKNA");
    windowChange(WINDOW_PIN_OPEN);
  }
  if (temp < tempBorder) {
    lcd.print("ZAMYKANIE OKNA");
    windowChange(WINDOW_PIN_CLOSE);
  }
  lcd.clear();
}

void windowChange(int windowPin) {
  pinMode(windowPin, OUTPUT);

  digitalWrite(windowPin, LOW);
  delay(OPEN_CLOSE_WINDOW_TIME);
  digitalWrite(windowPin, HIGH);

  pinMode(windowPin, INPUT);
}

float getTemp(DeviceAddress deviceAddress) {
  sensors.requestTemperatures();

  float temp = sensors.getTempC(deviceAddress);

  if (temp == DEVICE_DISCONNECTED_C) {
    lcd.print("BLAD ODCZYTU TEMPERATURY");
    delay(2000);
    return -1000;
  }
  return temp;
}

int getMode() {
  if (digitalRead(SWITCH_PIN_FREQ) == LOW) {
    return 1;
  }
  if (digitalRead(SWITCH_PIN_TEMP) == LOW) {
    return 3;
  }
  return 2;

}

int getIncOrDecValue() {
  delay(BEFORE_BUTTON_TIME);
  if (digitalRead(BUTTON_PIN_INC) == LOW) {
    return 1;
  }
  if (digitalRead(BUTTON_PIN_DEC) == LOW) {
    return -1;
  }
  return 0;
}

void loop() {
  int mode = getMode();
  if (lastMode != mode) {
    lcd.clear();
  }
  lastMode = mode;
  switch (mode) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("TRYB TEMP");
      lcd.setCursor(0, 1);
      lcd.print(String("OBECNA: ") + tempBorder + " C  ");
      tempBorder += getIncOrDecValue();
      if (tempBorder < 0) {
        tempBorder = 0;
      };
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("TRYB CZAS");
      lcd.setCursor(0, 1);
      lcd.print(String("OBECNY: ") + refreshMinutes + " MINUT ");
      refreshMinutes += getIncOrDecValue();
      if (refreshMinutes < 1) {
        refreshMinutes = 1;
      };
      break;
    default:
      lcd.setCursor(0, 0);
      lcd.print("TRYB PRACA");
      float currentTemp = getTemp(thermometer);
      unsigned long currentTimes = millis();
      lcd.setCursor(0, 1);
      lcd.print(String("TEMP: ") + currentTemp + " C  ");
      if ((currentTimes - lastCheckMs) > refreshMinutes * 60000 || currentTimes < lastCheckMs) {
        lastCheckMs = currentTimes;
        updateWindowStateBasingOnTemp(currentTemp);
      }
      break;
  }
}

