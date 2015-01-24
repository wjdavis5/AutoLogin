# AutoLogin
Teensy 3.1 auto login sketch

I recently got a Teensy 3.1 and have been looking for little projects to do.

This is a quick one that I wrote that, when plugged in, automatically logs me into my computer. 

It uses the basic keyboard emulation to send keys to the computer, typing in my password.

It uses 3 char arrays, with the letters/numbers properly offset so that its easy to send the 
proper int to the usb_keyboard_press function

```
char keysLower[31] = "0000abcdefghijklmnopqrstuvwxyz";

char keysUpper[31] = "0000ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char nums[68] = "pppppppppppppppppppppppppppppp1234567890";
```

You call 
```
  writeWord("Mywordtowrite");
```
here is the function - it just loops through each char and calls the proper write method
```

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
```

Here is writeNumber
```
void writeNumber(char number)
{
  char *ptr = strchr(nums,number); //try to find the char in the array
  if(ptr){
    int index = ptr - nums; //get the index of the char in the array - this should match the proper int for the keyboard
    int ascii = (int) number;
    usb_keyboard_press(index,0); //write out that number
  }
}
```
And finally - writeLetter, which checks (based on ASCII value) if the char is Upper or lower
and applies the proper key modified (KEY_SHIFT)

```
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

```
