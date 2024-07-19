
#include <msp430.h>
#include <i2c.h>

#define TMP102_ADDRESS 0x48

register int temperature;

void setup() {
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  ADC12CTL0 = ADC12ON + ADC12CSTARTADD0; // Turn on ADC12
  ADC12CTL1 = ADC12CSTARTADD0; // Select temperature sensor channel
  i2c_init(); // Initialize I2C
}

void loop() {
  __delay_cycles(1000); // Wait for 1ms
  temperature = i2c_read(TMP102_ADDRESS, 0x00); // Read temperature value from TMP102
  temperature = (temperature - 0x1A98) * (85 - 30) / (0x1E4F - 0x1A98) + 30; // Convert temperature value to Celsius
  __delay_cycles(1000); // Wait for 1ms
}

int main() {
  setup();
  while(1) {
    loop();
  }
}
