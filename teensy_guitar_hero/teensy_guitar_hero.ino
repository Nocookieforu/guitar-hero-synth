#include <Wire.h>

#define GUITAR_I2C_ADDR   0x52
#define I2C_REG_START     0xA40000
#define I2C_REG_LEN       0x100

extern "C"
{

enum touchbar_t
{
  TB_NO_TOUCH   = 0x0F,
  TB_FRET1      = 0x04,
  TB_FRETS_12   = 0x07,
  TB_FRET2      = 0x0A,
  TB_FRETS_23   = 0x0C,
  TB_FRETS_23_2 = 0x0D,
  TB_FRET3      = 0x12,
  TB_FRET3_2    = 0x13,
  TB_FRETS_34   = 0x14,
  TB_FRETS_34_2 = 0x15,
  TB_FRET4      = 0x17,
  TB_FRET4_2    = 0x18,
  TB_FRETS_45   = 0x1A,
  TB_FRET5      = 0x1F,
};

} //extern "C"

typedef struct guitar_data_format
{
  unsigned char analog_x;
  unsigned char analog_y;
  //touchbar_t    touchbar;
  unsigned char touchbar;
  unsigned char whammy_bar;
  unsigned char buttons1;
  unsigned char buttons0;
} guitar_data;

const unsigned int gh3_id_bytes[6] = 
{
   0x03, 0x01, 0x20, 0xA4, 0x00, 0x00, 
};
unsigned int i2c_buff[I2C_REG_LEN] = {0};

void setup() {
  Serial.begin(115200);

  // Set up I2C and send [0x40, 0x00] to init Guitar
  Wire.begin();
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0x40);
  Wire.send(0x00);
  Wire.endTransmission();
}

void init_guitar()
{
  // Write 0x00 to 0xA40040 to initialize guitar
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0x40);
  Wire.send(0x00);
  Wire.send(0xA4);
  Wire.send(0x00);
  Wire.endTransmission();
  
  // Check ID of guitar
  // Send ID register location, then read 6 bytes of register ID
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0xFA);
  Wire.send(0x00);
  Wire.send(0xA4);
  Wire.endTransmission();
  Wire.requestFrom(GUITAR_I2C_ADDR, 6);
  int curr_byte = 0;
  while (Wire.available())
  {
    i2c_buff[curr_byte] = Wire.read();
    curr_byte++;
    Serial.print(i2c_buff[curr_byte]);
  }
  
  // Write 0x55 to 0xA400F0
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0xF0);
  Wire.send(0x00);
  Wire.send(0xA4);
  Wire.send(0x55);
  Wire.endTransmission();
  
  // Write 0x00 to A400FB
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0xF0);
  Wire.send(0x00);
  Wire.send(0xA4);
  Wire.send(0x55);
  Wire.endTransmission();
}

/*
bool read_guitar_data(guitar_data* data)
{
  // Read data from register 0xA40008
  Wire.beginTransmission(GUITAR_I2C_ADDR);
  Wire.send(0x08);
  Wire.send(0x00);
  Wire.send(0xA4);
  Wire.endTransmission();
  Wire.requestFrom(GUITAR_I2C_ADDR, 6);
  
  int curr_byte = 0;
  while (Wire.available())
  {
    i2c_buff[curr_byte] = Wire.read();
    curr_byte++;
    Serial.print(i2c_buff[curr_byte]);
  }
  
  if (curr_byte < 6)
  {
    return false;
  }
  
  data->analog_x = i2c_buff[0];
  data->analog_y = i2c_buff[1];
  //data->touchbar = (touchbar_t)i2c_buff[2];
  data->touchbar = i2c_buff[2];
  data->whammy_bar = i2c_buff[3];
  data->buttons1 = i2c_buff[4];
  data->buttons0 = i2c_buff[5];
  return true;
}
*/

void loop() {
  // put your main code here, to run repeatedly:

}
