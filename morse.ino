#define TIME_DELAY 200

// KDWallace 2023.12.28
// A simple algorithmic approach to morse code
// currently 956 bytes of storage and 9 bytes of dynamic memory when string is removed from the function (2044B storage and 53B of dynamic memory with morse("Hello World");)
///////////////////////////////////////////////////////////////////////////////////////////////////

// simple function for turning light on and off for time/1000 seconds
void blink(int time)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
  delay(TIME_DELAY);
}

void dit()
{
  blink(TIME_DELAY); //blink for 0.2 seconds
}

void dah()
{
  blink(TIME_DELAY*3); //blink for 0.6 seconds
}

// dirty function for rounding down
char ceil(float value)
{
  // if the float is greater than the casted value, it needs to be rounded up as casting rounds down
  // an alternative way would have been to check if (value != (char)value) return (char)value + 1
  if (value > (char)value)
    return (char)value + 1;
  return (char)value;
}

// converts letters to blinks algorithmically
void morse(const char* string)
{
  // calc length of string from pointer. Could be improved
  int length;
  for (length = 0; string[length] != '\0'; length++);

  // order of characters as well as non-existing chars
  const char alph[] = "##etianmsurwdkgohvf#l#pjbxcyzq";

  for (int i = 0; i < length; i++)
  {
    char c = string[i];
    // converts uppercase to lower case by treating it as an unsigned short
    if (c >= 'A' && c <= 'Z')
      c += 32;
    
    // if is lowercase char
    if (c >= 'a' && c <= 'z')
    {
      // check for positional index in alph
      for (short j = 0; j < 30; j++)
      {
        if (c == alph[j])
        {
          // index in alph that can be manipulated
          char index = j + 1;
          // unisgned char for bit storage of dits and dahs (1 byte)
          unsigned char dahs = 0;
          // initialise position in the byte
          short pos = -1;

          // half val per iteration, even is dah, odd is dit
          while (index > 2)
          {
            pos++;

            // if the index is even this represents a dah (1), if odd this is a dit (0)
            if (index%2 == 0)
              dahs = (dahs | (1 << (pos)));
            
            // index is halved and rounded up if needed
            index = ceil((float)index/2);
          }
          // flips order of dits and dahs
          for (short k = pos; k > -1; k--)
          {
            // if the bit is a 1
            if ((dahs >> k) & 1)
              dah();
            
            // if the bit is a 0
            else
              dit();
          }
          break;
        }
      }
      delay(TIME_DELAY*2); // time delay between chars
    }

    // if the character is a space
    else if (c == ' ')
      delay(TIME_DELAY*6);
  }
  delay(TIME_DELAY*6); // delay at end of string
}

// the setup function runs once when you press reset or power the board
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever and ever
void loop()
{
  morse("Hello World");
}
