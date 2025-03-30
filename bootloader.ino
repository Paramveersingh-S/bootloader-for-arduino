#include <avr/boot.h>  
#include <avr/wdt.h>  

#define APP_START_ADDR 0x7000  // Application starts at 28KB (adjust per board)  

// Compute checksum of application code  
uint16_t compute_checksum() {  
  uint16_t sum = 0;  
  for (uint16_t addr = APP_START_ADDR; addr < APP_START_ADDR + 1024; addr += 2) {  
    sum += pgm_read_word(addr);  
  }  
  return sum;  
}  

// Jump to application  
void jump_to_app() {  
  void (*app_start)(void) = (void (*)(void))(APP_START_ADDR);  
  cli();  
  wdt_disable();  
  app_start();  
}  

void setup() {  
  Serial.begin(9600);  
  uint16_t stored_checksum = pgm_read_word(0x7FFC);  // Store checksum at last 4 bytes of flash  
  uint16_t calculated_checksum = compute_checksum();  

  if (stored_checksum == calculated_checksum) {  
    Serial.println("Checksum OK. Starting app...");  
    jump_to_app();  
  } else {  
    Serial.println("Checksum FAILED!");  
  }  
}  

void loop() {}  
