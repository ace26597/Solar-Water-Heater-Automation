#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <SoftPWM.h>


const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char numberKeys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(numberKeys), rowPins, colPins, ROWS, COLS);

int relay = 12;
int hh = 18;
int mm = 07;
int ss = 00;
int h1, h2, m1, m2, m3, m4, h3, h4, hr, mn, h11 , h22, m11, m22 , mmm, hhh;
int i, a = 0;
int alarm = 13;
bool summermode, morn, summe;
AlarmId id;
RTC_Millis rtc;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  pinMode(12, INPUT);
  pinMode(A5, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(alarm, OUTPUT);
  Serial.begin(57600);
  lcd.begin(16, 2);
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  DateTime now = rtc.now();
  setTime(now.hour(), now.minute(), now.second(), now.month(), now.day(), now.year());
  // create the alarms, to trigger at specific times
  //Alarm.alarmRepeat(hh, mm, ss, MorningAlarm);
  //digitalWrite(alarm, LOW);
  keypad.addEventListener(keypadEvent);
  keypad.setDebounceTime(10);
  keypad.setHoldTime(2000);
  Alarm.timerOnce(10, OnceOnly);            // called once after 10 seconds
}

void OnceOnly() {
  Serial.println("SM LOW");
  digitalWrite(alarm, LOW);
  Alarm.free(id);
  id = dtINVALID_ALARM_ID;
}

void summer()
{
  lcd.clear();
  lcd.print("Summeralarm");
  lcd.setCursor(0, 1);
  lcd.print("Enter Hour-");
  char key1 = keypad.getKey();
  while (key1 != '*') {
    char key2 = keypad.getKey();
    if (key2)
    {
      lcd.print(key2);
      h11 = key2;
      while (key2 != '*') {
        char key3 = keypad.getKey();
        if (key3)
        {
          lcd.print(key3);
          h22 = key3;
          key1 = '*';
          key2 = '*';
          lcd.clear();
        }
      }
    }
  }
  h11 = h11 - 48;
  h22 = h22 - 48;
  hhh = (h11 * 10) + h22;
  lcd.setCursor(0, 0);
  lcd.print("Hour = ");
  lcd.print(hhh);
  lcd.setCursor(0, 1);
  lcd.print("Enter Min-");
  char key4 = keypad.getKey();
  while (key4 != '*') {
    char key5 = keypad.getKey();
    if (key5)
    {
      lcd.print(key5);
      m11 = key5;
      while (key5 != '*') {
        char key6 = keypad.getKey();
        if (key6)
        {
          lcd.print(key6);
          m22 = key6;
          key4 = '*';
          key5 = '*';
          lcd.clear();
        }
      }
    }
  }
  m11 = m11 - 48;
  m22 = m22 - 48;
  mmm = (m11 * 10) + m22;
  Alarm.alarmRepeat(hhh, mmm, 00, summeralarm);
}
void normalalarm()
{
  Serial.println("#");
  lcd.clear();
  lcd.print("morning alarm");
  lcd.setCursor(0, 1);
  lcd.print("Enter Hour-");
  char key1 = keypad.getKey();
  while (key1 != '*') {
    char key2 = keypad.getKey();
    if (key2)
    {
      lcd.print(key2);
      h1 = key2;
      while (key2 != '*') {
        char key3 = keypad.getKey();
        if (key3)
        {
          lcd.print(key3);
          h2 = key3;
          key1 = '*';
          key2 = '*';
          lcd.clear();
        }
      }
    }
  }
  h1 = h1 - 48;
  h2 = h2 - 48;
  hh = (h1 * 10) + h2;
  lcd.setCursor(0, 0);
  lcd.print("Hour = ");
  lcd.print(hh);
  lcd.setCursor(0, 1);
  lcd.print("Enter Min-");
  char key4 = keypad.getKey();
  while (key4 != '*') {
    char key5 = keypad.getKey();
    if (key5)
    {
      lcd.print(key5);
      m1 = key5;
      while (key5 != '*') {
        char key6 = keypad.getKey();
        if (key6)
        {
          lcd.print(key6);
          m2 = key6;
          key4 = '*';
          key5 = '*';
          lcd.clear();
        }
      }
    }
  }
  m1 = m1 - 48;
  m2 = m2 - 48;
  mm = (m1 * 10) + m2;
  Alarm.alarmRepeat(hh, mm, ss, MorningAlarm);
}

