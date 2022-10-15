/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: October 7, 2018
  Outputs: Displays power-on-reset values of all ENC28J60 registers 
	from BANK0, BANK1, BANK2 and BANK3 on serial terminal */

#include <SPI.h>

#define CS 10
#define MOSI 11
#define MISO 12
#define SCK 13

#define RD_CTRL_REG 0x00
#define WR_CTRL_REG 0x40
#define ECON1 0x1F

void setup() 
{
  Serial.begin(9600); 
  SPI.begin();                              
  pinMode(CS, OUTPUT);                                  //  Setting CSN pin as output.
  pinMode(MOSI, OUTPUT);                                //  Setting MOSI pin as output.
  pinMode(MISO, INPUT);                                 //  Setting MISO pin as input.
  pinMode(SCK, OUTPUT);                                 //  Setting SCK pin as output.
  digitalWrite(CS, HIGH);                               //  Setting CS = 1 to make SPI idle.
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
  SPI.transfer(ADDR);                                  // Dummy byte    
  regVal = SPI.transfer(ADDR);                   
  digitalWrite(CS, HIGH);                              // Setting CS = 1 to make SPI idle.
  return regVal;
}