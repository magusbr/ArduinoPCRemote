#include <IRremote.h>
#include "HID-Project.h"
/*
play -10044
<< -27617
>> 16134
|<< 28354
>>| -9585
pause 32603
stop 4190
up -11203
down -9828
left 11843
right -10204
keycodes on ImprovedKeylayouts.h
 */

#define SONY_IR_PLAY        -10044
#define SONY_IR_PAUSE       32603
#define SONY_IR_STOP        4190
#define SONY_IR_PREV        -27617
#define SONY_IR_FAST_PREV   28354
#define SONY_IR_NEXT        16134
#define SONY_IR_FAST_NEXT   -9585
#define SONY_IR_UP          -11203
#define SONY_IR_DOWN        -9828
#define SONY_IR_LEFT        11843
#define SONY_IR_RIGHT       -10204
#define SONY_IR_OK          -22268

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;
int key_pressed;
int ok;
int ok_pause;



void setup()
{
  //Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Keyboard.begin();
}

void loop() {
  ok = 0;
  ok_pause = 0;

  if (irrecv.decode(&results)) {
    
    key_pressed = results.value;
    //Serial.print("pressed ");
    //Serial.print(" ");
    //Serial.println(key_pressed);

    ok = 1;
    switch(key_pressed) {
      case SONY_IR_PLAY:
        Consumer.write(MEDIA_PLAY_PAUSE);
        ok = 0;
        ok_pause = 1;
        break;
      case SONY_IR_PAUSE:
        Consumer.write(MEDIA_RECORD);
        ok = 0;
        ok_pause = 1;
        break;
      case SONY_IR_PREV:
        Consumer.write(MEDIA_VOLUME_UP);
        break;
      case SONY_IR_FAST_PREV:
        Consumer.write(MEDIA_VOLUME_DOWN);
        break;
      case SONY_IR_NEXT:
        Keyboard.write(KEY_LEFT_WINDOWS);
        break;
      case SONY_IR_FAST_NEXT:
        Keyboard.write(KEY_TAB);
        Keyboard.write(KEY_TAB);
        delay(50);
        Keyboard.write(KEY_DOWN_ARROW);
        Keyboard.write(KEY_DOWN_ARROW);
        Keyboard.write(KEY_DOWN_ARROW);
        Keyboard.write(KEY_DOWN_ARROW);
        break;
      case SONY_IR_UP:
        Keyboard.write(KEY_UP_ARROW);
        break;
      case SONY_IR_DOWN:
        Keyboard.write(KEY_DOWN_ARROW);
        break;
      case SONY_IR_LEFT:
        Keyboard.write(KEY_LEFT_ARROW);
        break;
      case SONY_IR_RIGHT:
        Keyboard.write(KEY_RIGHT_ARROW);
        break;
      case SONY_IR_OK:
        Keyboard.write(KEY_ENTER);
        break;
    }
	
    if (ok) delay(150);
    else if (ok_pause) delay(600);
    
    irrecv.resume(); // Receive the next value
  }
}