void clk()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("change Time");
  lcd.setCursor(0, 1);
  lcd.print("Enter Hour-");
  char key11 = keypad.getKey();
  while (key11 != '*') {
    char key12 = keypad.getKey();
    if (key12)
    {
      lcd.print(key12);
      h3 = key12;
      while (key12 != '*') {
        char key13 = keypad.getKey();
        if (key13)
        {
          lcd.print(key13);
          h4 = key13;
          key11 = '*';
          key12 = '*';
          lcd.clear();
        }
      }
    }
  }
  h3 = h3 - 48;
  h4 = h4 - 48;
  hr = (h3 * 10) + h4;
  lcd.setCursor(0, 0);
  lcd.print("Hour = ");
  lcd.print(hr);
  lcd.setCursor(0, 1);
  lcd.print("Enter Min-");
  char key14 = keypad.getKey();
  while (key14 != '*') {
    char key15 = keypad.getKey();
    if (key15)
    {
      lcd.print(key15);
      m3 = key15;
      while (key15 != '*') {
        char key16 = keypad.getKey();
        if (key16)
        {
          lcd.print(key16);
          m4 = key16;
          key14 = '*';
          key15 = '*';
          lcd.clear();
        }
      }
    }
  }
  m3 = m3 - 48;
  m4 = m4 - 48;
  mn = (m3 * 10) + m4;
  Alarm.alarmRepeat(hh, mm, ss, MorningAlarm);
  Alarm.alarmRepeat(hhh, mmm, 00, summeralarm);
  setTime(hr, mn, 00, 26, 5, 2016);
}

// functions to be called when an alarm triggers:
void MorningAlarm() {
  Serial.println("Alarm: ");

  digitalWrite(alarm, HIGH);
  morn = 1;
}

void summeralarm()
{
  Serial.println("Summer");
  digitalWrite(alarm, HIGH);
  summe = 1;
   if (digitalRead(relay) == LOW && summe == HIGH  )
  {
  Alarm.timerOnce(10, OnceOnly);
  }
}

void loop() {
  lcd.clear();
  digitalClockDisplay();
  lcd.setCursor(0, 1);
  lcd.print("Alarm:");
  lcd.print(hh);
  lcd.print(":");
  lcd.print(mm);
  lcd.print(":");
  lcd.print(ss);


  char key = keypad.getKey();
  if (key)
  {
    Serial.println(key);
  }

  if (digitalRead(relay) == LOW && morn == 1 )
  {
    Serial.println("LOW");
    digitalWrite(alarm, LOW);
    morn = 0;
  }
  else if (digitalRead(relay) == LOW && summe == 1)
  {
   summe = 0;
   Alarm.timerOnce(10, OnceOnly);
   }
  Alarm.delay(1000); // wait one second between clock display

}

void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
    case PRESSED:
      if (key == '#') {
        lcd.clear();
        digitalClockDisplay();
        lcd.setCursor(0, 1);
        lcd.print("S+ Alarm:");
        lcd.print(hhh);
        lcd.print(":");
        lcd.print(mmm);
        lcd.print(":");
        lcd.print(00);
      }
      break;

    case RELEASED:
      if (key == '1') {
        Serial.println("released");
      }
      break;

    case HOLD:
      switch (key)
      {
        case '*' :

          {
            clk();
          }
          break;

        case '#' :
          {
            normalalarm();
          }
          break;

        case '8':
          {
            summer();
          }
          break;

        case '0' :
          {
            if (summermode == 0)
            {
              Serial.println("Summer Mode ON");
              summermode = 1;
              lcd.clear();
              lcd.print("Summer Mode ON");
              delay(2000);
              loop();
            }
            else if (summermode == 1 && summe == 0 )
            {
              lcd.clear();
              lcd.print("Summer Mode OFF");
              delay(2000);
              Serial.println("Summer Mode OFF");
              summermode = 0;
              loop();
            }
          }
      }
  }
}

void digitalClockDisplay()
{
  // digital clock display of the time
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  //Serial.print(hour());
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits)
{
  Serial.print(":");
  Serial.print(digits);
  lcd.print(":");
  if (digits < 10)
    //Serial.print('0');
    lcd.print('0');
  //Serial.print(digits);
  lcd.print(digits);
}

