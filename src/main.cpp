#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Information taken from https://wolles-elektronikkiste.de/en/timer-and-pwm-part-2-16-bit-timer1
  // Clear OC1A on Compare Match / Set OC1A at Bottom; Wave Form Generator: Fast PWM 14, Top = ICR1
  // COM1A1=true: Clear OC1A/OC1B on Compare Match (set output to low level)
  TCCR1A = (1<<COM1A1) + (1<<WGM11); 
  // WGM11=true; WGM13=true; WGM12=true: Mode 14, Fast PWM ICR1 is TOP
  TCCR1B = (1<<WGM13) + (1<<WGM12) + (1<<CS11); // prescaler = 8; 
  // top = system_clock / (prescaler * f_desired) - 1 = 16MHz / (8 * 500Hz) = 3999
  ICR1 = 3999;
  // Duty cycle 50% (4000 - 2000 = 2000)
  OCR1A = 1999;
  // Set OC1A pin (PB1 in ATmega328P / Arduino Nano) as an output
  DDRB |= (1<<PB1);

  while (true) {
  }
}
