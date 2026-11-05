// Parker Wilson - documentation reference receiver
// Home and limits must match the Python controller.
// Pin 9 = pan, pin 10 = tilt. Baud = 115200.
#include <Servo.h>
#include <stdlib.h>

Servo pan;
Servo tilt;
const int MIN_ANGLE = 30;
const int MAX_ANGLE = 150;
const int HOME_PAN = 40;
const int HOME_TILT = 40;

char line[24];
byte used = 0;
bool overflow = false;

void applyCommand(char* text) {
  // Accept exactly integer,integer. Reject trailing text.
  if (!(*text == '-' || (*text >= '0' && *text <= '9'))) return;
  char* end;
  long p = strtol(text, &end, 10);
  if (*end != ',') return;
  char* second = end + 1;
  if (!(*second == '-' || (*second >= '0' && *second <= '9'))) return;
  long t = strtol(second, &end, 10);
  if (*end != '\0') return;
  if (p < MIN_ANGLE || p > MAX_ANGLE ||
      t < MIN_ANGLE || t > MAX_ANGLE) return;
  pan.write((int)p);
  tilt.write((int)t);
}

void setup() {
  Serial.begin(115200);
  pan.write(HOME_PAN);
  tilt.write(HOME_TILT);
  pan.attach(9);
  tilt.attach(10);
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n') {
      if (!overflow) {
        // Serial Monitor may send CRLF.
        if (used > 0 && line[used - 1] == '\r') --used;
        line[used] = '\0';
        applyCommand(line);
      }
      used = 0;
      overflow = false;
    } else if (!overflow) {
      if (used < sizeof(line) - 1) line[used++] = c;
      else overflow = true;
    }
  }
}
