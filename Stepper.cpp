
#include "Stepper.hpp"

using LuckyLuke::avr;

Stepper::Stepper(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
: p1(pin1), p2(pin2), p3(pin3), p4(pin4) {
  position = 0;
  
  // To prevent unwanted peaks, define the output pins as LOW before set them as OUTPUT
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);

  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
}

void Stepper::step(const int8_t steps, const uint8_t speed) {
  // Move left (-) or right (+)
  if (steps == 0) return;
  if (steps < 0) {
    for (uint8_t i = 0; i < 0 - steps; i++) {
      if (position == 0) {
        position = STEPPER_NUM_STEPS;
      }
      to_position(--position);
      delay(speed);
    }
    return;
  }
  
  for (uint8_t i = 0; i < steps; i++) {
    to_position(++position)
    if (position == STEPPER_NUM_STEPS) {
      position = 0;
    }
    delay(speed);
  }
}

void Stepper::step(DIRECTION direction) {
  switch (direction) {
    case LEFT: step(-1, 0); break;
    case RIGHT: step(1, 0); break;
  }
}

void Stepper::to_position(const uint8_t pos) {
  // just to be sure :)
  uint8_t _pos = pos % STEPPER_NUM_STEPS;
  
  digitalWrite(pin1, positions[0][_pos][0] == 0 ? LOW : HIGH);
  digitalWrite(pin2, positions[0][_pos][1] == 0 ? LOW : HIGH);
  digitalWrite(pin3, positions[0][_pos][2] == 0 ? LOW : HIGH);
  digitalWrite(pin4, positions[0][_pos][3] == 0 ? LOW : HIGH);
}

void Stepper::shutdown() {
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);  
}
