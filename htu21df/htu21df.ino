#include <Wire.h>

// target device:HTU21D(i2c temperature sensor)
#define ADDR 0x40
#define CMD_READ_TEMP_HOLD 0xe3
#define CMD_READ_HUM_HOLD 0xe5
#define CMD_READ_TEMP_NOHOLD 0xf3
#define CMD_READ_HUM_NOHOLD 0xf5
#define CMD_WRITE_USER_REG 0xe6
#define CMD_READ_USER_REG 0xe7
#define CMD_SOFT_RESET 0xfe

void write_i2c_byte(uint8_t adr, uint8_t val)
{
  Wire.beginTransmission(adr);
  Wire.write(val);
  Wire.endTransmission();  
}

#define READ_MAX_LEN 16
uint8_t readData[READ_MAX_LEN];
uint8_t cmdCnt;

uint8_t read_i2c_block_data(uint8_t adr, uint8_t reg, uint8_t len) {
  write_i2c_byte(adr, reg);
  delay(100);

  cmdCnt = 0;
  Wire.requestFrom(adr, len);
  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    readData[cmdCnt] = c;
    cmdCnt++;
  }

  return cmdCnt;  
}

void setup()
{
  Serial.begin(115200); 
  Serial.println("start");

  // I2C
  Wire.begin();
  Wire.setClock(100000L); //100kHz up to 400kHz
}

void loop()
{
  write_i2c_byte(ADDR, CMD_SOFT_RESET);
  uint8_t readSize = read_i2c_block_data(ADDR, CMD_READ_TEMP_HOLD, 3);
  if(readSize > 0) {
    uint16_t tmp = readData[0];
    tmp = tmp << 8;
    tmp = tmp | readData[1];
    tmp = tmp & 0xFFFC;

    float temp = -46.85 + (175.72 * tmp / 65536);

    Serial.print("Temperature: ");
    Serial.print(temp, 1);
    Serial.println(" C");
  }
  else {
    Serial.println("fail to get temperature");
  }

  delay(3000);
}
