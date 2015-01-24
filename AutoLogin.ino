#define USB_SERIAL_PRIVATE_INCLUDE
#include "usb_keyboard.h"
#define KEY_SHIFT	0x02
const int led = LED_BUILTIN;
char keysLower[31] = "0000abcdefghijklmnopqrstuvwxyz";
char keysUpper[31] = "0000ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char nums[68] = "pppppppppppppppppppppppppppppp1234567890";

void setup(){
  pinMode(led, OUTPUT);
  delay(3000);
start();
   writeWord("MyAwesomePassword");
}
void loop(){}

void start()
{
     usb_keyboard_press(42,0);
     delay(1000);
        usb_keyboard_press(42,0);
      delay(1000);
         usb_keyboard_press(42,0);
      delay(540);
}



void writeWord(char sWord[])
{
  int i;
  char *p;
  p = sWord;
  for(i = 0;p[ i ];i++)
  {
    if(isNumber(p[ i ]))
      writeNumber(p[ i ]);
    else
      writeLetter(p[ i ]);
    delay(50);
  }
 usb_keyboard_press(40,0);
}

void writeNumber(char number)
{
  char *ptr = strchr(nums,number);
  if(ptr){
    int index = ptr - nums;
    int ascii = (int) number;
    usb_keyboard_press(index,0);
  }
}

void writeLetter(char letter)
{
  if(letter == '(')
  {
    usb_keyboard_press(KEY_9,KEY_SHIFT);
    return;
  }
  if(isUpper(letter))
  {
    char *ptr = strchr(keysUpper,letter);
    if(ptr){
      int index = ptr - keysUpper;
      int ascii = (int) letter;
      if(isUpper(letter))
        usb_keyboard_press(index,KEY_SHIFT);
      else
        usb_keyboard_press(index,0);
    }
  }
  else
  {
    char *ptr = strchr(keysLower,letter);
    if(ptr){
      int index = ptr - keysLower;
      int ascii = (int) letter;
      if(isUpper(letter))
        usb_keyboard_press(index,KEY_SHIFT);
      else
        usb_keyboard_press(index,0);
    }
  }

}


bool isUpper(char letter)
{
  int ascii = (int) letter;
  if(ascii >= 65 && ascii <=90)
  {
    blink();
    return true;
  }
  else
    return false;
}

bool isNumber(char letter)
{
  int ascii = (int) letter;
  if(ascii >= 48 && ascii <=57)
  {
    // blink();
    return true;
  }
  else
    return false;
}

void blink()
{
  digitalWrite(led, HIGH);
  delay(10);
  digitalWrite(led, LOW);

}


