/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: October 7, 2018
  Outputs: Displays power-on-reset values of all ENC28J60 registers 
<<<<<<< HEAD
		   from BANK0, BANK1, BANK2 and BANK3 on serial terminal */
=======
	from BANK0, BANK1, BANK2 and BANK3 on serial terminal */
>>>>>>> 2435b4d (Updated and corrected program)

#include <SPI.h>

#define CS 10
#define MOSI 11
#define MISO 12
#define SCK 13

<<<<<<< HEAD
void setup() 
{
  Serial.begin(9600);
  SPI.begin();                               
=======
#define RD_CTRL_REG 0x00
#define WR_CTRL_REG 0x40
#define ECON1 0x1F

void setup() 
{
  Serial.begin(9600); 
  SPI.begin();                              
>>>>>>> 2435b4d (Updated and corrected program)
  pinMode(CS, OUTPUT);                                  //  Setting CSN pin as output.
  pinMode(MOSI, OUTPUT);                                //  Setting MOSI pin as output.
  pinMode(MISO, INPUT);                                 //  Setting MISO pin as input.
  pinMode(SCK, OUTPUT);                                 //  Setting SCK pin as output.
  digitalWrite(CS, HIGH);                               //  Setting CS = 1 to make SPI idle.
<<<<<<< HEAD
  delay(2000);
}

void loop() 
{              
  for (byte j = 0; j <= 3; j++)
  {
    writeReg(0x40 | 0x1F, j);
    Serial.print("BANK: ");
    Serial.println(j);
    for (byte k = 0; k <= 0x19; k++)
    {
      Serial.print(k, HEX);
      Serial.print("h: ");
      Serial.print(readReg(k), HEX);
      Serial.print(", ");
    }
    Serial.println("\r\n");
  }
=======
}

void loop() 
{
  for(int BANK_NUM = 0; BANK_NUM <= 3; BANK_NUM++)
  {
    writeReg(WR_CTRL_REG | ECON1, BANK_NUM);
    Serial.print("BANK#");
    Serial.print(BANK_NUM);
    Serial.print(": ");

    for(int REG_ADDR = 0; REG_ADDR <= 19; REG_ADDR++)
    {
      Serial.print(readReg(RD_CTRL_REG | REG_ADDR), HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  
>>>>>>> 2435b4d (Updated and corrected program)
  while(1);
}

void writeReg(byte ADDR, byte CONTENT)
{
  digitalWrite(CS, LOW);                               // Setting CS = 0 to make SPI active.
  SPI.transfer(ADDR);                                  // Address of register where content is to be written.
  SPI.transfer(CONTENT);                               // Actual content that is to be written.
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
}

byte readReg(byte ADDR)
{
  byte regVal;
  digitalWrite(CS, LOW);                               // Setting CS = 0 to make SPI active.
<<<<<<< HEAD
  SPI.transfer(ADDR);                                  // Address of register from where content is to be read.    
  regVal = SPI.transfer(0x00);                   
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
  return regVal;
}
=======
  SPI.transfer(ADDR);                                  // Dummy byte    
  regVal = SPI.transfer(ADDR);                   
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
  return regVal;
}
>>>>>>> 2435b4d (Updated and corrected program)
