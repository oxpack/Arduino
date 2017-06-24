/*
 Example 41.1 - Microchip MCP23017 with Arduino
 http://tronixstuff.com/tutorials > chapter 41
 John Boxall | CC by-sa-nc
*/
// pins 15~17 to GND, I2C bus address is 0x20
#include "Wire.h"
void setup()
{
  Serial.begin(9600);
  Wire.begin(); // wake up I2C bus

  // set I/O pins to outputs

  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x21);//second chip
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x21);//second chip
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission();
}

void binaryCount()
{
  for (unsigned long a = 0; a < 0xFFFF; a++)
  {
    set_bits(a);
  }
}

void l_r()
{
  unsigned long i = 1;
  for (byte a = 0; a < 24; a++)
  {
    set_bits(i);
    i = i << 1;
    delay(100);
  }
}

void r_l()
{
  unsigned long i = 1;
  i = i << 23;
  for (byte a = 0; a < 24; a++)
  {
    set_bits(i);
    i = i >> 1;
    delay(100);
  }
}

void greta()
{
  unsigned long letter[] = {
    0x000000, 0x000000, 0x00ff00, 0x01ffc0, 0x03e1e0, 0x070070, 0x0e0038, 0x0c0018, 0x0c0018, 0x1c080c, 0x18180c, 0x1c180c,
    0x0c1808, 0x0c1818, 0x0ff818, 0x0ff838, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x0ffff8, 0x0ffff8, 0x000808,
    0x000808, 0x001808, 0x001c08, 0x003c18, 0x00fe18, 0x03e7f8, 0x0fc3f0, 0x0e00c0, 0x080000, 0x000000, 0x000000, 0x000000,
    0x0ffff8, 0x0ffff8, 0x0dedd8, 0x0c0c08, 0x0c0c08, 0x0c0c08, 0x0c0c08, 0x0c0c08, 0x0c0c08, 0x0c0008, 0x000000, 0x000000,
    0x000008, 0x000008, 0x000008, 0x000008, 0x000008, 0x0ffff8, 0x0ffff8, 0x0ffff8, 0x000008, 0x000008, 0x000008, 0x000008,
    0x000008, 0x000000, 0x0c0000, 0x0f0000, 0x07e000, 0x01fc00, 0x00df80, 0x00c7e0, 0x00c0f8, 0x00c03c, 0x00c0f8, 0x00c7f0,
    0x00dfc0, 0x00fe00, 0x07f000, 0x0f8000, 0x0c0000, 0x000000, 0x000000
  };

  for (int i = 0; i < (sizeof(letter)/sizeof(long)); i++)
  {
    set_bits(letter[i]);
    delay(15);
  }

}

void set_bits(unsigned long i)
{
  byte b;
  b = i & B11111111;
  Serial.print(b);
  Serial.print("  ");

  Wire.beginTransmission(0x20); //chip 1
  Wire.write(0x12); // GPIOA
  Wire.write(b); // port A
  Wire.endTransmission();

  i = i >> 8;
  b = i & B11111111;

  Wire.beginTransmission(0x20); //chip 1
  Wire.write(0x13); // GPIOB
  Wire.write(b); // port B
  Wire.endTransmission();

  i = i >> 8;
  b = i & B11111111;

  Wire.beginTransmission(0x21); //chip 2
  Wire.write(0x12); // GPIOA
  Wire.write(b); // port B
  Wire.endTransmission();
}

void all_flash()
{
  for (byte a = 0; a < 2; a++)
  {
    set_bits(0xFFFFFFu);
    delay(500);
    set_bits(0x000000u);
    delay(500);
  }
}

void loop()
{ Serial.println("Begin all_flash()");
  all_flash();
  greta();
  //for (int i = 0; i < 5; i++)
  //{
   // l_r();
  //  r_l();
  //}
 // Serial.println("Begin binaryCount()");
 // binaryCount();
 delay(1000);
}
