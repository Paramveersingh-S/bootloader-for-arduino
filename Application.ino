#include <avr/sleep.h>  

// Application vector table (for ARM boards)  
__attribute__((section(".app_vector_table")))  
const uint32_t vectors[] = {  
  0x20008000,          // Initial stack pointer (ARM boards)  
  (uint32_t)main       // Reset handler  
};  

void setup() {  
  pinMode(LED_BUILTIN, OUTPUT);  
}  

void loop() {  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(1000);  
  digitalWrite(LED_BUILTIN, LOW);  
  delay(1000);  
}  
