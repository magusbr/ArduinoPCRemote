//#include <USBAPI.h>
#include <HID.h>
#include <Keyboard.h>
#include <IRremote.h>
/*
play -10044
<< -27617
>> 16134
|<< 28354
>>| -9585
pause 32603
stop 4190
 */
int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;
int key_pressed;
int ok;
int ok_pause;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  ok = 0;
  ok_pause = 0;

  if (irrecv.decode(&results)) {
    
    key_pressed = results.value;
    Serial.print("pressed ");
    Serial.print(" ");
    Serial.println(key_pressed);
	
	if (key_pressed == -10044) {
      Remote.pause();
      Remote.clear();
	  ok_pause = 1;
    }
  
    if (key_pressed == 16134) {
      Remote.increase();
      Remote.clear();
	  ok = 1;
    }
  
    if (key_pressed == -27617) {
      Remote.decrease();
      Remote.clear();
	  ok = 1;
    }
	
    if (ok) delay(300);
    else if (ok_pause) delay(800);
    
    irrecv.resume(); // Receive the next value
  }
}